#include "DefaultSensor.hpp"


DefaultSensor::DefaultSensor() : Sensor()
{
    data.pm1  = INVAL;
    data.pm25 = INVAL;
    data.pm4  = INVAL;
    data.pm10 = INVAL;
}

DefaultSensor::~DefaultSensor()
{
}

void DefaultSensor::handle()
{
}

sensorData DefaultSensor::getData()
{
    return data;
}

void DefaultSensor::startMeasurement() {

}
boolean DefaultSensor::measurementStatus() {
    return true;
}