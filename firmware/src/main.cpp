#include <ch.hpp>
#include <hal.h>
#include <shell.h>
#include "Shell.hpp"
#include "Board.hpp"
#include "Logging.hpp"
#include "BuildConf.hpp"
#include "Dynamixel2Arduino.h"
#include "PliersManager.hpp"



int main() {
    halInit();
    chSysInit();
    Board::init();
    Logging::init();
    Logging::println("Starting up");
    shellInit();
    Board::Com::CANBus::init();
    Board::Com::DxlServo::init();


    PliersManager::instance()->start(NORMALPRIO);
    chThdCreateFromHeap(NULL, SHELL_WA_SIZE,
                        "shell", NORMALPRIO + 1,
                        shellThread, (void*)&shell_cfg);
    chThdSleepMilliseconds(20);
    while (!chThdShouldTerminateX()) {
        palToggleLine(LED_LINE);
        chThdSleepMilliseconds(20);
    }
    Logging::println("Shutting down");
}
