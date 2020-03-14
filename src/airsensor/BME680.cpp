#include "BME680.hpp"


BME680::BME680() : AirSensor()
{
    data.temperature = INVAL;
    data.humidity = INVAL;
    data.pressure = INVAL;
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
    // only read out if BME is over end time and a measurement is active
    if(millis()>this->endTime && this->active) {
        if(this->bme->endReading()) {
            this->active=false;
            this->status=true;
            this->data.humidity = this->bme->readHumidity()*1000;
            this->data.pressure = this->bme->readPressure();
            this->data.temperature = this->bme->readTemperature()*1000;
        }
    }
}

airSensorData BME680::getData()
{
    if(this->status) {
    } else {
        this->data.temperature = INVAL;
        this->data.humidity = INVAL;
        this->data.pressure = INVAL;
    }
    return data;
}

void BME680::startMeasurement() {
    this->active = true;
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