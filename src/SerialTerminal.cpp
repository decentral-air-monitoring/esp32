#include "SerialTerminal.hpp"

SerialTerminal::SerialTerminal() {

}

void SerialTerminal::init() {
    this->printHelp();
}

void SerialTerminal::printHelp() {
    Serial.println("'?' for this hint message");
    Serial.println("'PRINT' for the current configuration");
    Serial.println("\"key=value\" to set a new value");
}

void SerialTerminal::printConfiguration() {
    Serial.println("Current Configuration:");
}

void SerialTerminal::handle() {
    while(Serial.available() > 0) {
        // Check for free buffer
        if(this->serialBufferPointer<SERIAL_BUF_LENGTH-1) {
            char temp = (char) Serial.read();
            if(temp == '\r') return;
            this->serialBuffer[this->serialBufferPointer] = temp;
            // Check for newline
            if(this->serialBuffer[this->serialBufferPointer]=='\n') {
                this->serialBuffer[this->serialBufferPointer] = 0;
                this->serialBufferPointer=0;
                this->receive();
                return;
            }
            this->serialBufferPointer++;
        } else {
            // Buffer filed up, jump to handler and reset
            this->serialBuffer[this->serialBufferPointer] = 0;
            this->receive();
            this->serialBufferPointer = 0;
        }        
    }
}

void SerialTerminal::receive() {
    char key[20] = "";
    char value[20] = "";
    char dummy[1];
    Serial.println(this->serialBuffer);
    if(!strcmp(this->serialBuffer, "PRINT")) {
        this->printConfiguration();
        return;
    }
    if(!strcmp(this->serialBuffer, "?")) {
        this->printHelp();
        return;
    }
    // sscanf(this->serialBuffer,"%s%[=]%s",key,dummy,value);
    /*if(preferences.putString(key,value)) { // ToDo: Don't use preferences directly, but use an interface to a config class
        Serial.printf("Set %s to %s\n", key, value);
    } else {
        Serial.println("Error setting preferences!");
    }*/
    Serial.println("Unrecognized Command. '?' for help.");
}
