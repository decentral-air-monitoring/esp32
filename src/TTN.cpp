#include "TTN.hpp"

TTN::TTN() {

}

void TTN::init() {
    configuration.getString("TTN_DEV_EUI").toCharArray(this->devEui,TTN_BUFFER);
    configuration.getString("TTN_APP_EUI").toCharArray(this->appEui,TTN_BUFFER);
    configuration.getString("TTN_APP_KEY").toCharArray(this->appKey,TTN_BUFFER);
    this->ttn_class.begin();
    this->ttn_class.showStatus();
    this->join();
}

void TTN::join() {
    this->ttn_class.join(this->devEui,this->appEui,this->appKey);
    int i = 0;
    while (!this->ttn_class.isJoined())
    {
        Serial.print(".");
        i++;
        if(i>10) {
            return;
        }
        delay(500);
    }
    if(this->ttn_class.isJoined()) {
        this->sendInitPacket();
    }
    Serial.println("\njoined !");
    this->ttn_class.showStatus();
}

void TTN::handle() {
    
}

void TTN::send() {

}

void TTN::send(sensorData d) {
    airSensorData a;
    a.humidity = -300; a.temperature=-300; a.pressure=-300;
    //this->send(d,a);
}

void TTN::send(sensorData d, airSensorData a) {
    char msg[80];
    // StationID,Statuscode,PM1,PM2.5,PM4,PM10,Temperature,Humidity,Pressure
    sprintf(msg,"%i,%i,%i,%i,%i,%i,%i,%i,%i",configuration.getInt("STATION_ID"), d.status, d.pm1,d.pm25,d.pm4,d.pm10,a.temperature,a.humidity,a.pressure);
    this->ttn_class.sendBytes((uint8_t*)msg,strlen(msg));
    
}

void TTN::sendInitPacket() {
    char msg[80];
    // StationId, 10, Sensortype Particle, Sensortype Environment, Connection Type
    sprintf(msg,"%i,%i,%i,%i",configuration.getInt("STATION_ID"), 10, configuration.getInt("SENSOR_TYPE"), configuration.getInt("AIR_SENSOR_TYPE"));
    this->ttn_class.sendBytes((uint8_t*)msg,strlen(msg));
}