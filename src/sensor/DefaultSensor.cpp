#include "DefaultSensor.hpp"


DefaultSensor::DefaultSensor() : Sensor()
{
    data.pm1  = -1;
    data.pm25 = -1;
    data.pm4  = -1;
    data.pm10 = -1;
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