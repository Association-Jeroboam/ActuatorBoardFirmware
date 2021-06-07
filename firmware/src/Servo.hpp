#pragma once
#include <inttypes.h>

class Servo {
public:
    Servo(uint8_t id);

protected:
    uint8_t m_id;

};
