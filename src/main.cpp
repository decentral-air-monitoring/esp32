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

PubSubClient client;
WiFiClient espClient;
WiFiClientSecure espClientSecure;


#define MQTT_LENGTH 25
// ToDo: Cleanup/Refactor in class
char mqttServer[MQTT_LENGTH] = "";
int mqttPort = 0;
char mqttUser[MQTT_LENGTH] = "";
char mqttPassword[MQTT_LENGTH] = "";
boolean mqttState = false;

void setup() {
  Serial.begin(115200);
  // Setup Configuration
  configuration.init();
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
  if(op_mode == config) {
    config_mode.init();
  } else {
    // MQTT test stuff
    configuration.getString("MQTT_SERVER").toCharArray(mqttServer,MQTT_LENGTH);
    configuration.getString("MQTT_USER").toCharArray(mqttUser,MQTT_LENGTH);
    configuration.getString("MQTT_PASSWORD").toCharArray(mqttPassword,MQTT_LENGTH);
    mqttPort = configuration.getInt("MQTT_PORT");
    if(configuration.getBool("MQTT_TLS")) {
      // MQTT with TLS
      client.setClient(espClientSecure);
      Serial.println("Start MQTT with TLS");
    } else {
      // No TLS
      client.setClient(espClient);
      Serial.println("Start MQTT without TLS");
    }
    client.setServer(mqttServer, mqttPort);
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
  if(op_mode == config) {
    config_mode.handle();
  } else {
    // Try to connect to MQTT
    if(WiFi.isConnected()) {
      
      if(!mqttState) {
        // 
        Serial.printf("Connecting to MQTT as user %s\n",mqttUser);
        if (client.connect("ESP32Client",mqttUser,mqttPassword)) {
          Serial.println("connected");
          mqttState = true;
          client.publish("particle", "42,42,42,42,42,42,42,42,42");
        
        } else {
  
          Serial.print("failed with state ");
          Serial.print(client.state());
          mqttState = true; //Temp: Set to true to avoid blocking  
        }
      }
    }
  }
  terminal.handle();
}