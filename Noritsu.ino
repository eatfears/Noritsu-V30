#include "logger.h"

#include "sensors.h"
#include "elements.h"

//https://github.com/JChristensen/Timer/archive/v2.1.zip
//https://playground.arduino.cc/code/timer
//http://www.doctormonk.com/2012/01/arduino-timer-library.html
#include "Timer.h"
Timer t;

#include "stages.h"
Stage *stage = nullptr;

void setup()
{
  logger.init();
  logger.info(F("Initializing controller"));

  leader_sensor.init();
  film_l_sensor.init();
  film_r_sensor.init();
  perf_l_sensor.init();
  perf_r_sensor.init();
  cover_sensor.init();


  leader_element.init();
  film_l_element.init();
  film_r_element.init();
  perf_l_element.init();
  perf_r_element.init();
  cover_element.init();
  cover_lock_element.init();
  pressure_solenoid_element.init();

  led_element.init();
  buzz_element.init();

  stage = new StageIdle();
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

  //  delay(100);

  t.update();
}
