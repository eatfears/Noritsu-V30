#pragma once

#include "pin.h"


Sensor leader_sensor(LEADER_IN_PIN, true);
Sensor film_l_sensor(FILM_L_IN_PIN);
Sensor film_r_sensor(FILM_R_IN_PIN);
Sensor perf_l_sensor(PERF_L_IN_PIN);
Sensor perf_r_sensor(PERF_R_IN_PIN);
Sensor cover_sensor(COVER_IN_PIN);
