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
    Serial.println("'reboot' to restart the ESP");
}

void SerialTerminal::printConfiguration() {
    Serial.println("Current Configuration:");
    for(int i=0;i<sizeof(configuration.keys)/sizeof(config_item);i++) {
        Serial.print(configuration.keys[i].key);
        Serial.print("=");
        switch(configuration.keys[i].type) {
            case CONFIG_TYPE::BOOL:
                Serial.print(configuration.getBool(configuration.keys[i].key));
            break;
            case CONFIG_TYPE::INT:
                Serial.print(configuration.getInt(configuration.keys[i].key));
            break;
            case CONFIG_TYPE::STRING:
                Serial.print(configuration.getString(configuration.keys[i].key));
            break;
            default:
                return;
        }
        Serial.println();
    }
}

void SerialTerminal::handle() {
    if(Serial.available()) {
        ledState = !ledState;
    }
    while(Serial.available() > 0) {
        // Check for free buffer
        if(this->serialBufferPointer<SERIAL_BUF_LENGTH-1) {
            char temp = (char) Serial.read();
            Serial.print(temp);
            if(temp == '\r') return;
            if(temp == 0x08) {
                if(this->serialBufferPointer>0) {
                    this->serialBufferPointer--;
                }
                return;
            }
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
    if(!strcmp(this->serialBuffer, "PRINT")) {
        this->printConfiguration();
        return;
    }
    if(!strcmp(this->serialBuffer, "?")) {
        this->printHelp();
        return;
    }
    if(!strcmp(this->serialBuffer, "reboot")) {
        ESP.restart();
        return;
    }
    if(sscanf(this->serialBuffer,"%[^=]=%[^=]",key,value)==2) {
        if(strlen(value) < 1) {
            Serial.println("Error: No value given");
            return;
        }
        switch(configuration.getType(key)) {
            case CONFIG_TYPE::STRING:
                configuration.setString(key,value);
                Serial.printf("%s successfully updated!\n",key);
            break;
            case CONFIG_TYPE::BOOL:
                if(!strcmp(value,"true")) {
                    configuration.setBool(key,true);
                    Serial.printf("%s successfully updated!\n",key);
                } else if (!strcmp(value,"1")) {
                    configuration.setBool(key,true);
                    Serial.printf("%s successfully updated!\n",key);
                } else if (!strcmp(value,"false")) {
                    configuration.setBool(key,false);
                    Serial.printf("%s successfully updated!\n",key);
                } else if (!strcmp(value,"0")) {
                    configuration.setBool(key,false);
                    Serial.printf("%s successfully updated!\n",key);
                } else {
                    Serial.printf("Unable to recognize %s as Boolean\n",value);
                }
                if(!strcmp(key,"CONFIGURED")) {
                    ESP.restart();
                }
            break;
            case CONFIG_TYPE::INT:
                int i;
                if(sscanf(value,"%i",&i)==1) {
                    configuration.setInt(key,i);
                    Serial.printf("%s successfully updated!\n",key);
                } else {
                    Serial.println("Error: Invalid Integer");
                }
            break;
            default:
                Serial.printf("Set for %s not implemented or %s not existing!\n",key, key);
        }
        return;
    }
    Serial.println("Unrecognized Command. '?' for help.");
}
