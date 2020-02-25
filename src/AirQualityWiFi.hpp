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
};

extern AirQualityWifi air_wifi;

#endif