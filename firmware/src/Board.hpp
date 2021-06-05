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
            Pliers* getPliersByID(enum pliersID ID);
        }
    }
}