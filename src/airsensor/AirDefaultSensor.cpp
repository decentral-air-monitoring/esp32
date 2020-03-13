#include "AirDefaultSensor.hpp"


AirDefaultSensor::AirDefaultSensor() : AirSensor()
{
    data.temperature = 22;
    data.humidity = 21;
    data.pressure = 20;
}

AirDefaultSensor::~AirDefaultSensor()
{
}

void AirDefaultSensor::handle()
{
}

airSensorData AirDefaultSensor::getData()
{
    return data;
}

void AirDefaultSensor::startMeasurement() {

}

boolean AirDefaultSensor::measurementStatus() {
    return true;
}