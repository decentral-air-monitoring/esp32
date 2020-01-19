#include "AirQualityWiFi.hpp"

AirQualityWifi::AirQualityWifi() {
}

void AirQualityWifi::init() {
    switch(op_mode) {
        case config:
            WiFi.mode(WIFI_AP);
            WiFi.softAP(ConfigModeSSID, "insecure-default-todo");
            Serial.println("WiFi Config Mode");
        break;
        case normal:
        // ToDo: Connect to preconfigured 
            /*Serial.printf("Connect with %s\n",ssid);
            WiFi.mode(WIFI_STA);
            WiFi.begin(ssid);*/
        break;
    } 
}