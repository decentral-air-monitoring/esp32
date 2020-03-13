####
# MQTT
####

# specify the hostname/ip of the mqtt broker
MQTT_HOST = "particle.nodelove.eu"
# specify the server port on which the mqtt broker is listening
MQTT_PORT = 8883
MQTT_KEEPALIVE = 60
# sepcify the topic to subscribe to
MQTT_TOPIC = "particle/#"


####
# InfluxDB
####

INFLUX_HOST = "localhost"
INFLUX_PORT = 8086
INFLUX_DATABASE = 'sensordata'
INFLUX_INIT_DATA = 'initdata'

####
# Sensors
####

SENSORS = {
    "praticle":{
        0:"NoSensor",
        1:"DemoSensor",
        2:"SDS011",
        3: "HMPA115C0",
        4: "SPS30"
    },
    "environment":{
        0:"NoSensor",
        1:"BME680"
    }
}

####
# Connection Type
####

CONNECTION = {
    0: "NotSet",
    1: "LoraOnly",
    2: "WifiOnly",
    3: "LoraAndWifi"
}