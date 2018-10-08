#pragma once

#include "pin.h"


Element leader_element(LEADER_OUT_PIN, true, true);

Element film_l_element(FILM_L_OUT_PIN, false);
Element film_r_element(FILM_R_OUT_PIN, false);
Element perf_l_element(PERF_L_OUT_PIN, false);
Element perf_r_element(PERF_R_OUT_PIN, false);

Element cover_element(COVER_OUT_PIN, true);
Element cover_lock_element(COVER_LOCK_OUT_PIN, true);

Element pressure_solenoid_l_element(PRESSURE_SOLENOID_L_OUT_PIN, true);
Element pressure_solenoid_r_element(PRESSURE_SOLENOID_R_OUT_PIN, true);

Element repl_cd_element(REPL_CD_OUT_PIN, true);
Element repl_bl_element(REPL_BL_OUT_PIN, true);
Element repl_fix_element(REPL_FIX_OUT_PIN, true);
Element repl_stb_element(REPL_STB_OUT_PIN, true);

Element led_element(LED_OUT_PIN, true);
Element buzz_element(BUZZ_OUT_PIN, false);

Element test_element(TEST_OUT_PIN, false);
