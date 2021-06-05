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
            m_pliers[id]->init();
            m_pliers[id]->open();
        }
    }

    Board::Com::CANBus::registerListener(this);

    while (!shouldTerminate()){
        struct pliersData * data;
        chFifoReceiveObjectTimeout(&m_orderQueue, (void **)&data, TIME_INFINITE);
        if(data->plierID < PLIERS_MANAGER_MAX_PLIERS_COUNT) {
            switch (data->state) {
                case PLIERS_OPEN:
                    m_pliers[data->plierID]->open();
                case PLIERS_CLOSE:
                    m_pliers[data->plierID]->close();
            }
            Logging::println("[PliersManager] Order sent. ID %u, state %u", data->plierID, data->state);

        } else {
            Logging::println("[PliersManager] received order for unknown pliers");
        }


        chFifoReturnObject(&m_orderQueue, data);
    }
}

void PliersManager::processFrame(canFrame_t frame){

    if(frame.ID == CAN_PLIERS_ID) {
        struct pliersData *data = (struct pliersData *) chFifoTakeObjectTimeout(&m_orderQueue, TIME_IMMEDIATE);
        if (data == NULL) {
            Logging::println("[PliersManager] Queue full!");
        } else {
            *data = frame.data.pliersData;
            chFifoSendObject(&m_orderQueue, data);
        }
    }
}
