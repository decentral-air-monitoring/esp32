#ifndef SDS_011_HPP
#define SDS_011_HPP
#include "common.hpp"
#include "Sensor.hpp"
#include "SDS011.h"

#define RX2 22 //grün
#define TX2 23 //blau


class Sds_011 : public Sensor
{
private:
    sensorData data;
    HardwareSerial serialPort = HardwareSerial(2);
    SDS011 my_sds;
public:
    Sds_011();
    ~Sds_011();
    void handle();
    sensorData getData();
    void startMeasurement();
    boolean measurementStatus();
};
#endif
