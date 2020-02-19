#include "Config.hpp"

Config::Config() {

}

void Config::init() {
    this->preferences.begin("air-quality");
}

boolean Config::getBool(const char * key) {
    if(this->itemExists(key)) {
        return this->preferences.getBool(key, false);
    };
    return false;
}

String Config::getString(const char * key) {
    if(this->itemExists(key)) {
        return this->preferences.getString(key, "");
    };
    return "false";
}

boolean Config::itemExists(const char * item) {
    for(int i=0;i<sizeof(this->keys);i++) {
        if(!strcmp(item,keys[i].key)) {
            return true;
        }
    }
    return false;
}