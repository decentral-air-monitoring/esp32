#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "common.hpp"

#include <Preferences.h>

enum CONFIG_TYPE {
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
        Preferences preferences;
};

#endif