#pragma once

#include "clsPCA9555.h"
#include "Wire.h"
#include "pinout.h"
#include "logger.h"


PCA9555 ioport(0x20);

class Pin
{
  public:
    Pin(int pin) : m_PinNum(pin) {};

    virtual String name() const
    {
      return pinNames(m_PinNum);
    }
  protected:
    int m_PinNum;
    bool m_Init = false;
};

class OutputPin : public Pin
{
  public:
    OutputPin(int pin) : Pin(pin) {};

    virtual void init() = 0;
    virtual void set(int value) = 0;
};

class OutputPinUno : public OutputPin
{
  public:
    OutputPinUno(int pin) : OutputPin(pin) {};

    void init()
    {
      if (!m_Init)
      {
        pinMode(m_PinNum, OUTPUT);
        m_Init = true;
      }
      else
      {
        logger.error("Pin " + String(m_PinNum)  + F(" already initialized"));
      }
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

class OutputPinI2C : public OutputPin
{
  public:
    OutputPinI2C(int pin) : OutputPin(pin) {};

    void init()
    {
      if (!m_Init)
      {
        ioport.pinMode(m_PinNum, OUTPUT);
        m_Init = true;
      }
      else
      {
        logger.error("Pin " + String(m_PinNum)  + F(" I2C 0x20 already initialized"));
      }
    };

    void set(int value)
    {
      if (m_Init)
      {
        ioport.digitalWrite(m_PinNum, value);
      }
      else
      {
        logger.error("Pin " + String(m_PinNum)  + F(" I2C 0x20 not initialized"));
      }
    }

    String name() const
    {
      return i2cPinNames(m_PinNum);
    }
};

class InputPin : public Pin
{
  public:
    InputPin(int pin) : Pin(pin) {};

    virtual void init() = 0;
    virtual int get() = 0;
};

class InputPinUno : public InputPin
{
  public:
    InputPinUno(int pin) : InputPin(pin) {};

    void init()
    {
      if (!m_Init)
      {
        pinMode(m_PinNum, INPUT_PULLUP);
        m_Init = true;
      }
      else
      {
        logger.error("Pin " + String(m_PinNum)  + F(" already initialized"));
      }
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

class InputPinI2C : public InputPin
{
  public:
    InputPinI2C(int pin) : InputPin(pin) {};

    void init()
    {
      if (!m_Init)
      {
        ioport.pinMode(m_PinNum, INPUT);
        m_Init = true;
      }
      else
      {
        logger.error("Pin " + String(m_PinNum)  + F(" I2C 0x20 already initialized"));
      }
    }

    int get()
    {
      if (m_Init)
      {
        return ioport.digitalRead(m_PinNum);
      }
      else
      {
        logger.error("Pin " + String(m_PinNum)  + F(" I2C 0x20 not initialized"));
        return 0;
      }
    }

    String name() const
    {
      return i2cPinNames(m_PinNum);
    }
};

class Sensor
{
  public:
    Sensor(int pin, bool i2c, bool inverted = false, bool logging =  true)
      : m_Inverted(inverted), m_Logging(logging)
    {
      if (i2c)
      {
        m_Pin = new InputPinI2C(pin);
      }
      else
      {
        m_Pin = new InputPinUno(pin);
      }
    }
    ~Sensor()
    {
      delete m_Pin;
    }

    void init()
    {
      m_Pin->init();
    }

    void read()
    {
      bool opened = m_Inverted ^ m_Pin->get() == HIGH;
      if (opened != m_Opened)
      {
        m_Opened = opened;
        if (m_Logging)
        {
          m_Opened ? logger.debug(m_Pin->name() + F(" sensor is opened")) : logger.debug(m_Pin->name() + F(" sensor is closed"));
        }
      }
    }

    bool isOpen() const
    {
      return m_Opened == 1;
    }

  private:
    InputPin *m_Pin;
    bool m_Inverted;
    bool m_Logging;
    int m_Opened = -1;
};

class Element
{
  public:
    Element(int pin, bool i2c, bool inverted = false, bool default_value = false)
      : m_Inverted(inverted), m_DefaultValue(default_value), m_Opened(!default_value)
    {
      if (i2c)
      {
        m_Pin = new OutputPinI2C(pin);
      }
      else
      {
        m_Pin = new OutputPinUno(pin);
      }
    }
    ~Element()
    {
      delete m_Pin;
    }

    void init()
    {
      m_Pin->init();
      setOpen(m_DefaultValue);
    }

    void setOpen(bool opened)
    {
      if (opened != m_Opened)
      {
        m_Pin->set(m_Inverted ^ opened == HIGH);
        m_Opened = opened;
        m_Opened ? logger.debug(m_Pin->name() + F(" element is opened")) : logger.debug(m_Pin->name() + F(" element is closed"));
      }
    }
  protected:
    OutputPin *m_Pin;
    bool m_Inverted;
    bool m_DefaultValue;
    bool m_Opened;
};
