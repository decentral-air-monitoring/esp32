#ifndef COMMON_HPP
#define COMMON_HPP

#include <Arduino.h>
#include "AirQualityWiFi.hpp"
#include "config.hpp"

enum OPERATION_MODE {config, normal};
extern OPERATION_MODE op_mode;

#endif