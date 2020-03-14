#include "AirDefaultSensor.hpp"


AirDefaultSensor::AirDefaultSensor() : AirSensor()
{
    data.temperature = INVAL;
    data.humidity = INVAL;
    data.pressure = INVAL;
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