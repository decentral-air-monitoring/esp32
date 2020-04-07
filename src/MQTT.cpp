#include "MQTT.hpp"

MQTT::MQTT() {

}

void MQTT::init() {
    configuration.getString("MQTT_SERVER").toCharArray(this->mqttServer,MQTT_LENGTH);
    configuration.getString("MQTT_USER").toCharArray(this->mqttUser,MQTT_LENGTH);
    configuration.getString("MQTT_PASSWORD").toCharArray(this->mqttPassword,MQTT_LENGTH);
    this->mqttPort = configuration.getInt("MQTT_PORT");
    this->reconnectInterval = configuration.getInt("MQTT_RECONNECT")*1000;
    sprintf(this->mqttName,"AirQualityStation%i",configuration.getInt("STATION_ID"));
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
            Serial.printf("MQTT: Status %i\n",this->client.state());
            Serial.printf("MQTT: Connecting to %s as user %s\n", this->mqttServer, this->mqttUser);
            if (this->client.connect(this->mqttName,this->mqttUser,this->mqttPassword)) {
                Serial.println("MQTT: connected");
                this->sendInitPacket();                 
            } else {
                Serial.print("MQTT: Connection failed failed with state ");
                Serial.println(this->client.state());
            }
        }
    }
    this->client.loop();
}

void MQTT::send() {
    airSensorData a;
    a.humidity = INVAL; a.temperature=INVAL; a.pressure=INVAL;
    sensorData d;
    d.pm1 = INVAL; d.pm25=INVAL; d.pm4=INVAL;d.pm10=INVAL; d.status=SENSOR_STATUS::ERROR;
    this->send(d,a);
}

void MQTT::send(sensorData d) {
    airSensorData a;
    a.humidity = INVAL; a.temperature=INVAL; a.pressure=INVAL;
    this->send(d,a);
}

void MQTT::send(sensorData d, airSensorData a) {
    if(this->client.connected()) {
        char msg[80];
        // StationID,Statuscode,PM1,PM2.5,PM4,PM10,Temperature,Humidity,Pressure
        sprintf(msg,"%i,%i,%i,%i,%i,%i,%i,%i,%i",configuration.getInt("STATION_ID"), d.status, d.pm1,d.pm25,d.pm4,d.pm10,a.temperature,a.humidity,a.pressure);
        this->client.publish("particle", msg);
    }
}

void MQTT::sendInitPacket() {
    if(this->client.connected()) {
        char msg[80];
        // StationId, 10, Sensortype Particle, Sensortype Environment, Connection Type
        sprintf(msg,"%i,%i,%i,%i",configuration.getInt("STATION_ID"), 10, configuration.getInt("SENSOR_TYPE"), configuration.getInt("AIR_SENSOR_TYPE"));
        this->client.publish("particle", msg);
    }
}