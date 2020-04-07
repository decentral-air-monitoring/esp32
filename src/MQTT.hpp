#ifndef MQTT_HPP
#define MQTT_HPP

#include "common.hpp"
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

#define MQTT_LENGTH 25

struct sensorData;
struct airSensorData;

class MQTT {
    public:
        MQTT();
        void init();
        void handle();
        void send();
        void send(sensorData d);
        void send(sensorData d, airSensorData a);
        void sendInitPacket();
    private:
        PubSubClient client;
        WiFiClient espClient;
        WiFiClientSecure espClientSecure;
        char mqttServer[MQTT_LENGTH] = "";
        int mqttPort = 0;
        char mqttUser[MQTT_LENGTH] = "";
        char mqttPassword[MQTT_LENGTH] = "";
        char mqttName[MQTT_LENGTH] = "";
        unsigned long reconnectInterval = 0;
        unsigned long reconnectLastTry = 0;
        boolean connectFirstTry = true;
};

#endif