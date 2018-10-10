#pragma once

#include "pin.h"


Sensor leader_sensor(LEADER_IN_PIN, true);

Sensor film_l_sensor(FILM_L_IN_PIN, false);
Sensor film_r_sensor(FILM_R_IN_PIN, false);
Sensor perf_l_sensor(PERF_L_IN_PIN, false);
Sensor perf_r_sensor(PERF_R_IN_PIN, false);

Sensor drive_sensor(DRIVE_IN_PIN, false);
Sensor cover_sensor(COVER_IN_PIN, true, true);
