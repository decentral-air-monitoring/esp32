#include <Arduino.h>
// ESP32-specific
#include <WiFi.h>
// Board-specific
#include "heltec.h"
// Peripherie

// Data

char ssid[] = "ffm.freifunk.net"; // ToDo: Dynamic configurable

void setup() {
  Serial.begin(115200);
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  // Connect to WiFi
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Connecting with");
  Heltec.display->drawString(0, 10, ssid);
  Heltec.display->display();
  Serial.printf("Connect with %s\n",ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid);
  // Wait for connection
  while(!WiFi.isConnected()); // ToDo: Rebuild with events
  // Print out success
  Heltec.display->clear();
  Heltec.display->drawString(0,0,"Connected!");
  Heltec.display->drawString(0,10,WiFi.localIP().toString());
  Heltec.display->display();
  Serial.println("Connected!");
  Serial.println(WiFi.localIP().toString());
  // ToDo: PubSubClient
}

void loop() {
}