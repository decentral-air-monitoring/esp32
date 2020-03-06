#include "Sds_011.hpp"

HardwareSerial SerialSensor(2);

Sds_011::Sds_011() : Sensor()
{
    this->data.pm10 = -1;
    this->data.pm4 = -1;
    this->data.pm25 = -1;
    this->data.pm1 = -1;
    
    //SerialSensor.begin(9600,SERIAL_8N1,RX2,TX2);
    //SerialSensor.println("Hello Marvin!!!!");
    this->my_sds.begin(&SerialSensor,RX2,TX2);
    this->my_sds.wakeup();
}

Sds_011::~Sds_011()
{
}

void Sds_011::handle()
{

    boolean err;
    float p10 = -1;
    float p25 = -1;
    
    err = this->my_sds.read(&p25, &p10);

    if (!err){
        this->data.pm25 = p25;
        this->data.pm10 = p10;
    }else{
        Serial.println("error");
        Serial.println(p25);
    }
}

sensorData Sds_011::getData()
{
    return data;
}

void Sds_011::startMeasurement() {

}
boolean Sds_011::measurementStatus() {
    return false;
}