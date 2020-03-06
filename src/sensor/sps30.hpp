#ifndef SPS30_HPP
#define SPS30_HPP
#include "common.hpp"
#include "Sensor.hpp"

class SPS30:public Sensor
{
private:
    sensorData data;
    void startMeasurement();
    void stopMeasurement();
    
public:
    SPS30();
    ~SPS30();
    void handle();
    sensorData getData();
}