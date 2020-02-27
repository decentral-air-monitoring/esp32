#ifndef SDS_011_HPP
#define SDS_011_HPP
#include "common.hpp"
#include "Sensor.hpp"
#include <SoftwareSerial.h>
#include <SDS011.h>

#define RX1 16
#define TX2 17

#ifdef ESP32
//HardwareSerial port(2);
#endif

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
};
#endif
