#ifndef DISPLAY_POWER_H
#define DISPLAY_POWER_H

#include <esp_display_panel.hpp>

using namespace esp_panel::drivers;
using namespace esp_panel::board;

void display_power_init(Board* board);
void display_power_loop();
void display_power_wake();
void display_power_sleep();
void display_power_touch_activity();

#endif // DISPLAY_POWER_H
