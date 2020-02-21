#include "ConfigMode.hpp"

ConfigMode::ConfigMode() {
    
}

void ConfigMode::init() {
    this->server.on("/", this->formular);
    this->server.begin(80);
    Serial.println("Config Mode enabled");
}

void ConfigMode::handle() {
    this->server.handleClient();
}

WebServer::THandlerFunction ConfigMode::formular() {
    Serial.println("GET /");
    config_mode.server.send(200,"text/html","Hier k&ouml;nnten Ihre Einstellungen stehen!");
    return 0;
}