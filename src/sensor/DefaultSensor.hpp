#ifndef DEFAULT_SENSOR_HPP
#define DEFAULT_SENSOR_HPP
//#include "common.hpp"
#include "Sensor.hpp"
#include <stdlib.h>

class DefaultSensor : public Sensor
{
private:
    sensorData data;
public:
    DefaultSensor();
    ~DefaultSensor();
    void handle();
    sensorData getData();
    void startMeasurement();
    boolean measurementStatus();
};
#endif
