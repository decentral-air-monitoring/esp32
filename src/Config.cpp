#include "Config.hpp"

Config::Config() {

}

void Config::init() {
    this->preferences.begin("air-quality");
}

boolean Config::getBool(const char * key) { // Stub
    if(this->itemExists(key)) {
        return preferences.getBool(key, false);
    };
    return false;
}

boolean Config::itemExists(const char * item) {
    for(int i=0;i<sizeof(this->keys);i++) {
        if(!strcmp(item,keys[i].key)) {
            return true;
        }
    }
    return false;
}