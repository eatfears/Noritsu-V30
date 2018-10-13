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
  void func(int i){ func(String(i)); } \
  void func(unsigned long i){ func(String(i)); }

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
        Serial.println(timeToString(millis()) + String(F(". ")) + levelToString(level) + String(F(": ")) + s);
      }
    }

    char* timeToString(unsigned long t)
    {
      static char str[18];
      int ms = t % 1000;
      t = t / 1000;
      long h = t / 3600;
      t = t % 3600;
      int m = t / 60;
      int s = t % 60;
      sprintf(str, "%04ld:%02d:%02d.%03d", h, m, s, ms);
      return str;
    }
};

Logger logger;
