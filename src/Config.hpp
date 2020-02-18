#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "common.hpp"

#include <Preferences.h>

void initConfig();

class Config{
    public:
        Config();
        void init();
    private:
        Preferences preferences;
};

#endif