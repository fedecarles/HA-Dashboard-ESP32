#ifndef LIGHTS_H
#define LIGHTS_H

#include <Arduino.h>
#include <lvgl.h>
#include "screens.h"

struct LightConfig {
    const char* id;
    const char* title;
    const char* mqtt_base;
};

extern "C" {
    void action_toggle_luz_oficina_t();
    void action_toggle_luz_oficina_l();
    void action_toggle_luz_comedor();
    void action_toggle_luz_living();
    void action_toggle_luz_dormitorio_g();
    void action_toggle_luz_dormitorio_c();
    void action_config_comedor(lv_event_t* e);
    void action_config_living(lv_event_t* e);
    void action_config_dormg(lv_event_t* e);
    void action_config_dormc(lv_event_t* e);
    void action_config_office(lv_event_t* e);
    void action_config_office_pie(lv_event_t* e);
    void action_change_brightness(lv_event_t* e);
    void action_go_to_main(lv_event_t* e);
}

void lights_setup();
void lights_set_publish_func(void (*publish)(const char*, const char*));
void lights_set_subscribe_func(void (*subscribe)(const char*));
void select_light(const char* id);

#endif // LIGHTS_H
