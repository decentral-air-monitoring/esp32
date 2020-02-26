#ifndef SDS_011_HPP
#define SDS_011_HPP
#include "common.hpp"
#include "Sensor.hpp"
#include <SoftwareSerial.h>

class Sds_011 : public Sensor
{
private:
    sensorData data;

    SoftwareSerial connection;
public:
    Sds_011();
    ~Sds_011();
    void handle();
    sensorData getData();
};
#endif
