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
    if(this->bme->endReading()) {
        this->status=true;
        this->data.humidity = this->bme->readHumidity()*1000;
        this->data.pressure = this->bme->readPressure();
        this->data.temperature = this->bme->readTemperature()*1000;
    }
}

airSensorData BME680::getData()
{
    if(this->status) {
    } else {
        this->data.temperature = -30000;
        this->data.humidity = -30000;
        this->data.pressure = -30000;
    }
    return data;
}

void BME680::startMeasurement() {
    this->status = false;
    this->endTime = this->bme->beginReading();
    if(this->endTime == 0) {
        Serial.println(F("BME680: Failure to start reading"));
        return;
    }
}

boolean BME680::measurementStatus() {
    return this->status; 
}