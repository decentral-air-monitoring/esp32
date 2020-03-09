#ifndef BME680_SENSOR_HPP
#define BME680_SENSOR_HPP
#include "AirSensor.hpp"
#include <stdlib.h>
#include <bsec.h>

class BME680 : public AirSensor
{
private:
    airSensorData data;
    Bsec iaqSensor;
public:
    BME680();
    ~BME680();
    void handle();
    airSensorData getData();
};
#endif
