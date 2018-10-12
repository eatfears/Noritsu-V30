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
        led_element.setOpen(true);
        buzz_element.setOpen(true);
      }
      else if (millis() - m_Start < 500)
      {
        led_element.setOpen(false);
        buzz_element.setOpen(false);
      }
      else if (millis() - m_Start < 1000)
      {
        led_element.setOpen(true);
        buzz_element.setOpen(true);
      }
      else if (millis() - m_Start > 1000)
      {
        led_element.setOpen(false);
        buzz_element.setOpen(false);
      }
    }
  private:
    static unsigned long m_Start;
};

unsigned long Signal::m_Start = -1000;
