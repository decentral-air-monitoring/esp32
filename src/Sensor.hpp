#ifndef SENSOR_HPP
#define SENSOR_HPP

#include "common.hpp"

struct sensorData{
    float pm1;
    float pm25;
    float pm8;
    float pm10;
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