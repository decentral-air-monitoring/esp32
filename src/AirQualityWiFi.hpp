#ifndef WIFI_HPP
#define WIFI_HPP

#include "common.hpp"

#include <WiFi.h>

class AirQualityWifi {
    public:
        AirQualityWifi();
        void init();
};

extern AirQualityWifi air_wifi;

#endif