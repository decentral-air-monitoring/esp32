#ifndef SDS_011_HPP
#define SDS_011_HPP
#include "common.hpp"
#include "Sensor.hpp"
#include "SDS011.h"

#define TX2 21 //grün
#define RX2 22 //blau


class Sds_011 : public Sensor
{
private:
    sensorData data;
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
