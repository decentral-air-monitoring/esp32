#include "MQTT.hpp"

MQTT::MQTT() {

}

void MQTT::init() {
    configuration.getString("MQTT_SERVER").toCharArray(this->mqttServer,MQTT_LENGTH);
    configuration.getString("MQTT_USER").toCharArray(this->mqttUser,MQTT_LENGTH);
    configuration.getString("MQTT_PASSWORD").toCharArray(this->mqttPassword,MQTT_LENGTH);
    this->mqttPort = configuration.getInt("MQTT_PORT");
    this->reconnectInterval = configuration.getInt("MQTT_RECONNECT")*1000;
    if(configuration.getBool("MQTT_TLS")) {
      // MQTT with TLS
      this->client.setClient(this->espClientSecure);
      Serial.println("MQTT: init with TLS");
    } else {
      // No TLS
      this->client.setClient(this->espClient);
      Serial.println("MQTT: init without TLS");
    }
    this->client.setServer(this->mqttServer, this->mqttPort);
}

void MQTT::handle() {
    // Try to connect to MQTT if unconnected
    if(WiFi.isConnected() && !this->client.connected()) {
        if((millis() - this->reconnectLastTry > this->reconnectInterval) || this->connectFirstTry) {
            this->connectFirstTry = false;
            this->reconnectLastTry = millis();
            Serial.printf("MQTT: Connecting to %s as user %s\n", this->mqttServer, this->mqttUser);
            if (this->client.connect("ESP32Client",this->mqttUser,this->mqttPassword)) {
                Serial.println("MQTT: connected");                  
            } else {
                Serial.print("MQTT: Connection failed failed with state ");
                Serial.println(this->client.state());
            }
        }
    }
}

void MQTT::send() {
    if(this->client.connected()) {
        // ToDo: Read values from global Sensor-Singleton
        this->client.publish("particle", "42,42,42,42,42,42,42,42,42");
    }
}

void MQTT::send(sensorData d) {
    if(this->client.connected()) {
        char msg[80];
        int status = 20;
        sprintf(msg,"%i,%i,%i,%i,%i,%i,42,42,42",configuration.getInt("STATION_ID"), status, d.pm1,d.pm25,d.pm4,d.pm10);
        this->client.publish("particle", msg);
    }
}