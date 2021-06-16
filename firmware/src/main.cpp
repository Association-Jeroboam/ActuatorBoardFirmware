#include <ch.hpp>
#include <hal.h>
#include <shell.h>
#include "Shell.hpp"
#include "Board.hpp"
#include "Logging.hpp"
#include "BuildConf.hpp"
#include "Dynamixel2Arduino.h"
#include "PliersManager.hpp"
#include "PCA9635.h"
#include "Adafruit_PWMServoDriver.h"
#include "hal_pal.h"

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


    PliersManager::instance()->start(NORMALPRIO);
    chThdCreateFromHeap(NULL, SHELL_WA_SIZE,
                        "shell", NORMALPRIO + 1,
                        shellThread, (void*)&shell_cfg);
    chThdSleepMilliseconds(20);

    uint8_t id = 4;
    while (!chThdShouldTerminateX()) {
        palToggleLine(LED_LINE);
        chThdSleepMilliseconds(200);
        palToggleLine(LED_LINE);
        chThdSleepMilliseconds(200);
    }
    Logging::println("Shutting down");
}
