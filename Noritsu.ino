#include "Arduino.h"

#include "logger.h"

#include "sensors.h"
#include "elements.h"


int m_nextTimeout = 0;

#include "pump.h"
#include "stages.h"
#include "drive_sensor.h"

DriveSensor driveSensor;

stage currentStage = stageIdle;
stage nextStage = stageIdle;
Stage *p_stage = nullptr;


void setup()
{
  logger.init();
  logger.info(F("Initializing controller"));

  leader_sensor.init();
  film_l_sensor.init();
  film_r_sensor.init();
  perf_l_sensor.init();
  perf_r_sensor.init();

  drive_sensor.init();
  cover_sensor.init();

  ik_led_sensor.init();

  leader_element.init();
  film_l_element.init();
  film_r_element.init();
  perf_l_element.init();
  perf_r_element.init();

  cover_element.init();
  cover_lock_element.init();

  pressure_solenoid_l_element.init();
  pressure_solenoid_r_element.init();

  repl_cd_element.init();
  repl_bl_element.init();
  repl_fix_element.init();
  repl_stb_element.init();

  led_element.init();
  buzz_element.init();

  test_element.init();

  p_stage = new StageIdle();

  nextStage = stageStartup;
}

void loop()
{
  String command = "";
  if (Serial.available() > 0)
  {
    command = Serial.readStringUntil('\n');
  }

//  if (command == F("1"))
//  {
//    logger.info(F("Security"));
//    nextStage = stageSecurityTimeout;
//  }
  /*
    else if (command == F("q"))
    {
    logger.info(F("Changing test"));
    static bool fff = false;
    fff = !fff;
    test_element.setOpen(fff);
    leader_element.setOpen(fff);
    repl_cd_element.setOpen(fff);
    }
    else if (command == F("a"))
    {
      repl_cd_element.fire();
    }
    else if (command == F("s"))
    {
      repl_bl_element.fire();
    }
    else if (command == F("d"))
    {
      repl_fix_element.fire();
    }
    else if (command == F("f"))

    {
      repl_stb_element.fire();
    }

    else if (command == F("z"))
    {
    static bool fff = false;
    fff = !fff;
    cover_lock_element.setOpen(fff);
    pressure_solenoid_l_element.setOpen(fff);
    pressure_solenoid_r_element.setOpen(fff);
    }
  */
  if (command == F("c"))
  {
    FakeLeaders::start();
  }
  if (command == F("x"))
  {
    FakeLeaders::stop();
  }
//  if (command == F("v"))
//  {
//    logger.info(driveSensor.getCounter());
//    logger.info(driveSensor.getPumpCounter());
//  }


  if (nextStage != currentStage)
  {
    delete p_stage;
    switch (nextStage)
    {
      case stageIdle:
        p_stage = new StageIdle();
        break;
      case stageStartup:
        p_stage = new StageStartup();
        break;
      case stageReady:
        p_stage = new StageReady();
        break;
      case stageLeaderLoad:
        p_stage = new StageLeaderLoad();
        break;
      case stageLeaderEnd:
        p_stage = new StageLeaderEnd();
        break;
      case stageFilmLoad:
        p_stage = new StageFilmLoad();
        break;
      case stageSecurityTimeout:
        p_stage = new StageSecurityTimeout();
        break;
      default:
        logger.critical(String(F("Unknown stage ")) + String(nextStage) + String(F(". Going idle now")));
        p_stage = new StageIdle();
        nextStage = stageIdle;
        break;
    }
    currentStage = nextStage;
  }
  p_stage->work();

  delay(100);

  static void(*handler)(void) = 0;
  static unsigned long handlerTimer;

  if (FakeLeaders::m_nextAfter)
  {
    handlerTimer = millis();
    handler = FakeLeaders::m_nextAfter;

    FakeLeaders::m_nextAfter = nullptr;
  }

  if (millis() - handlerTimer > FakeLeaders::m_nextTimeout && handler)
  {
    handler();
    handler = nullptr;
  }

}
