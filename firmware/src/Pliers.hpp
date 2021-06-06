#pragma once
#include "Servo.hpp"
#include "Dynamixel2Arduino.h"

class Pliers : public Servo {
public:
    virtual void init() = 0;
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual void setAngle(int16_t angle);

};
