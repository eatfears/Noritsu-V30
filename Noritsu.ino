#include "logger.h"

#include "sensors.h"
#include "elements.h"

#include "stages.h"

//https://github.com/JChristensen/Timer/archive/v2.1.zip
//https://playground.arduino.cc/code/timer
//http://www.doctormonk.com/2012/01/arduino-timer-library.html
#include "Timer.h"

Timer t;

void setup()
{
  logger.init();
  logger.info("Initializing controller");

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
  cover_lock_element.init();
  pressure_solenoid_element.init();

  led_element.init();
  buzz_element.init();
}

void loop()
{
  /*
    if (Serial.available() > 0)
    {
    logger.warning("recieved string: " + Serial.readStringUntil('\n'));
    }
    logger.info("Stage 1. " + String(leader_sensor.isOpen()));

    delay(100);
  */

  /*
    switch (currentStage)
    {
      case stageIdle:
        {
          StageIdle s;
          s.run();
        }
        break;
      case stageStartup:
        {
          StageStartup s;
          s.run();
        }
        break;
    }
  */

  t.update();
}
