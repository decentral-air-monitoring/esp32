#include "Sds_011.hpp"

Sds_011::Sds_011() : Sensor()
{
    this->data.pm10 = INVAL;
    this->data.pm4 = INVAL;
    this->data.pm25 = INVAL;
    this->data.pm1 = INVAL;
    
    this->my_sds.begin(&SerialSensor,RX2,TX2);
}

Sds_011::~Sds_011()
{
    this->my_sds.sleep();
}

void Sds_011::handle()
{
    boolean err = false;
    float p10 = INVAL;
    float p25 = INVAL;
    if(this->active){
        err = this->my_sds.read(&p25, &p10);
        if(err){
            this->data.status = SENSOR_STATUS::ERROR;
            p10=INVAL;
            p25=INVAL;
            return;
        }
        this->status=true;
        this->data.status = SENSOR_STATUS::OK_MASS;
        this->data.pm25 = (int)(p25*1000);
        this->data.pm10 = (int)(p10*1000);
    }
}

sensorData Sds_011::getData()
{
    if(!this->status){
        this->data.pm25 = INVAL;
        this->data.pm10 = INVAL;
    }
    return data;
}

void Sds_011::startMeasurement() {
    this->my_sds.wakeup();
    this->active = true;
    this->status = false;
}
boolean Sds_011::measurementStatus() {
    return this->status;
}