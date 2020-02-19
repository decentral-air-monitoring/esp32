#include "ConfigMode.hpp"

ConfigMode::ConfigMode() {
    
}

void ConfigMode::init() {
    this->server.on("/", this->formular);
    this->server.begin(80);
    Serial.println("Config Mode via Serial available:");
    Serial.println("Enter \"key=value\"");
}

void ConfigMode::handle() {
    this->server.handleClient();
    if(Serial.available()) {
        Serial.readBytesUntil('\n', serialBuffer, SERIAL_BUF_LENGTH);
        this->serialReceive();
    }
}
// ToDo: sscanf-logic currently broken
void ConfigMode::serialReceive() {
    char key[20] = "";
    char value[20] = "";
    char dummy[1];
    sscanf(this->serialBuffer,"%s%[=]%s",key,dummy,value);
    /*if(preferences.putString(key,value)) { // ToDo: Don't use preferences directly, but use an interface to a config class
        Serial.printf("Set %s to %s\n", key, value);
    } else {
        Serial.println("Error setting preferences!");
    }*/
}

WebServer::THandlerFunction ConfigMode::formular() {
    Serial.println("GET /");
    config_mode.server.send(200,"text/html","Hier k&ouml;nnten Ihre Einstellungen stehen!");
    return 0;
}