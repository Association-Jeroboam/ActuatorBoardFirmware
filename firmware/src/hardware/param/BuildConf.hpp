#pragma once

#include "ch.hpp"
#include "Board.hpp"
#include "board.h"
#include "hal_serial.h"
#include "LocalMath.hpp"

#define LOGGING_DRIVER SD2
#define SHELL_DRIVER LOGGING_DRIVER

#define LED_LINE LINE_LED_GREEN
#define XL320_DRIVER SD1

#define XL320_DATA_PIN PAL_LINE(GPIOA, 9U)
#define XL320_DIR_PIN LINE_ARD_D12

#define CAN_DRIVER CAND1

#define CAN_TX_PIN      LINE_ARD_D2
#define CAN_TX_PIN_MODE PAL_MODE_ALTERNATE(9)
#define CAN_RX_PIN      LINE_ARD_D10
#define CAN_RX_PIN_MODE PAL_MODE_ALTERNATE(9)

constexpr uint8_t PLIERS_FRONT_FAR_LEFT_ID  = 13; //TODO: CHANGE ME!
constexpr uint8_t PLIERS_FRONT_LEFT_ID      = 14; //TODO: CHANGE ME!
constexpr uint8_t PLIERS_FRONT_RIGHT_ID     = 15; //TODO: CHANGE ME!
constexpr uint8_t PLIERS_FRONT_FAR_RIGHT_ID = 16; //TODO: CHANGE ME!
constexpr uint8_t PLIERS_REAR_FAR_RIGHT_ID  = 0; //TODO: CHANGE ME!
constexpr uint8_t PLIERS_REAR_RIGHT_ID      = 0; //TODO: CHANGE ME!
constexpr uint8_t PLIERS_REAR_MIDDLE_ID     = 0; //TODO: CHANGE ME!
constexpr uint8_t PLIERS_REAR_LEFT_ID       = 0; //TODO: CHANGE ME!
constexpr uint8_t PLIERS_REAR_FAR_LEFT_ID   = 0; //TODO: CHANGE ME!

constexpr uint8_t PLIERS_BLOCK_LEFT_ID    = 24;
constexpr uint8_t PLIERS_BLOCK_LEFT_IDLE_ANGLE = 224;
constexpr uint8_t PLIERS_BLOCK_LEFT_ACTIVE_ANGLE = 148;

constexpr uint8_t PLIERS_BLOCK_RIGHT_ID   = 18;
constexpr uint8_t PLIERS_BLOCK_RIGHT_IDLE_ANGLE = 76;
constexpr uint8_t PLIERS_BLOCK_RIGHT_ACTIVE_ANGLE = 152;

constexpr uint8_t SLIDER_ELEVATOR_ID = 1;
constexpr float   SLIDER_ELEVATOR_DISTANCE_PER_TURN = 15.3 * 2. * M_PI;

