#ifndef SERIAL_HPP
#define SERIAL_HPP

#include "common.hpp"

#define SERIAL_BUF_LENGTH 20

class SerialTerminal {
    public:
        SerialTerminal();
        void init();
        void handle();
        void printHelp();
        void printConfiguration();
    private:
        void receive();
        char serialBuffer[SERIAL_BUF_LENGTH];
        uint8_t serialBufferPointer = 0;
};

#endif