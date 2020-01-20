#ifndef CONFIGMODE_HPP
#define CONFIGMODE_HPP

#include "common.hpp"
#include <WebServer.h>

#define SERIAL_BUF_LENGTH 20

class ConfigMode {
    private:
        static WebServer::THandlerFunction formular();
        char serialBuffer[SERIAL_BUF_LENGTH];
    public:
        ConfigMode();
        void init();
        void handle();
        void serialReceive();
        WebServer server;
};

extern ConfigMode config_mode;

#endif