#include "AP_LeakDetector_Digital.h"
#include <AP_HAL/AP_HAL.h>

extern const AP_HAL::HAL& hal;

AP_LeakDetector_Digital::AP_LeakDetector_Digital(AP_LeakDetector &_leak_detector, AP_LeakDetector::LeakDetector_State &_state) :
    AP_LeakDetector_Backend(_leak_detector, _state)
{}

void AP_LeakDetector_Digital::read()
{
    if (leak_detector._pin[state.instance] >= 0) {
        hal.gpio->pinMode(leak_detector._pin[state.instance], HAL_GPIO_INPUT);
        state.sensorPulse= hal.gpio->read(leak_detector._pin[state.instance]) != leak_detector._default_reading[state.instance];
        state.lastPulse = AP_HAL::millis();
        // eg. lastPulse = 12:01:00 (timercount)
        state.status = AP_HAL::millis() > state.lastPulse + LEAK_SENSOR_DELAY;
        //  status true only when  12:01:01  
    } else {
        state.status = false;
    }
  
}
