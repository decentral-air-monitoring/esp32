#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "common.hpp"

#include <Preferences.h>

#define KEY_LENGTH 20
#define VALUE_LENGTH 40

enum class CONFIG_TYPE {
    INT,
    BOOL,
    STRING
};

struct config_item {
  char key[KEY_LENGTH];
  CONFIG_TYPE type;
  union default_value {
    boolean b;
    int i;
    char s[VALUE_LENGTH];
  } def;
};

class Config{
    public:
        Config();
        void init();
        boolean getBool(const char * key);
        String getString(const char * key);
        int getInt(const char * key);
        const config_item keys[3] = {
            {"CONFIGURED", CONFIG_TYPE::BOOL, {.b = false }},
            {"CONFIG_AP_NAME", CONFIG_TYPE::STRING, {.s = "Particle-Config"}},
            {"READ_INTERVAL", CONFIG_TYPE::INT, {.i = 60}}
        };
    private:
        Preferences preferences;
        boolean itemExists(const char * item);
        boolean itemExists(const char * item, char *d);
        boolean itemExists(const char * item, int * d);
        boolean itemExists(const char * item, boolean * d);
};

#endif