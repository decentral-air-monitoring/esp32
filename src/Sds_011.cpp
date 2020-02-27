#include "Sds_011.hpp"

Sds_011::Sds_011() : Sensor()
{
    //my_sds.begin(&port);
}

Sds_011::~Sds_011()
{
}

void Sds_011::handle()
{
    /*time_t timer;
    int err;
    float p10, p25;
    my_sds.wakeup();

    err = my_sds.read(&p25, &p10);

    if (!err){
          data.pm25 = p25;
          data.pm10 = p10;
          data.time = time(&timer);
    }*/
}

sensorData Sds_011::getData()
{
    return data;
}