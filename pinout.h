#pragma once

#define LEADER_IN_PIN               7
#define FILM_L_IN_PIN               2
#define FILM_R_IN_PIN               3
#define PERF_L_IN_PIN               4
#define PERF_R_IN_PIN               5
#define COVER_IN_PIN                6


#define LEADER_OUT_PIN              11
#define FILM_L_OUT_PIN              12
#define FILM_R_OUT_PIN              13
#define PERF_L_OUT_PIN              14
#define PERF_R_OUT_PIN              15
#define COVER_OUT_PIN               20
#define COVER_LOCK_OUT_PIN          16
#define PRESSURE_SOLENOID_OUT_PIN   17
#define PRESSURE_SOLENOID_R_OUT_PIN 17

#define LED_OUT_PIN                 18
#define BUZZ_OUT_PIN                19


String pinNames(int pin)
{
  switch (pin)
  {
    case LEADER_IN_PIN: return F("Leader"); break;
    case FILM_L_IN_PIN: return F("Film L"); break;
    case FILM_R_IN_PIN: return F("Film R"); break;
    case PERF_L_IN_PIN: return F("Perf L"); break;
    case PERF_R_IN_PIN: return F("Perf R"); break;
    case COVER_IN_PIN: return F("Cover"); break;

    case LEADER_OUT_PIN: return F("Leader"); break;
    case FILM_L_OUT_PIN: return F("Film L"); break;
    case FILM_R_OUT_PIN: return F("Film R"); break;
    case PERF_L_OUT_PIN: return F("Perf L"); break;
    case PERF_R_OUT_PIN: return F("Perf R"); break;
    case COVER_OUT_PIN: return F("Cover"); break;
    case COVER_LOCK_OUT_PIN: return F("Cover lock"); break;
    case PRESSURE_SOLENOID_OUT_PIN: return F("Pressure solenoid"); break;

    case LED_OUT_PIN: return F("Led"); break;
    case BUZZ_OUT_PIN: return F("Buzz"); break;
    default: return F("Unknown pin"); break;
  }
}
