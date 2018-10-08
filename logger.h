#pragma once

enum logger_level
{
  trace,
  debug,
  info,
  notice,
  warning,
  error,
  critical,
  alert
};
static logger_level logLevel = debug;


String levelToString(logger_level level)
{
  switch (level)
  {
    case trace: return F("trace");
    case debug: return F("debug");
    case info: return F("info");
    case notice: return F("notice");
    case warning: return F("warning");
    case error: return F("error");
    case critical: return F("critical");
    case alert: return F("alert");
  }
  return F("logger");
}


#define LOGGER_FUNCTION(func) \
  void func(const String &s) { log(s, logger_level::func); } \
  void func(int i){ func(String(i)); }

class Logger
{
  public:
    void init()
    {
      Serial.begin(115200); //300 600 1200 2400 4800 9600 14400 19200 28800 38400 57600 115200
    }

    LOGGER_FUNCTION(trace)
    LOGGER_FUNCTION(debug)
    LOGGER_FUNCTION(info)
    LOGGER_FUNCTION(notice)
    LOGGER_FUNCTION(warning)
    LOGGER_FUNCTION(error)
    LOGGER_FUNCTION(critical)
    LOGGER_FUNCTION(alert)

  private:
    void log(const String &s, logger_level level)
    {
      if (level >= logLevel)
      {
        Serial.println(levelToString(level) + F(": ") + s);
      }
    }
};

Logger logger;
