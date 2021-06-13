#include "Board.hpp"
#include "board.h"
#include "ch.hpp"
#include "hal.h"
#include "BuildConf.hpp"
#include "Logging.hpp"
#include "CanRxThread.hpp"
#include "CanTxThread.hpp"
#include "Pliers.hpp"
#include "DxlPliers.hpp"
#include "Slider.hpp"

CanRxThread canRxThread;
CanTxThread canTxThread;
static DxlPliers s_pliersFrontFarLeft(PLIERS_FRONT_FAR_LEFT_ID);
static DxlPliers s_pliersFrontLeft(PLIERS_FRONT_LEFT_ID);
static DxlPliers s_pliersFrontRight(PLIERS_FRONT_RIGHT_ID);
static DxlPliers s_pliersFrontFarRight(PLIERS_FRONT_FAR_RIGHT_ID);
static DxlPliers s_pliersRearFarRight(PLIERS_REAR_FAR_RIGHT_ID);
static DxlPliers s_pliersRearRight(PLIERS_REAR_RIGHT_ID);
static DxlPliers s_pliersRearMiddle(PLIERS_REAR_MIDDLE_ID);
static DxlPliers s_pliersRearLeft(PLIERS_REAR_LEFT_ID);
static DxlPliers s_pliersRearFarLeft(PLIERS_REAR_FAR_LEFT_ID);

static DxlPliers s_pliersBlockLeft(PLIERS_BLOCK_LEFT_ID, PLIERS_BLOCK_LEFT_IDLE_ANGLE, PLIERS_BLOCK_LEFT_ACTIVE_ANGLE);
static DxlPliers s_pliersBlockRight(PLIERS_BLOCK_RIGHT_ID, PLIERS_BLOCK_RIGHT_IDLE_ANGLE, PLIERS_BLOCK_RIGHT_ACTIVE_ANGLE);

static Slider s_elevator(SLIDER_ELEVATOR_ID);

constexpr uint32_t DXL_BAUDRATE = 1000000;
Dynamixel2Arduino * dxlBus;

CANConfig canConfig = {
    .mcr = 0,
    .btr = 0x00050007,
};

void Board::init() {
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

void Board::Com::DxlServo::init(){
    palSetLineMode(XL320_DATA_PIN, PAL_MODE_ALTERNATE(7));
    palSetLineMode(XL320_DIR_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    dxlBus = new Dynamixel2Arduino(&XL320_DRIVER);
    dxlBus->begin(DXL_BAUDRATE);
    dxlBus->setPortProtocolVersion(2.0);

    //init pliers
    s_pliersFrontFarLeft.init();
    s_pliersFrontLeft.init();
    s_pliersFrontRight.init();
    s_pliersFrontFarRight.init();
    s_pliersRearFarRight.init();
    s_pliersRearRight.init();
    s_pliersRearMiddle.init();
    s_pliersRearLeft.init();
    s_pliersRearFarLeft.init();

    //init pliers block
    s_pliersBlockLeft.init();
    s_pliersBlockRight.init();

    // init sliders
    s_elevator.init();
    s_elevator.setPIDGains(640, 50, 4000);

}

Dynamixel2Arduino * Board::Com::DxlServo::getBus(){
    return dxlBus;
}

Pliers*  Board::Com::DxlServo::getPliersByID(enum pliersID ID){

    switch (ID) {
        case PLIERS_FRONT_FAR_LEFT: return &s_pliersFrontFarLeft;
        case PLIERS_FRONT_LEFT: return &s_pliersFrontLeft;
        case PLIERS_FRONT_RIGHT: return &s_pliersFrontRight;
        case PLIERS_FRONT_FAR_RIGHT: return &s_pliersFrontFarRight;
        case PLIERS_REAR_FAR_RIGHT: return &s_pliersRearFarRight;
        case PLIERS_REAR_RIGHT: return &s_pliersRearRight;
        case PLIERS_REAR_MIDDLE: return &s_pliersRearMiddle;
        case PLIERS_REAR_LEFT: return &s_pliersRearLeft;
        case PLIERS_REAR_FAR_LEFT: return &s_pliersRearFarLeft;
    }
    return nullptr;
}
void Board::Com::DxlServo::engagePliersBlock() {
    s_pliersBlockLeft.activate();
    s_pliersBlockRight.activate();
}

void Board::Com::DxlServo::disengagePliersBlock() {
    s_pliersBlockLeft.deactivate();
    s_pliersBlockRight.deactivate();
}

void Board::Com::DxlServo::elevatorSetHeigth(int16_t height) {
    s_elevator.goToDistance(height);
}
