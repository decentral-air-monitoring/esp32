#include "TTN.hpp"

TTN::TTN() {

}

void TTN::init() {
    // configuration.getString("TTN_PASSWORD").toCharArray(this->TTNPassword,TTN_LENGTH);
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
    /*if(this->client.connected()) {
        char msg[80];
        // StationID,Statuscode,PM1,PM2.5,PM4,PM10,Temperature,Humidity,Pressure
        sprintf(msg,"%i,%i,%i,%i,%i,%i,%i,%i,%i",configuration.getInt("STATION_ID"), d.status, d.pm1,d.pm25,d.pm4,d.pm10,a.temperature,a.humidity,a.pressure);
        this->client.publish("particle", msg);
    }*/
}

void TTN::sendInitPacket() {
   /* if(this->client.connected()) {
        char msg[80];
        // StationId, 10, Sensortype Particle, Sensortype Environment, Connection Type
        sprintf(msg,"%i,%i,%i,%i",configuration.getInt("STATION_ID"), 10, configuration.getInt("SENSOR_TYPE"), configuration.getInt("AIR_SENSOR_TYPE"));
        this->client.publish("particle", msg);
    }*/
}