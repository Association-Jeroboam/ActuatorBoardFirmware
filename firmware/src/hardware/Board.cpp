#include "Board.hpp"
#include "board.h"
#include "ch.hpp"
#include "hal.h"
#include "BuildConf.hpp"
#include "Logging.hpp"
#include "CanRxThread.hpp"
#include "CanTxThread.hpp"

CanRxThread canRxThread;
CanTxThread canTxThread;

CANConfig canConfig = {
    .mcr = 0,
    .btr = 0x00050007,
};

void Board::init() {
    // XL320 serial driver
    palSetLineMode(XL320_DATA_PIN, PAL_MODE_ALTERNATE(7));
    palSetLineMode(XL320_DIR_PIN, PAL_MODE_OUTPUT_PUSHPULL);
}

void Board::Com::CANBus::init(){
    palSetLineMode(CAN_TX_PIN, CAN_TX_PIN_MODE);
    palSetLineMode(CAN_RX_PIN, CAN_RX_PIN_MODE);
    canStart(&CAN_DRIVER, &canConfig);
    canTxThread.start(NORMALPRIO);
    canRxThread.start(NORMALPRIO+1);
    // let Threads finish initialization
    chThdYield();
}

bool Board::Com::CANBus::send(canFrame_t canData){
    return canTxThread.send(canData);
}

void Board::Com::CANBus::registerListener(CanListener *listener) {
    canRxThread.registerListener(listener);
}
