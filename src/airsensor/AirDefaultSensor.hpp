#ifndef AIR_DEFAULT_SENSOR_HPP
#define AIR_DEFAULT_SENSOR_HPP
#include "AirSensor.hpp"
#include <stdlib.h>

class AirDefaultSensor : public AirSensor
{
private:
    airSensorData data;
public:
    AirDefaultSensor();
    ~AirDefaultSensor();
    void handle();
    airSensorData getData();
};
#endif
