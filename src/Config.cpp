#include "Config.hpp"

Config::Config() {

}

void Config::init() {
    this->preferences.begin("air-quality");
}

boolean Config::getBool(String key) { // Stub
    return false;
}