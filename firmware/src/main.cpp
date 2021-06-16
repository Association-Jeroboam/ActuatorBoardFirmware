#include <ch.hpp>
#include <hal.h>
#include <shell.h>
#include "Shell.hpp"
#include "Board.hpp"
#include "Logging.hpp"
#include "BuildConf.hpp"
#include "Dynamixel2Arduino.h"
#include "PliersManager.hpp"

static THD_WORKING_AREA(waShellThread, SHELL_WA_SIZE);


int main() {
    halInit();
    chSysInit();
    Board::init();
    Logging::init();
    Logging::println("Starting up");
    Board::Com::CANBus::init();
    Board::Com::DxlServo::init();
    Board::Com::I2CBus::init();
    Board::Actuators::init();
    shellInit();


    chThdCreateStatic(waShellThread, sizeof(waShellThread), NORMALPRIO,
                      shellThread, (void*)&shell_cfg);;
    chThdSleepMilliseconds(20);
    PliersManager::instance()->start(NORMALPRIO);
    while (!chThdShouldTerminateX()) {
        palToggleLine(LED_LINE);
        chThdSleepMilliseconds(20);
    }
    Logging::println("Shutting down");
}
