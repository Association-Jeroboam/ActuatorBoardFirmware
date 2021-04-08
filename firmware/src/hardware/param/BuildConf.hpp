#pragma once

#include "Board.hpp"
#include "board.h"

#define LOGGING_DRIVER SD2
#define SHELL_DRIVER LOGGING_DRIVER

#define LED_LINE LINE_LED_GREEN

#define CAN_DRIVER CAND1

#define CAN_TX_PIN      LINE_ARD_D2
#define CAN_TX_PIN_MODE PAL_MODE_ALTERNATE(9)
#define CAN_RX_PIN      LINE_ARD_D10
#define CAN_RX_PIN_MODE PAL_MODE_ALTERNATE(9)

