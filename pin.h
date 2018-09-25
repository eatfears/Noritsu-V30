#pragma once

#include "pinout.h"

class Pin
{
  public:
    Pin(int pin) : m_PinNum(pin) {};
  protected:
    int m_PinNum;
    bool m_Init = false;

    void _init(int mode)
    {
      if (!m_Init)
      {
        pinMode(m_PinNum, mode);
        m_Init = true;
      }
      else
      {
        logger.error("Pin " + String(m_PinNum)  + " already initialized");
      }
    }
};

class OutputPin : public Pin
{
  public:
    OutputPin(int pin) : Pin(pin) {};

    void init()
    {
      _init(OUTPUT);
    };

    void set(int value)
    {
      if (m_Init)
      {
        if (value != m_Value)
        {
          digitalWrite(m_PinNum, value);
          m_Value = value;
        }
      }
      else
      {
        logger.error("Pin " + String(m_PinNum)  + " not initialized");
      }
    }
  private:
    int m_Value = 0;
};

class InputPin : public Pin
{
  public:
    InputPin(int pin) : Pin(pin) {};

    void init()
    {
      _init(INPUT_PULLUP);
    }

    int get()
    {
      if (m_Init)
      {
        return digitalRead(m_PinNum);
      }
      else
      {
        logger.error("Pin " + String(m_PinNum)  + " not initialized");
        return 0;
      }
    }
};

class Sensor
{
  public:
    Sensor(int pin, bool inverted = false)
      : m_Pin(pin), m_Inverted(inverted) {}

    void init()
    {
      m_Pin.init();
    }

    bool isOpen() const
    {
      return m_Inverted^m_Pin.get() == HIGH;
    }

    bool isInverted() {
      return m_Inverted;
    }

  private:
    InputPin m_Pin;
    bool m_Inverted;
};

class Element
{
  public:
    Element(int pin, bool inverted = false, bool default_value = false)
      : m_Pin(pin), m_Inverted(inverted), m_DefaultValue(default_value) {}

    void init()
    {
      m_Pin.init();
      setOpen(m_DefaultValue);
    }

    void setOpen(bool value)
    {
      m_Pin.set(m_Inverted^value == HIGH);
    }
  private:
    OutputPin m_Pin;
    bool m_Inverted;
    bool m_DefaultValue;
};
