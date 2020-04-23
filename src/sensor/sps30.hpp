/*
 * Copyright (c) 2018, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SPS30_HPP
#define SPS30_HPP
#include "common.hpp"
#include "Sensor.hpp"
#include "sensirion/sensirion_uart.hpp"
#include "sensirion/sensirion_arch_config.h"

#define SPS30_MAX_SERIAL_LEN 32
#define SPS30_ERR_NOT_ENOUGH_DATA (-1)
#define SPS30_ERR_STATE_MASK (0x100)
#define SPS30_IS_ERR_STATE(err_code) (((err_code) | 0xff) == 0x1ff)
#define SPS30_GET_ERR_STATE(err_code) ((err_code)&0xff)

struct receive_data {
    float32_t mass_pm1;
    float32_t mass_pm2_5;
    float32_t mass_pm4;
    float32_t mass_pm10;
    float32_t count_pm0_5;
    float32_t count_pm1;
    float32_t count_pm2_5;
    float32_t count_pm4;
    float32_t count_pm10;
    float32_t typical_particle_size;
};

class SPS30:public Sensor
{
private:
    int status;
    sensorData data;
    struct receive_data measurement;
    void setup();
    int startMeasurementInt();
    int stopMeasurement();
    int readMeasurement();
    int16_t sps30_probe();
    int16_t sps30_get_serial(char *);
    s16_t sps30_set_fan_auto_cleaning_interval(uint32_t);
    s16_t sps30_set_fan_auto_cleaning_interval_days(uint8_t);

public:
    SPS30();
    ~SPS30();
    void handle();
    sensorData getData();
    void startMeasurement();
    boolean measurementStatus();
};
#endif