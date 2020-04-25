#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "common.hpp"

#include <Preferences.h>

#define VALUE_LENGTH 40

enum class CONFIG_TYPE {
    INT,
    BOOL,
    STRING,
    FALSE // in case of an error
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

        boolean setString(const char * key, const char * val);
        boolean setBool(const char * key, boolean val);
        boolean setInt(const char * key, int val);

        CONFIG_TYPE getType(const char * key);

        const config_item keys[KEY_AMOUNT] = {
            {"CONFIGURED", CONFIG_TYPE::BOOL, {.b = false }},
            {"CONFIG_AP_NAME", CONFIG_TYPE::STRING, {.s = "Particle-Config"}},
            {"READ_INTERVAL", CONFIG_TYPE::INT, {.i = 10}},
            {"MQTT_PORT", CONFIG_TYPE::INT, {.i = 8883}},
            {"MQTT_SERVER", CONFIG_TYPE::STRING, {.s = "particle.nodelove.eu"}},
            {"MQTT_TOPIC", CONFIG_TYPE::STRING, {.s = "particle"}},
            {"MQTT_USER", CONFIG_TYPE::STRING, {.s = "demosensor"}},
            {"MQTT_PASSWORD", CONFIG_TYPE::STRING, {.s = "demopass"}},
            {"MQTT_TLS", CONFIG_TYPE::BOOL, {.b = true}},
            {"MQTT_RECONNECT", CONFIG_TYPE::INT, {.i = 10}},
            {"STA_SSID", CONFIG_TYPE::STRING, {.s = "demossid"}},
            {"STA_PASS", CONFIG_TYPE::STRING, {.s = "demopass"}},
            {"WIFI_RECONNECT", CONFIG_TYPE::INT, {.i = 10}},
            {"SENSOR_TYPE", CONFIG_TYPE::INT, {.i = 0}},
            {"AIR_SENSOR_TYPE", CONFIG_TYPE::INT, {.i = 0}},
            {"STATION_ID", CONFIG_TYPE::INT, {.i = -1}},
            {"LORA_ENABLED", CONFIG_TYPE::BOOL, {.b = false}},
            {"TTN_DEV_EUI", CONFIG_TYPE::STRING, {.s = ""}},
            {"TTN_APP_EUI", CONFIG_TYPE::STRING, {.s = ""}},
            {"TTN_APP_KEY", CONFIG_TYPE::STRING, {.s = ""}}
        };
    private:
        Preferences preferences;
        boolean itemExists(const char * item);
        boolean itemExists(const char * item, char *d);
        boolean itemExists(const char * item, int * d);
        boolean itemExists(const char * item, boolean * d);
};

#endif