#ifndef HPMA115C0_HPP
#define HPMA115C0_HPP
#include "common.hpp"
#include "Sensor.hpp"

#define RX1 16
#define TX2 17

#ifdef ESP32
//extern HardwareSerial port;
#endif

class HPMA115C0 : public Sensor
{
private:
    sensorData data;
    HardwareSerial serialPort = HardwareSerial(2);

public:
    HPMA115C0();
    ~HPMA115C0();
    void handle();
    sensorData getData();
};
#endif
