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
  String key;
  CONFIG_TYPE type;
};

class Config{
    public:
        Config();
        void init();
        boolean getBool(String key);
    private:
        const config_item keys[2] = {
            {"CONFIGURED", CONFIG_TYPE::BOOL },
            {"AP_NAME", CONFIG_TYPE::STRING }
        };
        Preferences preferences;
        boolean itemExists(String item);
};

#endif