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
            char ssid[WIFI_LENGTH] = "";
            char pass[WIFI_LENGTH] = "";
            configuration.getString("STA_SSID").toCharArray(ssid,WIFI_LENGTH);
            configuration.getString("STA_PASS").toCharArray(pass,WIFI_LENGTH);
            Serial.printf("Connecting with %s\n",ssid);
            WiFi.mode(WIFI_STA);
            WiFi.begin(ssid,pass);
        break;
    } 
}