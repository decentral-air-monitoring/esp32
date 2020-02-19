#ifndef COMMON_HPP
#define COMMON_HPP

#include <Arduino.h>
#include "heltec.h"
#include "Config.hpp"
#include "AirQualityWiFi.hpp"
#include "Display.hpp"
#include "ConfigMode.hpp"


enum OPERATION_MODE {config, normal};
extern OPERATION_MODE op_mode;

#endif