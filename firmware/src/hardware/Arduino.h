#ifndef ACTIONBOARDFIRMWARE_ARDUINO_H
#define ACTIONBOARDFIRMWARE_ARDUINO_H
#include "ch.hpp"
#include <cstring>
#include <cmath>
#include "Memory.hpp"
using namespace chibios_rt;

#define millis() TIME_I2MS(chVTGetSystemTime())

#endif //ACTIONBOARDFIRMWARE_ARDUINO_H
