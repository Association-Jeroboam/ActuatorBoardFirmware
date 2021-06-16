#pragma once
#include "Pliers.hpp"


class PwmPliers : public Pliers {
public:
    PwmPliers(uint8_t id, uint8_t channel, float idleAngle, float activeAngle);
    void init() override;
    void activate() override;
    void deactivate() override;
    void setAngle(int16_t angle) override;

protected:
    uint8_t m_channel;

};
