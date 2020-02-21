#include "Config.hpp"

Config::Config() {

}

void Config::init() {
    this->preferences.begin("air-quality");
}

boolean Config::getBool(const char * key) {
    boolean d;
    if(this->itemExists(key, &d)) {
        return this->preferences.getBool(key, d);
    };
    return false;
}

int Config::getInt(const char * key) {
    int d;
    if(this->itemExists(key, &d)) {
        return this->preferences.getInt(key, d);
    };
    return false;
}

String Config::getString(const char * key) {
    char d[VALUE_LENGTH];
    if(this->itemExists(key, d)) {
        return this->preferences.getString(key, d);
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
boolean Config::itemExists(const char * item, char *d) {
    for(int i=0;i<sizeof(this->keys);i++) {
        if(!strcmp(item,keys[i].key)) {
            strcpy(d, keys[i].def.s);
            return true;
        }
    }
    return false;
}
boolean Config::itemExists(const char * item, int * d) {
    for(int i=0;i<sizeof(this->keys);i++) {
        if(!strcmp(item,keys[i].key)) {
            *d = keys[i].def.i;
            return true;
        }
    }
    return false;
}
boolean Config::itemExists(const char * item, boolean * d) {
    for(int i=0;i<sizeof(this->keys);i++) {
        if(!strcmp(item,keys[i].key)) {
            *d = keys[i].def.b;
            return true;
        }
    }
    return false;
}