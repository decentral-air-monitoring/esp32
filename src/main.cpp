// General project definitions
#include "common.hpp"

// Board-specific
#include "heltec.h"
// Peripherie

// Include Other parts

// Globals
OPERATION_MODE op_mode;
AirQualityWifi air_wifi;

void setup() {
  Serial.begin(115200);
  // Setup Configuration
  initConfig();
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  // Check Mode
  if(preferences.getBool("configured", false)) {
    // Start normal operation
    Serial.println("operation mode");
    op_mode = normal;
  } else {
    // Enter config mode
    Serial.println("configuration mode");
    op_mode = config;
  }
  air_wifi.init();
  /* Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Connecting with");
  Heltec.display->drawString(0, 10, ssid);
  Heltec.display->display();

  // Print out success
  Heltec.display->clear();
  Heltec.display->drawString(0,0,"Connected!");
  Heltec.display->drawString(0,10,WiFi.localIP().toString());
  Heltec.display->display();
  Serial.println("Connected!");
  Serial.println(WiFi.localIP().toString());
  // ToDo: PubSubClient */
}

void loop() {
}