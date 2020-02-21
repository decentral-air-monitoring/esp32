#include "SerialTerminal.hpp"

SerialTerminal::SerialTerminal() {

}

void SerialTerminal::init() {
    this->printHelp();
}

void SerialTerminal::printHelp() {
    Serial.println("Enter \"key=value\"");
}

void SerialTerminal::handle() {
    if(Serial.available()) {
        Serial.readBytesUntil('\n', serialBuffer, SERIAL_BUF_LENGTH);
        this->receive();
    }
}

void SerialTerminal::receive() {
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
