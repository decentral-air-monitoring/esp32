#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "common.hpp"

class Display {
    public:
        Display();
        void init();
        void update();
};

extern Display display;

#endif