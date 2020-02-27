#include "DemoSensor.hpp"


DemoSensor::DemoSensor() : Sensor()
{
    
}

DemoSensor::~DemoSensor()
{
}

void DemoSensor::handle()
{
    time_t timer;

    data.pm1  = randomFloat(0,8);
    data.pm25 = randomFloat(0,8);
    data.pm8  = randomFloat(0,8);
    data.pm10 = randomFloat(0,8);
    data.time = time(&timer);
}

sensorData DemoSensor::getData()
{
    return data;
}



float DemoSensor::randomFloat(float min, float max)
{
    if(min < max){
        float random = ((float) rand()) / (float) RAND_MAX;
        float range = max - min;  
        return (random*range) + min;
    }
    return 0;
}