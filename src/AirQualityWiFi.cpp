#include "AirQualityWiFi.hpp"

AirQualityWifi::AirQualityWifi() {
}

void AirQualityWifi::init() {
    this->reconnectInterval = configuration.getInt("WIFI_RECONNECT")*1000;
    switch(op_mode) {
        case config:
            WiFi.mode(WIFI_AP);
            WiFi.softAP(ConfigModeSSID, "insecure-default-todo");
            Serial.println("WiFi Config Mode");
        break;
        case normal:
            configuration.getString("STA_SSID").toCharArray(this->ssid,WIFI_LENGTH);
            configuration.getString("STA_PASS").toCharArray(this->pass,WIFI_LENGTH);
            Serial.printf("WiFi: Connecting with %s\n",this->ssid);
            WiFi.mode(WIFI_STA);
            WiFi.begin(this->ssid,this->pass);
        break;
    } 
}

void AirQualityWifi::handle() {
    switch(op_mode) {
        case config:
        break;
        case normal:
        if(!WiFi.isConnected()) {
            if (millis() - this->reconnectLastTry > this->reconnectInterval) {
                this->reconnectLastTry = millis();
                Serial.println("WiFi: Trying to reconnect...");
                WiFi.disconnect();
                WiFi.mode(WIFI_OFF);
                WiFi.mode(WIFI_STA);
                WiFi.begin(this->ssid,this->pass);
            }
        }
        break;
    } 
}