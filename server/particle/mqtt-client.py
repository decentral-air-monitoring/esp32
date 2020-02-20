import paho.mqtt.client as mqtt
from influxwrite import InfluxWrite
from settings import mqtt_credentials, config


###############################################################################
#   mqtt callback functions
###############################################################################


def on_connect(client, userdata, flags, rc):
    """
    The callback for when the client receives a CONNACK response from the
    server.
    :param client:
    :param userdata:
    :param flags:
    :param rc:
    :return: nothing
    """
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe(config.MQTT_TOPIC)


def on_message(client, userdata, msg):
    """
    The callback for when a PUBLISH message is received from the server.
    :param client:
    :param userdata:
    :param msg: object containing received mqtt message
    :return: nothing
    """
    global InfluxWrite.model_values
    global InfluxWrite.store_data
    try:
        print(msg.topic+" "+str(msg.payload))
        sensorData = InfluxWrite.model_values(msg)
        InfluxWrite.store_data(sensorData)
    except Exception as e:
        print(e)
    


###############################################################################
#   mqtt client configuration
###############################################################################

# Create Client Object
client = mqtt.Client()

# Execute on_connect function in case of client event: on_connect
client.on_connect = on_connect
# Execute on_message function in case of client event: on_message
client.on_message = on_message
# Make TLS configuration (using default values)
client.tls_set()
#
client.username_pw_set(username=mqtt_credentials.USERNAME,
                       password=mqtt_credentials.PASSWORD)
client.connect(host=config.MQTT_HOST, port=config.MQTT_PORT,
               keepalive=config.MQTT_KEEPALIVE)

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_forever()
