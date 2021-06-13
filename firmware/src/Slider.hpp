#pragma once
#include <inttypes.h>
#include "Servo.hpp"

class Slider: public Servo{
public:
    Slider(uint8_t id);
    void init();
    void goToDistance(int16_t distance);
    void setPIDGains(uint16_t p, uint16_t i, uint16_t d);

};
