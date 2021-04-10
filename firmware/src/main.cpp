#include <ch.hpp>
#include <hal.h>
#include "Board.hpp"
#include "Logging.hpp"

int main() {
    halInit();
    chSysInit();
    Board::init();
    Logging::init();
    Logging::println("Starting up");
    Board::Com::CANBus::init();


    while (!chThdShouldTerminateX()) {
        canFrame_t canMsg = CanProtocol::createFrame(CAN_CURRENT_POSE_ID, (int16_t)50, (int16_t)-1000, (float)3.1415);
        Board::Com::CANBus::send(canMsg);

        canMsg = CanProtocol::createFrame(CAN_ACTION_DONE_ID);
        Board::Com::CANBus::send(canMsg);

        canMsg = CanProtocol::createFrame(CAN_COLOR_ID, (uint8_t)126, (uint8_t)15, (uint8_t)243);
        Board::Com::CANBus::send(canMsg);

        canMsg = CanProtocol::createFrame(CAN_PLIERS_ID, (uint8_t) 7, (uint8_t)9);
        Board::Com::CANBus::send(canMsg);

        canMsg = CanProtocol::createFrame(CAN_SLIDERS_ID, (uint8_t) 7, (uint16_t)9);
        Board::Com::CANBus::send(canMsg);
        chThdSleepMilliseconds(100);
        palToggleLine(LINE_LED_GREEN);
    }

    Logging::println("Shutting down");
}
