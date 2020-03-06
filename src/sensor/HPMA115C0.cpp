#include "HPMA115C0.hpp"

HPMA115C0::HPMA115C0() : Sensor()
{
    this->serialPort.begin(9600,SERIAL_8N1);
    this->data.pm10 = -1;
    this->data.pm4 = -1;
    this->data.pm25 = -1;
    this->data.pm1 = -1;
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