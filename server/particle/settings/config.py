# specify the hostname/ip of the mqtt broker
MQTT_HOST = "particle.nodelove.eu"
# specify the server port on which the mqtt broker is listening
MQTT_PORT = 8883
MQTT_KEEPALIVE = 60
# sepcify the topic to subscribe to
MQTT_TOPIC = "test/#"


####
# InfluxDB
####

INFLUX_HOST = "localhost"
INFLUX_PORT = 8086
INFLUX_DATABASE = 'sensordata'