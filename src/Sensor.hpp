#ifndef SENSOR_HPP
#define SENSOR_HPP

#include "common.hpp"

enum SENSOR_STATUS {
    OK_MASS = 20,
    OK_COUNT = 21,
    ERROR = 30
};

struct sensorData{
    int32_t pm1;
    int32_t pm25;
    int32_t pm4;
    int32_t pm10;
    unsigned short status = SENSOR_STATUS::ERROR;
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