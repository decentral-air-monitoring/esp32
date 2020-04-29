#ifndef COMMON_HPP
#define COMMON_HPP

class Config;

#ifdef ARDUINO_HELTEC_WIRELESS_STICK

#define TX2 21 //grün
#define RX2 22 //blau

#define I2C_SDA 13
#define I2C_SCL 17
#define OLED_AVAILABLE
#define LORA_AVAILABLE

#elif ARDUINO_HELTEC_WIRELESS_STICK_LITE

#define TX2 9 //grün
#define RX2 10 //blau

#define I2C_SDA 15
#define I2C_SCL 4

#else

#define TX2 21 //grün
#define RX2 22 //blau

#define I2C_SDA 13
#define I2C_SCL 17

#endif

#define INVAL -300000

#include <Arduino.h>
#include <string>
#include <time.h>
#include "heltec.h"
#include "Config.hpp"
#include "AirQualityWiFi.hpp"
#ifdef OLED_AVAILABLE
#include "Display.hpp"
#endif
#include "ConfigMode.hpp"
#include "SerialTerminal.hpp"
#include "Sensor.hpp"
#include "AirSensor.hpp"
#include "MQTT.hpp"
#include "TTN.hpp"

enum OPERATION_MODE {config, normal};
extern OPERATION_MODE op_mode;

extern Config configuration;
extern HardwareSerial SerialSensor;
extern boolean ledState;
#endif