#ifndef TTN_HPP
#define TTN_HPP

#include "common.hpp"

struct sensorData;
struct airSensorData;

#define ARDUINO_LMIC_CFG_NETWORK_TTN EU868

class TTN {
    public:
        TTN();
        void init();
        void handle();
        void send();
        void send(sensorData d);
        void send(sensorData d, airSensorData a);
        void sendInitPacket();
    private:
};

#endif