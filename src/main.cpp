// General project definitions
#include "common.hpp"

// Peripherie

// Include Other parts

// Globals
OPERATION_MODE op_mode;
AirQualityWifi air_wifi;
Display display;
ConfigMode config_mode;
SerialTerminal terminal;
Config configuration;
MQTT mqtt;

// Timing data
unsigned long last_read = 0;
unsigned long read_interval = 0;

DemoSensor sensor;

void setup() {
  Serial.begin(115200);
  // Setup Configuration
  configuration.init();
  sensor = DemoSensor();
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  terminal.init();
  // Check Mode
  if(configuration.getBool("CONFIGURED")) {
    // Start normal operation
    Serial.println("operation mode");
    op_mode = normal;
  } else {
    // Enter config mode
    Serial.println("configuration mode");
    op_mode = config;
  }
  air_wifi.init();
  display.init();
  
  // Readout Timing
  read_interval = configuration.getInt("READ_INTERVAL")*1000;

  if(op_mode == config) {
    config_mode.init();
  } else {
    mqtt.init();
  }
  /* 

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
  air_wifi.handle();
  if(op_mode == config) {
    config_mode.handle();
  } else {
    mqtt.handle();
    sensor.handle();
    // Check if it's time for an readout
    if(millis() - last_read > read_interval) {
      last_read = millis();
      // ToDo: Call sensor.read()
      // ToDo: Call MQTT transmit
      // ToDo: Call LoRa transmit
      sensorData data = sensor.getData();
      mqtt.send(data);
    }
  }
  terminal.handle();
}