#include "Config.hpp"

Config::Config() {

}

void Config::init() {
    this->preferences.begin("air-quality");
}

boolean Config::getBool(String key) { // Stub
    if(this->itemExists(key)) {
        // ToDo: Return Value
    };
    return false;
}

boolean Config::itemExists(String item) {
    for(int i=0;i<sizeof(this->keys);i++) {
        if(!item.compareTo(keys[i].key)) {
            return true;
        }
    }
    return false;
}