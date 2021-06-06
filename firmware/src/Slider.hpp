#ifndef __SLIDER_HPP__
#define __SLIDER_HPP__
#include <inttypes.h>

class Slider{
public:
    Slider(uint8_t id);
    void init();
    void goToDistance(int16_t distance);
    void setPIDGains(uint16_t p, uint16_t i, uint16_t d);

private:
    uint8_t m_id;
};


#endif //__SLIDER_HPP__
