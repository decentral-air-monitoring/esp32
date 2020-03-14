#include "Sds_011.hpp"

Sds_011::Sds_011() : Sensor()
{
    this->data.pm10 = INVAL;
    this->data.pm4 = INVAL;
    this->data.pm25 = INVAL;
    this->data.pm1 = INVAL;
    
    this->my_sds.begin(&SerialSensor,RX2,TX2);
    this->my_sds.wakeup();
}

Sds_011::~Sds_011()
{
}

void Sds_011::handle()
{

}

sensorData Sds_011::getData()
{
    boolean err;
    float p10 = INVAL;
    float p25 = INVAL;
    
    err = this->my_sds.read(&p25, &p10);

    if (!err){
        p10=p10*1000;
        p25=p25*1000;
        this->data.status = SENSOR_STATUS::OK_MASS;
        this->data.pm25 = (int)p25;
        this->data.pm10 = (int)p10;
    }else{
        this->data.status = SENSOR_STATUS::ERROR;
        Serial.println("error");
        Serial.println(p25);
    }
    return data;
}

void Sds_011::startMeasurement() {

}
boolean Sds_011::measurementStatus() {
    return true;
}