#ifndef CONFIGMODE_HPP
#define CONFIGMODE_HPP

#include "common.hpp"
#include <WebServer.h>

#define FORM_SIZE 210

class ConfigMode {
    private:
        static WebServer::THandlerFunction formular();
        static WebServer::THandlerFunction formularPost();
        char * createHTMLForKey(const char * key, char * htmlChar);
    public:
        ConfigMode();
        void init();
        void handle();
        WebServer server;

        const char keys [KEY_AMOUNT][KEY_LENGTH] = {
        "CONFIG_AP_NAME",
        "READ_INTERVAL",
        "MQTT_PORT",
        "MQTT_SERVER",
        "MQTT_TOPIC",
        "MQTT_USER",
        "MQTT_PASSWORD",
        "MQTT_TLS",
        "MQTT_RECONNECT",
        "STA_SSID",
        "STA_PASS",
        "WIFI_RECONNECT",
        "SENSOR_TYPE",
        "AIR_SENSOR_TYPE",
        "STATION_ID",
        "LORA_ENABLED",
        "TTN_DEV_EUI",
        "TTN_APP_EUI",
        "TTN_APP_KEY",
        "CONFIGURED"
    };
};

extern ConfigMode config_mode;

#endif