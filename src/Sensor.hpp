#ifndef SENSOR_HPP
#define SENSOR_HPP

#include "common.hpp"

struct sensorData{
    unsigned int pm1;
    unsigned int pm25;
    unsigned int pm4;
    unsigned int pm10;
    time_t time;
};
class Sensor
{
public:
    Sensor();
    ~Sensor();
    virtual void handle() = 0;
    virtual sensorData getData() = 0;
    virtual void startMeasurement() = 0;
    virtual boolean measurementStatus() = 0;
};

#include "sensor/DemoSensor.hpp"
#include "sensor/Sds_011.hpp"
#include "sensor/DefaultSensor.hpp"
#include "sensor/HPMA115C0.hpp"
#include "sensor/sps30.hpp"
#endif