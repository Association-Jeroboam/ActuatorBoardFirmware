#include "Slider.hpp"
#include "Board.hpp"
#include "BuildConf.hpp"
#include "ch.hpp"
#include "Logging.hpp"

Slider::Slider(uint8_t id): Servo(id){}

void Slider::init(){
    Logging::println("[Slider] init %d", m_id);
    Dynamixel2Arduino * bus = Board::Com::DxlServo::getBus();
    bus->ledOff(m_id);
    bus->torqueOff(m_id);
    chThdSleepMilliseconds(20);

    // Configure actuator here
    bus->setOperatingMode(m_id, OP_EXTENDED_POSITION);
    // Configuration done
    bus->torqueOn(m_id);
    bus->ledOn(m_id);
    float pos = bus->getPresentPosition(m_id, UNIT_DEGREE);
    Logging::println("pos %f", pos);
}

void Slider::goToDistance(int16_t distance){
    Dynamixel2Arduino * bus = Board::Com::DxlServo::getBus();
    bus->setGoalPosition(m_id, (float)distance / SLIDER_ELEVATOR_DISTANCE_PER_TURN * 360., UNIT_DEGREE);
}

void Slider::setPIDGains(uint16_t p, uint16_t i, uint16_t d){
    Dynamixel2Arduino * bus = Board::Com::DxlServo::getBus();
    bus->setPositionPIDGain(m_id, p, i, d);
}
