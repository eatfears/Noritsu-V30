#pragma once

#include "pin.h"


Element leader_element(LEADER_OUT_PIN, true);
Element film_l_element(FILM_L_OUT_PIN);
Element film_r_element(FILM_R_OUT_PIN);
Element perf_l_element(PERF_L_OUT_PIN);
Element perf_r_element(PERF_R_OUT_PIN);
Element cover_lock_element(COVER_LOCK_OUT_PIN);
Element pressure_solenoid_element(PRESSURE_SOLENOID_OUT_PIN);

Element led_element(LED_OUT_PIN);
Element buzz_element(BUZZ_OUT_PIN);
