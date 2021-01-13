#ifndef HPMA115C0_HPP
#define HPMA115C0_HPP
#include "common.hpp"
#include "Sensor.hpp"

#ifdef ESP32
//extern HardwareSerial port;
#endif

enum HPMA_COMMAND {
    NONE,
    STOP_AUTO_SEND,
    START_MEASUREMENT,
    STOP_MEASUREMENT,
    READ_RESULTS
};

class HPMA115C0 : public Sensor
{
private:
    sensorData data;
    HardwareSerial serialPort = HardwareSerial(2);
    void sendChecksum(byte data[], size_t len);
    HPMA_COMMAND command = HPMA_COMMAND::NONE;
    boolean measurement_available = false;
    boolean measurement_running = false;
public:
    HPMA115C0();
    ~HPMA115C0();
    void handle();
    sensorData getData();
    void startMeasurement();
    boolean measurementStatus();
};
#endif
