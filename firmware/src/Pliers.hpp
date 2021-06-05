#pragma once
#include "Servo.hpp"
#include "Dynamixel2Arduino.h"

class Pliers : public Servo {
public:
    virtual void init() = 0;
    virtual void open() = 0;
    virtual void close() = 0;

};
