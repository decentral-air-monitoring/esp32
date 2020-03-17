#ifndef TTN_HPP
#define TTN_HPP

#include "common.hpp"
#include <TTN_esp32.h>

struct sensorData;
struct airSensorData;

#define TTN_BUFFER 64

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
        TTN_esp32 ttn_class;
        void join();
        char devEui[TTN_BUFFER] = "";
        char appEui[TTN_BUFFER] = "";
        char appKey[TTN_BUFFER] = "";
};

#endif