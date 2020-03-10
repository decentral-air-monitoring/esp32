#ifndef BME680_SENSOR_HPP
#define BME680_SENSOR_HPP
#include "AirSensor.hpp"
#include <stdlib.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

class BME680 : public AirSensor
{
private:
    Adafruit_BME680* bme;
    airSensorData data;
public:
    BME680();
    ~BME680();
    void handle();
    airSensorData getData();
};
#endif
