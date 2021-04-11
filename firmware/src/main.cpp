#include <ch.hpp>
#include <hal.h>
#include "Board.hpp"
#include "Logging.hpp"
#include "BuildConf.hpp"
#include "Dynamixel2Arduino.h"



int main() {
    halInit();
    chSysInit();
    Board::init();
    Logging::init();
    Logging::println("Starting up");

    Dynamixel2Arduino actuator_bus(&XL320_DRIVER);
    actuator_bus.begin(1000000);
    uint8_t id = 21;
    bool ret;

    actuator_bus.setPortProtocolVersion(2.0);
    while (!chThdShouldTerminateX()) {


        ret = actuator_bus.setGoalPosition(id, 0, UNIT_DEGREE);
        chThdSleepMilliseconds(1000);
        float position = actuator_bus.getPresentPosition(id, UNIT_DEGREE);
        palSetLine(LED_LINE);
        Logging::println("position: %f, success %d", position, ret);
        ret = actuator_bus.setGoalPosition(id, 90, UNIT_DEGREE);
        chThdSleepMilliseconds(1000);
        position = actuator_bus.getPresentPosition(id, UNIT_DEGREE);
        palClearLine(LED_LINE);
        Logging::println("position: %f, success %d", position, ret);

    }

    Logging::println("Shutting down");
}
