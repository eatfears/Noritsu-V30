#pragma once

#include "fake_leaders.h"
#include "timeouts.h"
#include "drive_sensor.h"


extern DriveSensor driveSensor;

enum stage
{
  stageIdle,
  stageStartup,
  stageReady,
  stageLeaderLoad,
  stageLeaderEnd,
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

      repl_cd_element.checkClose();
      repl_bl_element.checkClose();
      repl_fix_element.checkClose();
      repl_stb_element.checkClose();

      if (currentStage == stageStartup)
      {
        film_l_element.setOpen(film_l_sensor.isOpen());
        film_r_element.setOpen(film_r_sensor.isOpen());
        perf_l_element.setOpen(perf_l_sensor.isOpen());
        perf_r_element.setOpen(perf_r_sensor.isOpen());
      }
      else
      {
        film_l_element.setOpen(ik_led_sensor.isOpen());
        film_r_element.setOpen(ik_led_sensor.isOpen());
        perf_l_element.setOpen(ik_led_sensor.isOpen());
        perf_r_element.setOpen(ik_led_sensor.isOpen());
      }
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

      drive_sensor.read();
      cover_sensor.read();

      ik_led_sensor.read();
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
      cover_lock_element.setOpen(true);

      pressure_solenoid_l_element.setOpen(true);
      pressure_solenoid_r_element.setOpen(true);

      led_element.setOpen(false);
      buzz_element.setOpen(false);
    }

    void stageWork() override
    {
      cover_element.setOpen(cover_sensor.isOpen());
      leader_element.setOpen(leader_sensor.isOpen());

      if (!leader_sensor.isOpen() && !cover_sensor.isOpen() )
      {
        nextStage = stageLeaderLoad;
      }
    }
};

/******* Ready *****************/
class StageReady : public Stage
{
  public:
    StageReady() : Stage(F("Ready"))
    {
      cover_element.setOpen(false);

      cover_lock_element.setOpen(true);

      pressure_solenoid_l_element.setOpen(true);
      pressure_solenoid_r_element.setOpen(true);

      film_l_element.setOpen(true);
      film_r_element.setOpen(true);
      perf_l_element.setOpen(true);
      perf_r_element.setOpen(true);
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
      cover_element.setOpen(false);
      cover_lock_element.setOpen(false);
      pressure_solenoid_l_element.setOpen(false);
      pressure_solenoid_r_element.setOpen(false);

      driveSensor.resetCounter();

      //startSendingFakeLeaders();
    }

    void stageWork() override
    {
      if (leader_sensor.isOpen())
      {
        nextStage = stageLeaderEnd;
      }
    }
};


/******** Leader end ****************/
class StageLeaderEnd: public Stage
{
  public:
    StageLeaderEnd() : Stage(String(F("Leader end. Holes: ")) + String(driveSensor.getCounter()))
    {
      cover_element.setOpen(false);
      cover_lock_element.setOpen(false);
      pressure_solenoid_l_element.setOpen(true);
      pressure_solenoid_r_element.setOpen(true);

      m_LaunchHoles = driveSensor.getCounter();
    }

    void stageWork() override
    {
      if (driveSensor.getCounter() - m_LaunchHoles > LEADER_END_HOLES)
      {
        nextStage = stageFilmLoad;
      }
    }

    unsigned long m_LaunchHoles;
};


/******** Film loading ****************/
class StageFilmLoad : public Stage
{
  public:
    StageFilmLoad() : Stage(F("Film loading"))
    {
      cover_lock_element.setOpen(false);
      pressure_solenoid_l_element.setOpen(true);
      pressure_solenoid_r_element.setOpen(true);
    }

    void stageWork() override
    {
      if (film_l_sensor.isOpen() && film_r_sensor.isOpen())
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

      m_LaunchHoles = driveSensor.getCounter();
    }

    void stageWork() override
    {
      if (driveSensor.getCounter() - m_LaunchHoles > SECURITY_HOLES)
      {
        nextStage = stageFilmLoad;
      }
    }

    unsigned long m_LaunchHoles;
};
