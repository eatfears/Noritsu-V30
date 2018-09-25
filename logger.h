#pragma once

#define LOGGER_FUNCTION(func) \
  void func(String s) { log(s, #func); } \
  void func(int i){ func(String(i)); }

class Logger
{
  public:
    void init()
    {
      Serial.begin(115200); //300 600 1200 2400 4800 9600 14400 19200 28800 38400 57600 115200
    }

    LOGGER_FUNCTION(debug)
    LOGGER_FUNCTION(info)
    LOGGER_FUNCTION(warning)
    LOGGER_FUNCTION(error)
    LOGGER_FUNCTION(critical)

  private:
    void log(const String &s, const String &level)
    {
      Serial.println("Logger " + level + ": " + s);
    }
};

Logger logger;
