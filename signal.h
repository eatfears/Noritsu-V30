#pragma once

#include "elements.h"

class Signal
{
  public:
    static void beep()
    {
      m_Start = millis();
    }

    static void check()
    {
      if (millis() - m_Start < 200)
      {
        digitalWrite(LED_OUT_PIN, HIGH);
        digitalWrite(BUZZ_OUT_PIN, HIGH);
      }
      else if (millis() - m_Start < 500)
      {
        digitalWrite(LED_OUT_PIN, LOW);
        digitalWrite(BUZZ_OUT_PIN, LOW);
      }
      else if (millis() - m_Start < 1000)
      {
        digitalWrite(LED_OUT_PIN, HIGH);
        digitalWrite(BUZZ_OUT_PIN, HIGH);
      }
      else if (millis() - m_Start > 1000)
      {
        digitalWrite(LED_OUT_PIN, LOW);
        digitalWrite(BUZZ_OUT_PIN, LOW);
      }
    }
  private:
    static unsigned long m_Start;
};

unsigned long Signal::m_Start = -1000;
