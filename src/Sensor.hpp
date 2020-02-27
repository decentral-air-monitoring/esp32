#ifndef SENSOR_HPP
#define SENSOR_HPP

#include "common.hpp"

struct sensorData{
    unsigned int pm1;
    unsigned int pm25;
    unsigned int pm8;
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
};

#include "DemoSensor.hpp"
#include "Sds_011.hpp"
#endif