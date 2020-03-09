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

#include "sps30.hpp"
#include "sensirion/sensirion_shdlc.h"

#define SPS30_ADDR 0x00
#define SPS30_CMD_START_MEASUREMENT 0x00
#define SPS30_CMD_STOP_MEASUREMENT 0x01
#define SPS30_SUBCMD_MEASUREMENT_START                                         \
    { 0x01, 0x03 }
#define SPS30_CMD_READ_MEASUREMENT 0x03
#define SPS30_CMD_FAN_CLEAN_INTV 0x80
#define SPS30_CMD_FAN_CLEAN_INTV_LEN 5
#define SPS30_SUBCMD_READ_FAN_CLEAN_INTV 0x00
#define SPS30_CMD_START_FAN_CLEANING 0x56
#define SPS30_CMD_DEV_INFO 0xd0
#define SPS30_CMD_DEV_INFO_SUBCMD_GET_SERIAL                                   \
    { 0x03 }
#define SPS30_CMD_RESET 0xd3
#define SPS30_ERR_STATE(state) (SPS30_ERR_STATE_MASK | (state))

SPS30::SPS30() : Sensor()
{
    //this->serialPort.begin(115200,SERIAL_8N1);
    this->data.pm10 = -1;
    this->data.pm4 = -1;
    this->data.pm25 = -1;
    this->data.pm1 = -1;
}

SPS30::~SPS30()
{
}

void SPS30::handle()
{
  sps30_probe();
  if (startMeasurementInt() != 0) {
      Serial.write("error starting measurement\n");
  }
}


int16_t SPS30::sps30_get_serial(char *serial) {
    struct sensirion_shdlc_rx_header header;
    uint8_t param_buf[] = SPS30_CMD_DEV_INFO_SUBCMD_GET_SERIAL;
    int16_t ret;

    ret = sensirion_shdlc_xcv(SPS30_ADDR, SPS30_CMD_DEV_INFO, sizeof(param_buf),
                              param_buf, SPS30_MAX_SERIAL_LEN, &header,
                              (uint8_t *)serial);
    if (ret < 0)
        return ret;

    if (header.state)
        return SPS30_ERR_STATE(header.state);

    return 0;
}

int16_t SPS30::sps30_probe() {
    char serial[SPS30_MAX_SERIAL_LEN];
    int16_t ret = sps30_get_serial(serial);

    return ret;
}

void SPS30::setup()
{
  Serial.begin(115200);
  sensirion_uart_open();
}

sensorData SPS30::getData()
{
  if (this->readMeasurement() != 0) {
      Serial.write("error reading measurement\n");
  }else{
      data.pm1 = this->measurement.count_pm1;
      data.pm25 = this->measurement.count_pm2_5;
      data.pm4 = this->measurement.count_pm4;
      data.pm10 = this->measurement.count_pm10;
  }
  return data;
}


int SPS30::startMeasurementInt()
{
    struct sensirion_shdlc_rx_header header;
    uint8_t param_buf[] = SPS30_SUBCMD_MEASUREMENT_START;

    return sensirion_shdlc_xcv(SPS30_ADDR, SPS30_CMD_START_MEASUREMENT,
                               sizeof(param_buf), param_buf, 0, &header, NULL);
}

int SPS30::stopMeasurement()
{
    struct sensirion_shdlc_rx_header header;

    return sensirion_shdlc_xcv(SPS30_ADDR, SPS30_CMD_STOP_MEASUREMENT, 0, NULL,
                               0, &header, NULL);
}

int SPS30::readMeasurement()
{
    struct sensirion_shdlc_rx_header header;
    int16_t ret;
    uint16_t idx;
    union {
        uint16_t u16_value[2];
        uint32_t u32_value;
        float32_t f32_value;
    } val, data[10];

    ret = sensirion_shdlc_xcv(SPS30_ADDR, SPS30_CMD_READ_MEASUREMENT, 0, NULL,
                              sizeof(data), &header, (uint8_t *)data);
    if (ret)
        return ret;

    if (header.data_len != sizeof(data))
        return SPS30_ERR_NOT_ENOUGH_DATA;

    idx = 0;
    val.u32_value = be32_to_cpu(data[idx].u32_value);
    this->measurement.mass_pm1 = val.f32_value;
    ++idx;
    val.u32_value = be32_to_cpu(data[idx].u32_value);
    this->measurement.mass_pm2_5 = val.f32_value;
    ++idx;
    val.u32_value = be32_to_cpu(data[idx].u32_value);
    this->measurement.mass_pm4 = val.f32_value;
    ++idx;
    val.u32_value = be32_to_cpu(data[idx].u32_value);
    this->measurement.mass_pm10 = val.f32_value;
    ++idx;
    val.u32_value = be32_to_cpu(data[idx].u32_value);
    //this->measurement.count_pm0_5 = val.f32_value;
    ++idx;
    val.u32_value = be32_to_cpu(data[idx].u32_value);
    this->measurement.count_pm1 = val.f32_value;
    ++idx;
    val.u32_value = be32_to_cpu(data[idx].u32_value);
    this->measurement.count_pm2_5 = val.f32_value;
    ++idx;
    val.u32_value = be32_to_cpu(data[idx].u32_value);
    this->measurement.count_pm4 = val.f32_value;
    ++idx;
    val.u32_value = be32_to_cpu(data[idx].u32_value);
    this->measurement.count_pm10 = val.f32_value;
    ++idx;
    val.u32_value = be32_to_cpu(data[idx].u32_value);
    //this->measurement.typical_particle_size = val.f32_value;

    if (header.state)
        return SPS30_ERR_STATE(header.state);

    return 0;
}

void SPS30::startMeasurement() {

}
boolean SPS30::measurementStatus() {
    return true;
}
