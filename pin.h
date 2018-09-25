#pragma once

#include "pinout.h"

class Pin
{
  public:
    Pin(int pin) : m_PinNum(pin) {};

    String name() const
    {
      return pinNames(m_PinNum);
    }
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
        logger.error("Pin " + String(m_PinNum)  + F(" already initialized"));
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
        digitalWrite(m_PinNum, value);
      }
      else
      {
        logger.error("Pin " + String(m_PinNum)  + F(" not initialized"));
      }
    }
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
        logger.error("Pin " + String(m_PinNum)  + F(" not initialized"));
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
      bool opened = m_Inverted ^ m_Pin.get() == HIGH;
      if (opened != m_Opened)
      {
        m_Opened = opened;
        m_Opened ? logger.debug(m_Pin.name() + F(" sensor is opened")) : logger.debug(m_Pin.name() + F(" sensor is closed"));
      }
      return opened;
    }

  private:
    InputPin m_Pin;
    bool m_Inverted;
    mutable int m_Opened = -1;
};

class Element
{
  public:
    Element(int pin, bool inverted = false, bool default_value = false)
      : m_Pin(pin), m_Inverted(inverted), m_DefaultValue(default_value), m_Opened(!default_value) {}

    void init()
    {
      m_Pin.init();
      setOpen(m_DefaultValue);
    }

    void setOpen(bool opened)
    {
      if (opened != m_Opened)
      {
        m_Pin.set(m_Inverted ^ opened == HIGH);
        m_Opened = opened;
        m_Opened ? logger.debug(m_Pin.name() + F(" element is opened")) : logger.debug(m_Pin.name() + F(" element is closed"));
      }
    }
  private:
    OutputPin m_Pin;
    bool m_Inverted;
    bool m_DefaultValue;
    bool m_Opened;
};
