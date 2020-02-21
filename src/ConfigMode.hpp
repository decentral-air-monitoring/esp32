#ifndef CONFIGMODE_HPP
#define CONFIGMODE_HPP

#include "common.hpp"
#include <WebServer.h>

class ConfigMode {
    private:
        static WebServer::THandlerFunction formular();
    public:
        ConfigMode();
        void init();
        void handle();
        WebServer server;
};

extern ConfigMode config_mode;

#endif