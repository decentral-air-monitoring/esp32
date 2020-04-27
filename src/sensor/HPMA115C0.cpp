#include "HPMA115C0.hpp"

HPMA115C0::HPMA115C0() : Sensor()
{
    this->serialPort.begin(9600,SERIAL_8N1);
    this->data.pm10 = INVAL;
    this->data.pm4 = INVAL;
    this->data.pm25 = INVAL;
    this->data.pm1 = INVAL;
}

HPMA115C0::~HPMA115C0()
{
}

void HPMA115C0::handle()
{
}

sensorData HPMA115C0::getData()
{
    return data;
}

void HPMA115C0::startMeasurement() {

}
boolean HPMA115C0::measurementStatus() {
    return true;
}