#pragma once
#include "CanProtocol.hpp"
#include "CanListener.hpp"
#include "Dynamixel2Arduino.h"
#include "Pliers.hpp"

namespace Board {
    void init();

    namespace Com {
        namespace CANBus {
            void init();
            bool send(canFrame_t canData);
            void registerListener(CanListener * listener);
        }

        namespace DxlServo {
            void init();
            Dynamixel2Arduino * getBus();

        }

        namespace I2CBus {
            void init();
            bool transmit(uint8_t addr, uint8_t *txData, uint8_t txLen, uint8_t *rxData, uint8_t rxLen);
            bool receive(uint8_t addr, uint8_t *rxData, uint8_t rxLen);
        }
    }

    namespace Actuators {
        void init();
        Pliers* getPliersByID(enum pliersID ID);
        void engagePliersBlock();
        void disengagePliersBlock();
        void elevatorSetHeigth(int16_t height);
        void setPwmServo(uint8_t channel, uint16_t value);
    }
}