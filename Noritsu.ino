#include "Arduino.h"

#include "logger.h"

#include "sensors.h"
#include "elements.h"

//https://github.com/JChristensen/Timer/archive/v2.1.zip
//https://playground.arduino.cc/code/timer
//http://www.doctormonk.com/2012/01/arduino-timer-library.html
#include "Timer.h"
Timer t;

#include "pump.h"
#include "stages.h"
Stage *stage = nullptr;

#include "drive_sensor.h"
DriveSensor driveSensor;

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

  stage = new StageIdle();

  nextStage = stageStartup;
}

void loop()
{
  String command = "";
  /**/
  if (Serial.available() > 0)
  {
    command = Serial.readStringUntil('\n');
  }

  if (command == F("start"))
  {
    logger.info(F("Starting"));
    nextStage = stageStartup;
  }
  else if (command == F("1"))
  {
    logger.info(F("Security"));
    nextStage = stageSecurityTimeout;
  }
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

  if (nextStage != currentStage)
  {
    delete stage;
    switch (nextStage)
    {
      case stageIdle:
        stage = new StageIdle();
        break;
      case stageStartup:
        stage = new StageStartup();
        break;
      case stageReady:
        stage = new StageReady();
        break;
      case stageLeaderLoad:
        stage = new StageLeaderLoad();
        break;
      case stageFilmLoad:
        stage = new StageFilmLoad();
        break;
      case stageSecurityTimeout:
        stage = new StageSecurityTimeout();
        break;
      default:
        logger.critical("Unknown stage " + String(nextStage) + F(". Going idle now"));
        stage = new StageIdle();
        nextStage = stageIdle;
        break;
    }
    currentStage = nextStage;
  }
  stage->work();

  delay(20);
  t.update();

  if (nextAfter)
  {
    t.after(nextTimeout, nextAfter);
    nextAfter = nullptr;
  }
}
