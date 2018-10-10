#pragma once

#include "elements.h"

class Pump : public Element
{
  public:
    Pump(int pin, int timeout) : Element(pin, true, false, false), m_Timeout(timeout) {}

    void fire()
    {
      logger.info(m_Pin->name() + F(" fire"));
      setOpen(true);

      m_FireTime = millis();
    }

    void checkClose()
    {
      if (m_Opened && millis() - m_FireTime > m_Timeout)
      {
        logger.info(m_Pin->name() + F(" fire stop"));
        setOpen(false);
      }
    }

  private:
    int m_Timeout;
    unsigned long m_FireTime;
};
