#include "Board.hpp"
#include "board.h"
#include "ch.hpp"
#include "hal.h"
#include "BuildConf.hpp"
#include "Logging.hpp"
#include "CanRxThread.hpp"

CanRxThread canRxThread;

CANConfig canConfig = {
        .btr = 0x00050007,
//    .mcr = 0,
};

void Board::init() {

}

void Board::Com::CANBus::init(){
    palSetLineMode(CAN_TX_PIN, CAN_TX_PIN_MODE);
    palSetLineMode(CAN_RX_PIN, CAN_RX_PIN_MODE);
    canStart(&CAN_DRIVER, &canConfig);
    canRxThread.start(NORMALPRIO);
    // let Threads finish initialization
    chThdYield();
}

}
