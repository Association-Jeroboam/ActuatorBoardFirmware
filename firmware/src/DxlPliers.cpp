#include "DxlPliers.hpp"
#include "ch.hpp"
#include "Board.hpp"
#include "Logging.hpp"

DxlPliers::DxlPliers(uint8_t id, float idleAngle, float activeAngle){
    m_id = id;
    m_idleAngle = idleAngle;
    m_activeAngle = activeAngle;
}

void DxlPliers::init(){
    Logging::println("[DxlPliers] init %d", m_id);
    Dynamixel2Arduino * bus = Board::Com::DxlServo::getBus();
    bus->ledOff(m_id);
    chThdSleepMilliseconds(200);

    bus->torqueOff(m_id);
    // Configure actuator here
    bus->setOperatingMode(m_id, OP_POSITION);
    bus->setPositionPIDGain(m_id, DXL_PLIERS_P_GAIN, DXL_PLIERS_I_GAIN, DXL_PLIERS_D_GAIN);
    // Configuration done
    bus->torqueOn(m_id);
    bus->ledOn(m_id);
    bus->setTorqueLimit(m_id, DXL_PLIERS_TORQUE_LIMIT, UNIT_PERCENT);
    bus->setGoalPosition(m_id, m_idleAngle);
}

void DxlPliers::open() {
    Board::Com::DxlServo::getBus()->setGoalPosition(m_id, m_idleAngle, UNIT_DEGREE);
}

void DxlPliers::close() {
    Board::Com::DxlServo::getBus()->setGoalPosition(m_id, m_activeAngle, UNIT_DEGREE);
}
