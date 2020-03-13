#include "BME680.hpp"


BME680::BME680() : AirSensor()
{
    data.temperature = 22;
    data.humidity = 21;
    data.pressure = 20;
    if(!Wire.begin(I2C_SDA,I2C_SCL)) {
        Serial.println("Wire: Initialization Error");
        return;
    }
    bme = new Adafruit_BME680(&Wire);
    if(!bme->begin()) {
        Serial.println("BME680: Initialization Error");
        return;
    }
    Serial.println("BME680 Initialized");
}

BME680::~BME680()
{
}

void BME680::handle()
{
}

airSensorData BME680::getData()
{
    if (! bme->performReading()) {
        Serial.println("Failed to perform reading :(");
        return data;
    }
    data.humidity = bme->readHumidity()*1000;
    data.pressure = bme->readPressure();
    data.temperature = bme->readTemperature()*1000;
    return data;
}

void BME680::startMeasurement() {

}

boolean BME680::measurementStatus() {
    return true; 
}