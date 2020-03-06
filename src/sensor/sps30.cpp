#include "sps30.hpp"

// UART Commands
#define UART_START_MEASUREMENT 0x00
#define UART_START_SUBCOMMAND 0x01
#define UART_START_MEASUREMENT_MODE 0x03

#define UART_STOP_MEASUREMENT 0x01
#define UART_READ_MEASUREMENT 0x03

SPS30::SPS30() : Sensor()
{
    //this->serialPort.begin(9600,SERIAL_8N1);
    this->data.pm10 = -1;
    this->data.pm8 = -1;
    this->data.pm25 = -1;
    this->data.pm1 = -1;
}

SPS30::~SPS30()
{
}

void SPS30::handle()
{
}

sensorData SPS30::getData()
{

    return data;
}


int SPS30::startMeasurement()
{
}

int SPS30::stopMeasurement()
{
}