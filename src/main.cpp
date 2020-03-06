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

// Measurement state
boolean measurement_running = false;

Sensor* sensor;

void setup() {
  Serial.begin(115200);
  // Setup Configuration
  configuration.init();
  switch(configuration.getInt("SENSOR_TYPE")) {
    case 4:
      sensor = new SPS30();
      break;
    case 3:
      sensor = new HPMA115C0();
      break;
    case 2:
      sensor = new Sds_011();
      break;
    case 1:
      sensor = new DemoSensor();
      break;
    default:
      sensor = new DefaultSensor();
  }
  // sensor->init(); ToDo: Actively initialize the sensor if necessary
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
    sensor->handle();
    // If there is an measurement running and data available, send out data
    if(measurement_running && sensor->measurementStatus()) {
      measurement_running = false;
      // Send measurement data
      sensorData data = sensor->getData();
      mqtt.send(data);
    }
    // Check if it's time for an new readout
    if(millis() - last_read > read_interval) {
      last_read = millis();
      // Check if there is no measurement running
      if(!measurement_running) {
        // Start measurement
        sensor->startMeasurement();
        // Check if we have an immediate result
        if(sensor->measurementStatus()) {
          // Send measurement data
          sensorData data = sensor->getData();
          mqtt.send(data);
        } else {
          // set flag
          measurement_running = true;
        }
      }
      // ToDo: Call LoRa transmit
    }
  }
  terminal.handle();
}