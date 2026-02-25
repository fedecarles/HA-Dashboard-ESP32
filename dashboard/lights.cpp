#include "lights.h"
#include "vars.h"
#include "ui.h"
#include <cstring>

static void (*_publish)(const char*, const char*) = nullptr;
static void (*_subscribe)(const char*) = nullptr;
static const LightConfig* _currentLight = nullptr;

static const LightConfig LIGHTS[] = {
    { "comedor_mesa",   "Comedor",       "esp32/comedor/light/mesa" },
    { "living_lampara", "Living",        "esp32/comedor/light/lampara" },
    { "dormg",          "Dormitorio G",  "esp32/dormitoriog/light" },
    { "dormc",          "Dormitorio C",  "esp32/dormitorioc/light" },
    { "office",         "Oficina Techo", "esp32/office/light" },
    { "office_pie",     "Oficina Pie",   "esp32/office/light/pie" }
};

void lights_setup() {
}

void lights_set_publish_func(void (*publish)(const char*, const char*)) {
    _publish = publish;
}

void lights_set_subscribe_func(void (*subscribe)(const char*)) {
    _subscribe = subscribe;
}

extern "C" {

void action_toggle_luz_oficina_t() {
    bool isChecked = get_var_luz_oficina_t_state();
    if (_publish) {
        _publish("esp32/office/light/set", isChecked ? "ON" : "OFF");
    }
}

void action_toggle_luz_oficina_l() {
    bool isChecked = get_var_luz_oficina_l_state();
    if (_publish) {
        _publish("esp32/office/light/pie/set", isChecked ? "ON" : "OFF");
    }
}

void action_toggle_luz_comedor() {
    bool isChecked = get_var_luz_comedor_state();
    if (_publish) {
        _publish("esp32/comedor/light/mesa/set", isChecked ? "ON" : "OFF");
    }
}

void action_toggle_luz_living() {
    bool isChecked = get_var_luz_living_state();
    if (_publish) {
        _publish("esp32/comedor/light/lampara/set", isChecked ? "ON" : "OFF");
    }
}

void action_toggle_luz_dormitorio_g() {
    bool isChecked = get_var_luz_dormitorio_g_state();
    if (_publish) {
        _publish("esp32/dormitoriog/light/set", isChecked ? "ON" : "OFF");
    }
}

void action_toggle_luz_dormitorio_c() {
    bool isChecked = get_var_luz_dormitorio_c_state();
    if (_publish) {
        _publish("esp32/dormitorioc/light/set", isChecked ? "ON" : "OFF");
    }
}

void action_config_comedor(lv_event_t* e) {
    (void)e;
    select_light("comedor_mesa");
}

void action_config_living(lv_event_t* e) {
    (void)e;
    select_light("living_lampara");
}

void action_config_dormg(lv_event_t* e) {
    (void)e;
    select_light("dormg");
}

void action_config_dormc(lv_event_t* e) {
    (void)e;
    select_light("dormc");
}

void action_config_office(lv_event_t* e) {
    (void)e;
    select_light("office");
}

void action_config_office_pie(lv_event_t* e) {
    (void)e;
    select_light("office_pie");
}

void action_go_to_main(lv_event_t* e) {
    (void)e;
    loadScreen(SCREEN_ID_MAIN);
}

} // extern "C"

void select_light(const char* id) {
    for (const auto& light : LIGHTS) {
        if (strcmp(light.id, id) == 0) {
            _currentLight = &light;
            set_var_config_screen(light.title);
            tick_screen(1);
            loadScreen(SCREEN_ID_CONFIG);

            char state_topic[128];
            snprintf(state_topic, sizeof(state_topic), "%s/brightness/state", _currentLight->mqtt_base);
            if (_subscribe) {
                _subscribe(state_topic);
            }
            return;
        }
    }
}

extern "C" void action_change_brightness(lv_event_t* e) {
    (void)e;
    if (!_currentLight || !_publish) return;

    int sliderValue = get_var_brightness();
    int mqttBrightness = map(sliderValue, 0, 100, 0, 255);

    char topic[128];
    snprintf(topic, sizeof(topic), "%s/brightness/set", _currentLight->mqtt_base);

    char payload[8];
    snprintf(payload, sizeof(payload), "%d", mqttBrightness);

    _publish(topic, payload);
}
