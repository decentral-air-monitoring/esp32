#ifndef WIFI_HPP
#define WIFI_HPP

#include "common.hpp"

#include <WiFi.h>
#include <WiFiClientSecure.h>

#define ConfigModeSSID "AirQualitySetup"
#define WIFI_LENGTH 20

class AirQualityWifi {
    public:
        AirQualityWifi();
        void init();
        void handle();
    private:
        char ssid[WIFI_LENGTH] = "";
        char pass[WIFI_LENGTH] = "";
        unsigned long reconnectInterval = 0;
        unsigned long reconnectLastTry = 0;
};

extern AirQualityWifi air_wifi;

#endif