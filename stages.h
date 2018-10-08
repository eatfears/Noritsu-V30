#pragma once

#include "fake_leaders.h"
#include "timeouts.h"

enum stage
{
  stageIdle,
  stageStartup,
  stageReady,
  stageLeaderLoad,
  stageFilmLoad,
  stageSecurityTimeout
};

stage currentStage = stageIdle;
stage nextStage = stageIdle;

class Stage
{
  public:
    Stage(String name) : m_Name(name)
    {
      logger.notice(m_Name + F(" stage"));
    };

    ~Stage()
    {
      logger.trace(m_Name + F(" stage end"));
    };

    void work()
    {
      readSensors();
      stageWork();
    }

  protected:
    virtual void stageWork()
    {
      logger.warning(m_Name + F(" stage. Empty work"));
      delay(1000);
    }
    String m_Name;

  private:
    void readSensors()
    {
      leader_sensor.read();
      film_l_sensor.read();
      film_r_sensor.read();
      perf_l_sensor.read();
      perf_r_sensor.read();
      cover_sensor.read();
    }
};

/****************************************************************/

/******* Ilde *****************/
class StageIdle : public Stage
{
  public:
    StageIdle() : Stage(F("Idle")) {}

    void stageWork() override {}
};

/******** Startup ****************/
class StageStartup : public Stage
{
  public:
    StageStartup() : Stage(F("Startup"))
    {
      leader_element.setOpen(true);
      cover_lock_element.setOpen(true);
      pressure_solenoid_l_element.setOpen(true);
      pressure_solenoid_r_element.setOpen(true);

      led_element.setOpen(false);
      buzz_element.setOpen(false);

      m_LaunchTime = millis();
    }

    void stageWork() override
    {
      film_l_element.setOpen(film_l_sensor.isOpen());
      film_r_element.setOpen(film_r_sensor.isOpen());
      perf_l_element.setOpen(perf_l_sensor.isOpen());
      perf_r_element.setOpen(perf_r_sensor.isOpen());

      if (millis() - m_LaunchTime > m_StartupTime)
      {
        nextStage = stageReady;
      }
    }

  private:
    int m_LaunchTime;
    const static int m_StartupTime = STARTUP_TIMEOUT;
};

/******* Ready *****************/
class StageReady : public Stage
{
  public:
    StageReady() : Stage(F("Ready"))
    {
      cover_lock_element.setOpen(true);
      pressure_solenoid_l_element.setOpen(true);
      pressure_solenoid_r_element.setOpen(true);

      film_l_element.setOpen(true);
      film_r_element.setOpen(true);
      perf_l_element.setOpen(true);
      perf_r_element.setOpen(true);

      startSendingFakeLeaders();
    }

    void stageWork() override
    {

      if (!leader_sensor.isOpen() && !cover_sensor.isOpen() )
      {
        nextStage = stageLeaderLoad;
      }
    }
};

/******** Leader loading ****************/
class StageLeaderLoad : public Stage
{
  public:
    StageLeaderLoad() : Stage(F("Leader loading"))
    {
      cover_lock_element.setOpen(false);
      pressure_solenoid_l_element.setOpen(false);
      pressure_solenoid_r_element.setOpen(false);
    }

    void stageWork() override
    {
      if (leader_sensor.isOpen()) //TODO: add timer for security
      {
        nextStage = stageFilmLoad;
      }
    }
};


/******** Film loading ****************/
class StageFilmLoad : public Stage
{
  public:
    StageFilmLoad() : Stage(F("Film loading"))
    {
      cover_lock_element.setOpen(false);
      pressure_solenoid_l_element.setOpen(false);
      pressure_solenoid_r_element.setOpen(false);
    }

    void stageWork() override
    {

      if (leader_sensor.isOpen()) //TODO: add timer for security
      {
        nextStage = stageSecurityTimeout;
      }
    }
};

/******** Security timeout ****************/
class StageSecurityTimeout : public Stage
{
  public:
    StageSecurityTimeout() : Stage(F("Security timeout"))
    {
      cover_lock_element.setOpen(false);
      pressure_solenoid_l_element.setOpen(true);
      pressure_solenoid_r_element.setOpen(true);

      m_LaunchTime = millis();
    }

    void stageWork() override
    {
      if (millis() - m_LaunchTime > m_SecurityTimeout)
      {
        nextStage = stageReady;
      }
    }
  private:
    int m_LaunchTime;
    const static int m_SecurityTimeout = SECURITY_TIMEOUT;
};
