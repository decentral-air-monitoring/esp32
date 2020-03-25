#ifndef SDS_011_HPP
#define SDS_011_HPP
#include "common.hpp"
#include "Sensor.hpp"
#include "SDS011.h"

class Sds_011 : public Sensor
{
private:
    sensorData data;
    SDS011 my_sds;
    boolean status = false;
    boolean active = false;
public:
    Sds_011();
    ~Sds_011();
    void handle();
    sensorData getData();
    void startMeasurement();
    boolean measurementStatus();
};
#endif
