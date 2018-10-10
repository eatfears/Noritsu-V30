#pragma once

#define FILM_L_IN_PIN               8
#define FILM_R_IN_PIN               6
#define PERF_L_IN_PIN               4
#define PERF_R_IN_PIN               12
#define DRIVE_IN_PIN                3

#define LEADER_IN_PIN               12
#define COVER_IN_PIN                11


#define FILM_L_OUT_PIN              9
#define FILM_R_OUT_PIN              7
#define PERF_L_OUT_PIN              5
#define PERF_R_OUT_PIN              13

#define LEADER_OUT_PIN              15
#define COVER_OUT_PIN               14
#define COVER_LOCK_OUT_PIN          7
#define PRESSURE_SOLENOID_L_OUT_PIN 5
#define PRESSURE_SOLENOID_R_OUT_PIN 6

#define REPL_CD_OUT_PIN             1
#define REPL_BL_OUT_PIN             2
#define REPL_FIX_OUT_PIN            3
#define REPL_STB_OUT_PIN            4

#define LED_OUT_PIN                 17
#define BUZZ_OUT_PIN                2

#define TEST_OUT_PIN                10


String pinNames(int pin)
{
  switch (pin)
  {
    case FILM_L_IN_PIN: return F("Film L"); break;
    case FILM_R_IN_PIN: return F("Film R"); break;
    case PERF_L_IN_PIN: return F("Perf L"); break;
    case PERF_R_IN_PIN: return F("Perf R"); break;
    case DRIVE_IN_PIN: return F("Drive"); break;

    case FILM_L_OUT_PIN: return F("Film L"); break;
    case FILM_R_OUT_PIN: return F("Film R"); break;
    case PERF_L_OUT_PIN: return F("Perf L"); break;
    case PERF_R_OUT_PIN: return F("Perf R"); break;

    case BUZZ_OUT_PIN: return F("Buzz"); break;

    case TEST_OUT_PIN: return F("Test 10"); break;

    default: return String(F("Unknown uno pin ")) + String(pin); break;
  }
}

String i2cPinNames(int pin)
{
  switch (pin)
  {
    case LEADER_IN_PIN: return F("Leader"); break;
    case COVER_IN_PIN: return F("Cover"); break;

    case LEADER_OUT_PIN: return F("Leader"); break;
    case COVER_OUT_PIN: return F("Cover"); break;
    case COVER_LOCK_OUT_PIN: return F("Cover lock"); break;
    case PRESSURE_SOLENOID_L_OUT_PIN: return F("Pressure solenoid L"); break;
    case PRESSURE_SOLENOID_R_OUT_PIN: return F("Pressure solenoid R"); break;

    case REPL_CD_OUT_PIN: return F("Replenisher CD"); break;
    case REPL_BL_OUT_PIN: return F("Replenisher BL"); break;
    case REPL_FIX_OUT_PIN: return F("Replenisher FIX"); break;
    case REPL_STB_OUT_PIN: return F("Replenisher STB"); break;

    case LED_OUT_PIN: return F("Led"); break;

    default: return String(F("Unknown i2c pin ")) + String(pin); break;
  }
}
