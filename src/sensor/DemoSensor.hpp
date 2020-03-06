#ifndef DEMO_SENSOR_HPP
#define DEMO_SENSOR_HPP
//#include "common.hpp"
#include "Sensor.hpp"
#include <stdlib.h>

class DemoSensor : public Sensor
{
private:
    sensorData data;
    
    float randomFloat(float min, float max);
public:
    DemoSensor();
    ~DemoSensor();
    void handle();
    sensorData getData();
    void startMeasurement();
    boolean measurementStatus();
};
#endif
