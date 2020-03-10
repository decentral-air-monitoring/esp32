#include "BME680.hpp"


BME680::BME680() : AirSensor()
{
    data.temperature = 22;
    data.humidity = 21;
    data.pressure = 20;
    Wire.begin(I2C_SDA,I2C_SCL);
    bme = new Adafruit_BME680(&Wire);
}

BME680::~BME680()
{
}

void BME680::handle()
{
}

airSensorData BME680::getData()
{
    return data;
}