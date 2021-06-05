#pragma once
#include <inttypes.h>

class Servo {
public:
    void setIdleAngle(float idleAngle);
    void setActiveAngle(float activeAngle);


protected:
    uint8_t m_id;
    float m_idleAngle;
    float m_activeAngle;


};
