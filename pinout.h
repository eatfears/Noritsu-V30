#pragma once

#define LEADER_IN_PIN               10
#define FILM_L_IN_PIN               8
#define FILM_R_IN_PIN               6
#define PERF_L_IN_PIN               4
#define PERF_R_IN_PIN               0
#define COVER_IN_PIN                12
#define DRIVE_IN_PIN                3


#define LEADER_OUT_PIN              11
#define FILM_L_OUT_PIN              9
#define FILM_R_OUT_PIN              7
#define PERF_L_OUT_PIN              5
#define PERF_R_OUT_PIN              1
#define COVER_OUT_PIN               13
#define COVER_LOCK_OUT_PIN          14
#define PRESSURE_SOLENOID_OUT_PIN   15
#define PRESSURE_SOLENOID_R_OUT_PIN 16

#define LED_OUT_PIN                 17
#define BUZZ_OUT_PIN                2


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
    case DRIVE_IN_PIN: return F("Drive"); break;

    case LEADER_OUT_PIN: return F("Leader"); break;
    case FILM_L_OUT_PIN: return F("Film L"); break;
    case FILM_R_OUT_PIN: return F("Film R"); break;
    case PERF_L_OUT_PIN: return F("Perf L"); break;
    case PERF_R_OUT_PIN: return F("Perf R"); break;
    case COVER_OUT_PIN: return F("Cover"); break;
    case COVER_LOCK_OUT_PIN: return F("Cover lock"); break;
    case PRESSURE_SOLENOID_OUT_PIN: return F("Pressure solenoid"); break;
    case PRESSURE_SOLENOID_R_OUT_PIN: return F("Pressure solenoid R"); break;

    case LED_OUT_PIN: return F("Led"); break;
    case BUZZ_OUT_PIN: return F("Buzz"); break;
    default: return F("Unknown pin"); break;
  }
}
