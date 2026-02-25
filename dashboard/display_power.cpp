#include <Arduino.h>
#include "display_power.h"

static Board* _board = nullptr;
static bool _displaySleeping = false;
static unsigned long _lastTouchTime = 0;
static const unsigned long DISPLAY_TIMEOUT = 60000;

void display_power_init(Board* board) {
    _board = board;
    _lastTouchTime = millis();
}

void display_power_loop() {
    unsigned long now = millis();
    if (!_displaySleeping && (now - _lastTouchTime > DISPLAY_TIMEOUT)) {
        display_power_sleep();
    }
}

void display_power_wake() {
    _lastTouchTime = millis();
    if (_displaySleeping && _board) {
        auto bl = _board->getBacklight();
        if (bl) {
            bl->on();
        }
        _displaySleeping = false;
        Serial.println("Display waking");
    }
}

void display_power_sleep() {
    if (!_displaySleeping && _board) {
        auto bl = _board->getBacklight();
        if (bl) {
            bl->off();
        }
        _displaySleeping = true;
        Serial.println("Display sleeping");
    }
}

void display_power_touch_activity() {
    _lastTouchTime = millis();
    if (_displaySleeping) {
        display_power_wake();
    }
}
