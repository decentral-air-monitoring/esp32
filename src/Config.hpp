#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "common.hpp"

#include <Preferences.h>

enum class CONFIG_TYPE {
    INT,
    BOOL,
    STRING
};

struct config_item {
  char key[20];
  CONFIG_TYPE type;
};

class Config{
    public:
        Config();
        void init();
        boolean getBool(const char * key);
        String getString(const char * key);
        int getInt(const char * key);
        const config_item keys[2] = {
            {"CONFIGURED", CONFIG_TYPE::BOOL },
            {"AP_NAME", CONFIG_TYPE::STRING }
        };
    private:
        Preferences preferences;
        boolean itemExists(const char * item);
};

#endif