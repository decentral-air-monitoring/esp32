#include "Display.hpp"

Display::Display() {
}

void Display::init() {
    Heltec.display->clear();
    switch(op_mode) {
        case config:
            Heltec.display->drawString(0, 0, "Config Mode");
            Heltec.display->drawString(0, 10, ConfigModeSSID);
        break;
        case normal:
            Heltec.display->drawString(0, 0, "Normal Operation");
        break;
    } 
    this->update();
}

void Display::update() {
    Heltec.display->display();
}