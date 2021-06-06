#include "Board.hpp"
#include "Logging.hpp"
#include "PliersManager.hpp"
#include <new>

using namespace Board::Com::DxlServo;

PliersManager PliersManager::s_instance;

PliersManager* PliersManager::instance() {
    return &s_instance;
}

PliersManager::PliersManager() {
    chFifoObjectInit(&m_orderQueue, ORDER_DATA_SIZE, ORDER_QUEUE_LEN,  m_orderBuffer, m_msgBuffer);
    for(uint8_t id = 0; id < PLIERS_MANAGER_MAX_PLIERS_COUNT; id++) {
        m_pliers[id] = Board::Com::DxlServo::getPliersByID((enum pliersID)id);
        if(!m_pliers[id]) {
            Logging::println("Pliers %d Not found!", id);
        }
    }
}

void PliersManager::main() {
    setName("Pliers Manager");

    for(uint8_t id = 0; id < PLIERS_MANAGER_MAX_PLIERS_COUNT; id++) {
        if(m_pliers[id]) {
            m_pliers[id]->deactivate();
        }
    }
    Board::Com::DxlServo::disengagePliersBlock();

    Board::Com::CANBus::registerListener(this);

    while (!shouldTerminate()){
        canFrame_t * frame;
        chFifoReceiveObjectTimeout(&m_orderQueue, (void **)&frame, TIME_INFINITE);
        switch (frame->ID) {
            case CAN_PLIERS_ID:
                if( frame->data.pliersData.plierID < PLIERS_MANAGER_MAX_PLIERS_COUNT) {
                    switch (frame->data.pliersData.state) {
                        case PLIERS_OPEN:
                            m_pliers[frame->data.pliersData.plierID]->deactivate();
                        case PLIERS_CLOSE:
                            m_pliers[frame->data.pliersData.plierID]->activate();
                    }
                    Logging::println("[PliersManager] Order sent. ID %u, state %u", frame->data.pliersData.plierID, frame->data.pliersData.state);

                } else {
                    Logging::println("[PliersManager] received order for unknown pliers");
                }
                break;
            case CAN_PLIERS_BLOCK_ID:
                if(frame->data.pliersBlockData.state == 0){
                    Board::Com::DxlServo::disengagePliersBlock();
                } else {
                    Board::Com::DxlServo::engagePliersBlock();
                }
                break;
            case CAN_ARMS_ID:
                break;
            case CAN_SLIDERS_ID:
                break;
            default:
                Logging::println("[PliersManager] Wrong ID received");
        }



        chFifoReturnObject(&m_orderQueue, frame);
    }
}

void PliersManager::processFrame(canFrame_t frame){

    if(frame.ID == CAN_PLIERS_ID       ||
       frame.ID == CAN_PLIERS_BLOCK_ID ||
       frame.ID == CAN_ARMS_ID         ||
       frame.ID == CAN_SLIDERS_ID        ) {
        canFrame_t *pushed_frame = (canFrame_t *) chFifoTakeObjectTimeout(&m_orderQueue, TIME_IMMEDIATE);
        if ( pushed_frame == NULL) {
            Logging::println("[PliersManager] Queue full!");
        } else {
            *pushed_frame = frame;
            chFifoSendObject(&m_orderQueue, pushed_frame);
        }
    }
}
