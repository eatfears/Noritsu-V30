#pragma once

#include "pinout.h"
#include "logger.h"
#include "stages_enum.h"

extern stage currentStage;

#define NUM 5

class DriveSensor
{
  public:
    DriveSensor()
    {
      //m_LastMillis = millis();
      attachInterrupt(digitalPinToInterrupt(DRIVE_IN_PIN), handler, RISING);
    }
    ~DriveSensor()
    {
      detachInterrupt(digitalPinToInterrupt(DRIVE_IN_PIN));
    }
/*
    static unsigned long getInterval()
    {
      unsigned long ret = 0;

      for (int i = 0; i < NUM; i++)
      {
        ret += m_Times[i];
      }
      return ret / NUM;
    }*/

    static unsigned long getCounter()
    {
      return m_Counter;
    }
    static void resetCounter()
    {
      m_Counter = 0;
    }

    static unsigned long getPumpCounter()
    {
      return m_PumpCounter;
    }
    static void resetPumpCounter()
    {
      m_PumpCounter = 0;
    }

  public:
    static void handler()
    {
      m_Counter++;

      if (currentStage == stageFilmLoad)
      {
        if (!film_l_sensor.isOpen() && !film_r_sensor.isOpen())
        {
          m_PumpCounter += 2;
        }
        else if (!film_l_sensor.isOpen() || !film_r_sensor.isOpen())
        {
          m_PumpCounter++;
        }
      }
/*
      unsigned long ms = millis();
      static int i = 0;
      int interval = ms - m_LastMillis;

      if (interval > 100)
      {
        m_Times[i] = interval;
        i++; if (i >= NUM) i = 0;

        //        logger.info(String(F("Counter: ")) + String(m_Counter) + F(". Interval: ") + String(getInterval()) + F(". Interval last: ") + String(interval));

        m_LastMillis = ms;
      }
      */
    }

    //static unsigned long m_Times[NUM];
    static unsigned long m_Counter;
    static unsigned long m_PumpCounter;
    //static unsigned long m_LastMillis;
};

unsigned long DriveSensor::m_Counter = 0;
unsigned long DriveSensor::m_PumpCounter = 0;
//unsigned long DriveSensor::m_LastMillis = 0;
//unsigned long DriveSensor::m_Times[NUM] = {};
