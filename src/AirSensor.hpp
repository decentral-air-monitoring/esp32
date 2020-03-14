#ifndef AIR_SENSOR_HPP
#define AIR_SENSOR_HPP

#include "common.hpp"

struct airSensorData{
    int32_t temperature;
    int32_t pressure;
    int32_t humidity;
};

class AirSensor
{
public:
    AirSensor();
    ~AirSensor();
    virtual void handle() = 0;
    virtual airSensorData getData() = 0;
    virtual void startMeasurement() = 0;
    virtual boolean measurementStatus() = 0;
};

#include "airsensor/AirDefaultSensor.hpp"
#include "airsensor/BME680.hpp"
#endif