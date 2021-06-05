#pragma once
#include "CanProtocol.hpp"
#include "CanListener.hpp"

namespace Board {
    void init();

    namespace Com {
        namespace CANBus {
            void init();
            bool send(canFrame_t canData);
            void registerListener(CanListener * listener);
        }
    }
}