#include "TTN.hpp"
#define UNUSED_PIN 0xFF

TTN::TTN() {

}

void TTN::init() {
    if(this->status==TTN_STATUS::INIT) { // only initialize, if no other stuff happened
        configuration.getString("TTN_DEV_EUI").toCharArray(this->devEui,TTN_BUFFER);
        configuration.getString("TTN_APP_EUI").toCharArray(this->appEui,TTN_BUFFER);
        configuration.getString("TTN_APP_KEY").toCharArray(this->appKey,TTN_BUFFER);
        //SPI.begin(SCK,MISO,MOSI,SS);
        //this->ttn_class.begin(TTN_esp32_LMIC::GetPinmap_heltec_wireless_stick());
        // this->ttn_class.begin(SS, UNUSED_PIN, RST_LoRa, DIO0,DIO1,DIO2);
        this->ttn_class.begin();
        this->join();
        this->status=TTN_STATUS::WAIT_JOIN;
    }
}

void TTN::join() {
    this->ttn_class.join(this->devEui,this->appEui,this->appKey);
}

void TTN::handle() {
    switch(this->status) {
        case TTN_STATUS::WAIT_JOIN:
            if(this->ttn_class.isJoined()) {
                this->status=TTN_STATUS::JOINED;
                this->sendInitPacket();
                Serial.println("TTN: joined!");
                this->ttn_class.showStatus();
            }
        break;
        case TTN_STATUS::JOINED:
        break;
    }
    
}

void TTN::send() {
    airSensorData a;
    a.humidity = INVAL; a.temperature=INVAL; a.pressure=INVAL;
    sensorData d;
    d.pm1 = INVAL; d.pm25=INVAL; d.pm4=INVAL;d.pm10=INVAL; d.status=SENSOR_STATUS::ERROR;
    this->send(d,a);
}

void TTN::send(sensorData d) {
    airSensorData a;
    a.humidity = INVAL; a.temperature = INVAL; a.pressure = INVAL;
    this->send(d,a);
}

void TTN::send(sensorData d, airSensorData a) {
    if(this->status!=TTN_STATUS::JOINED) return;
    char msg[80];
    // StationID,Statuscode,PM1,PM2.5,PM4,PM10,Temperature,Humidity,Pressure
    sprintf(msg,"%i,%i,%i,%i,%i,%i,%i,%i,%i",configuration.getInt("STATION_ID"), d.status, d.pm1,d.pm25,d.pm4,d.pm10,a.temperature,a.humidity,a.pressure);
    if(!this->ttn_class.sendBytes((uint8_t*)msg,strlen(msg))) {
        this->status=TTN_STATUS::ERR;
        Serial.println("TTN: Error sending packet!");
    }
}

void TTN::sendInitPacket() {
    if(this->status!=TTN_STATUS::JOINED) return;
    char msg[80];
    // StationId, 10, Sensortype Particle, Sensortype Environment, Connection Type
    sprintf(msg,"%i,%i,%i,%i",configuration.getInt("STATION_ID"), 10, configuration.getInt("SENSOR_TYPE"), configuration.getInt("AIR_SENSOR_TYPE"));
    if(!this->ttn_class.sendBytes((uint8_t*)msg,strlen(msg))) {
        this->status=TTN_STATUS::ERR;
        Serial.println("TTN: Error sending init packet!");
    }
}