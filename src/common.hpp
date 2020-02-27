#ifndef COMMON_HPP
#define COMMON_HPP

class Config;

#include <Arduino.h>
#include <string>
#include <time.h>
#include "heltec.h"
#include "Config.hpp"
#include "AirQualityWiFi.hpp"
#include "Display.hpp"
#include "ConfigMode.hpp"
#include "SerialTerminal.hpp"
#include "MQTT.hpp"
#include "Sensor.hpp"

enum OPERATION_MODE {config, normal};
extern OPERATION_MODE op_mode;

extern Config configuration;

#endif