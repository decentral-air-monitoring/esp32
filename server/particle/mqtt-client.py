import paho.mqtt.client as mqtt
import logging
from settings import mqtt_credentials, influx_credentials, config
from influxdb import InfluxDBClient

###############################################################################
# InfluxDB
###############################################################################

def model_values(msg):
    """

    :param msg:
    :return:
    """
    try:
        stationID, statuscode, pm1, pm2_5, pm4, pm10, temperature, humidity, pressure = msg.payload.decode('utf-8').split(',')
    except ValueError as err:
        logging.error(err.error, "wrong data format")

    sensorData = [
        {
            "measurement": "environment",
            "tags": {
                "stationID": int(stationID),
                "statuscode": int(statuscode)
            },
            "fields":{
                "temperature": int(temperature),
                "humidity": int(humidity),
                "pressure": int(pressure)
            }
        },
        {
            "measurement": "particles",
            "tags": {
                "stationID": int(stationID),
                "statuscode": int(statuscode)
            },
            "fields":{
                "pm1": int(pm1),
                "pm2_5": int(pm2_5),
                "pm4": int(pm4),
                "pm10": int(pm10)
            }
        }
    ]

    return sensorData

def store_data(sensorData):
    """

    :param sensorData:
    :return:
    """
    influx_client = InfluxDBClient(config.INFLUX_HOST, config.INFLUX_PORT, influx_credentials.USERNAME,
                                   influx_credentials.PASSWORD, config.INFLUX_DATABASE)

    if config.INFLUX_DATABASE in (item['name'] for item in client.query('show databases').get_points()):
        logging.info("database already exists")
    else:
        influx_client.create_database(config.INFLUX_DATABASE)

    influx_client.write_points(sensorData)

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
    global model_values
    global store_data
    try:
        print(msg.topic+" "+str(msg.payload))
        sensorData = model_values(msg)
        store_data(sensorData)
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
