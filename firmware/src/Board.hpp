#pragma once
#include "CanProtocol.hpp"

namespace Board {
    void init();

    namespace Com {
        namespace CANBus {
            void init();
            bool send(canFrame_t canData);
        }
    }
}