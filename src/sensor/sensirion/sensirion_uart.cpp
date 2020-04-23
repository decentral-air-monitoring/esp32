#include "common.hpp"
#include "sensirion_uart.hpp"
#include "wiring_private.h"
#include "Arduino.h"
#include "sensirion_arch_config.h"

HardwareSerial SERIALDEVICE_SPS30(2);

#define BAUDRATE 115200  // baud rate of SPS30

int16_t sensirion_uart_select_port(uint8_t port) {
    return 0;
}

int16_t sensirion_uart_open() {

    SERIALDEVICE_SPS30.begin(BAUDRATE, SERIAL_8N1, RX2, TX2);
    return 0;
}

int16_t sensirion_uart_close() {
    SERIALDEVICE_SPS30.end();
    return 0;
}

int16_t sensirion_uart_tx(uint16_t data_len, const uint8_t *data) {
    return SERIALDEVICE_SPS30.write(data, data_len);
}

int16_t sensirion_uart_rx(uint16_t max_data_len, uint8_t *data) {
    int16_t i = 0;

    while (SERIALDEVICE_SPS30.available() > 0 && i < max_data_len) {
        data[i] = (uint8_t)SERIALDEVICE_SPS30.read();
        i++;
    }
    return i;
}

void sensirion_sleep_usec(uint32_t useconds) {
    delay((useconds / 1000) + 1);
}