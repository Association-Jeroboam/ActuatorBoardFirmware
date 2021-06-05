#include "Servo.hpp"

void Servo::setActiveAngle(float activeAngle) {
    m_activeAngle = activeAngle;
}

void Servo::setIdleAngle(float idleAngle) {
    m_idleAngle = idleAngle;
}
