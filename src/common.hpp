#ifndef COMMON_HPP
#define COMMON_HPP

class Config;

#define TX2 21
#define RX2 22

#define I2C_SDA 13
#define I2C_SCL 17

#define INVAL -300000

#define KEY_LENGTH 20
#define KEY_AMOUNT 20

#include <Arduino.h>
#include <string>
#include <time.h>
#include <WebServer.h>
#include "heltec.h"
#include "Config.hpp"
#include "AirQualityWiFi.hpp"
#include "Display.hpp"
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