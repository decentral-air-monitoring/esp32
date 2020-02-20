from influxdb import InfluxDBClient
import logging
from settings import mqtt_credentials, influx_credentials, config

###############################################################################
# InfluxDB
###############################################################################

class InfluxWrite:
    global model_values
    def model_values(msg):
        """

        :param msg:
        :return:
        """
        try:
            stationID, statuscode, pm1, pm2_5, pm4, pm10, temperature, humidity, pressure = [int(value) for value in msg.payload.decode('utf-8').split(',')]
        except ValueError as err:
            logging.error(err.error, "wrong data format")

        sensorData = [
            {
                "measurement": "environment",
                "tags": {
                    "stationID": stationID,
                    "statuscode": statuscode
                },
                "fields":{
                    "temperature": temperature,
                    "humidity": humidity,
                    "pressure": pressure
                }
            },
            {
                "measurement": "particles",
                "tags": {
                    "stationID": stationID,
                    "statuscode": statuscode
                },
                "fields":{
                    "pm1": pm1,
                    "pm2_5": pm2_5,
                    "pm4": pm4,
                    "pm10": pm10
                }
            }
        ]

        return sensorData

    global store_data
    def store_data(sensorData):
        """

        :param sensorData:
        :return:
        """
        influx_client = InfluxDBClient(config.INFLUX_HOST, config.INFLUX_PORT, influx_credentials.USERNAME,
                                    influx_credentials.PASSWORD, config.INFLUX_DATABASE)

        if config.INFLUX_DATABASE in (item['name'] for item in influx_client.query('show databases').get_points()):
            logging.info("database already exists")
        else:
            influx_client.create_database(config.INFLUX_DATABASE)

        influx_client.write_points(sensorData)