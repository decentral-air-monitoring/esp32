#ifndef AIR_SENSOR_HPP
#define AIR_SENSOR_HPP

#include "common.hpp"

struct airSensorData{
    int temperature;
    unsigned int pressure;
    unsigned int humidity;
};

class AirSensor
{
public:
    AirSensor();
    ~AirSensor();
    virtual void handle() = 0;
    virtual airSensorData getData() = 0;
};

#include "airsensor/AirDefaultSensor.hpp"
#endif