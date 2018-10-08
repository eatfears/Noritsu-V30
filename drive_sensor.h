#include "pinout.h"
#include "logger.h"

#define NUM 5

class DriveSensor
{
  public:
    DriveSensor()
    {
      m_LastMillis = millis();
      attachInterrupt(digitalPinToInterrupt(DRIVE_IN_PIN), blinks, RISING);
      //attachInterrupt(digitalPinToInterrupt(DRIVE_IN_PIN), blinks, CHANGE);
    }
    ~DriveSensor()
    {
      detachInterrupt(digitalPinToInterrupt(DRIVE_IN_PIN));
    }

    static unsigned long getInterval()
    {
      unsigned long ret = 0;

      for (int i = 0; i < NUM; i++)
      {
        ret += m_Times[i];
      }
      return ret / NUM;
    }

    static unsigned long getCounter() {
      return m_Counter;
    }
    static void resetCounter() {
      m_Counter = 0;
    }

  private:
    static void blinks()
    {
      m_Counter++;
      unsigned long ms = millis();
      static int i = 0;
      int interval = ms - m_LastMillis;

      if (interval > 0)
      {
        m_Times[i] = interval;
        i++; if (i >= NUM) i = 0;

        logger.info(String(F("Counter: ")) + String(m_Counter) + F(". Interval: ") + String(getInterval()) + F(". Interval last: ") + String(interval));

        m_LastMillis = ms;
      }
    }

    static unsigned long m_Times[NUM];
    static unsigned long m_Counter;
    static unsigned long m_LastMillis;
};

unsigned long DriveSensor::m_Counter = 0;
unsigned long DriveSensor::m_LastMillis = 0;
unsigned long DriveSensor::m_Times[NUM] = {};
