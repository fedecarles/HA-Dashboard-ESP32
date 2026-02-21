#include <Arduino.h>
#include <esp_display_panel.hpp>
#include <lvgl.h>
#include "lvgl_v8_port.h"
#include <vars.h>
#include <ui.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <secrets.h>

using namespace esp_panel::drivers;
using namespace esp_panel::board;

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

const char* mqtt_server = MQTT_SERVER;
const int mqtt_port = MQTT_PORT;
const char* mqtt_user = MQTT_USER;
const char* mqtt_pass = MQTT_PASS;

WiFiClient espClient;
PubSubClient client(espClient);

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char *buf) {
  Serial.printf(buf);
  Serial.flush();
}
#endif

extern "C" void wake_display();

// Wifi setup
void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void reconnect_mqtt() {
  while (!client.connected()) {
    if (client.connect("esp32_eez_4_3", mqtt_user, mqtt_pass)) {
      Serial.println("MQTT connected");
      client.subscribe("esp32/office/light/state");
      client.subscribe("esp32/office/light/brightness/state");
    } else {
      delay(2000);
    }
  }
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    String msg;

    for (unsigned int i = 0; i < length; i++) {
        msg += (char)payload[i];
    }

    Serial.print("MQTT Received [");
    Serial.print(topic);
    Serial.print("]: ");
    Serial.println(msg);

    if (String(topic) == "esp32/office/light/brightness/state") {
        int value = msg.toInt();
        set_var_brightness(value);
    }
}

// variables
bool luz_comedor_state;
bool luz_living_state;
bool luz_dormitorio_c_state;
bool luz_dormitorio_g_state;
bool luz_oficina_t_state;
bool luz_oficina_l_state;
char temp[100] = { 0 };
unsigned long lastWeatherCheck = 0;
const unsigned long weatherInterval = 1800000; // 30 mins
unsigned long lastTouchTime = 0;
const unsigned long displayTimeout = 60000;
bool displaySleeping = false;
char date[100] = { 0 };
int32_t brightness;
char config_screen[100] = { 0 };

Board *board = nullptr;

struct LightConfig {
    const char* id;
    const char* title;
    const char* mqtt_base;
};

LightConfig lights[] = {
    { "comedor_mesa",   "Comedor",       "esp32/comedor/light/mesa" },
    { "living_lampara", "Living",        "esp32/comedor/light/lampara" },
    { "dormg",          "Dormitorio G",  "esp32/dormitoriog/light" },
    { "dormc",          "Dormitorio C",  "esp32/dormitorioc/light" },
    { "office",         "Oficina Techo", "esp32/office/light" },
    { "office_pie",     "Oficina Pie",   "esp32/office/light/pie" }
};

const LightConfig* currentLight = nullptr;

bool get_var_luz_comedor_state() {
    return luz_comedor_state;
}

void set_var_luz_comedor_state(bool value) {
    luz_comedor_state = value;
}

bool get_var_luz_living_state() {
    return luz_living_state;
}

void set_var_luz_living_state(bool value) {
    luz_living_state = value;
}

bool get_var_luz_dormitorio_c_state() {
    return luz_dormitorio_c_state;
}

void set_var_luz_dormitorio_c_state(bool value) {
    luz_dormitorio_c_state = value;
}

bool get_var_luz_dormitorio_g_state() {
    return luz_dormitorio_g_state;
}

void set_var_luz_dormitorio_g_state(bool value) {
    luz_dormitorio_g_state = value;
}

bool get_var_luz_oficina_t_state() {
    return luz_oficina_t_state;
}

void set_var_luz_oficina_t_state(bool value) {
    luz_oficina_t_state = value;
}

bool get_var_luz_oficina_l_state() {
    return luz_oficina_l_state;
}

void set_var_luz_oficina_l_state(bool value) {
    luz_oficina_l_state = value;
}

const char *get_var_temp() {
    return temp;
}

void set_var_temp(const char *value) {
    strncpy(temp, value, sizeof(temp) / sizeof(char));
    temp[sizeof(temp) / sizeof(char) - 1] = 0;
}

const char *get_var_date() {
    return date;
}

void set_var_date(const char *value) {
    strncpy(date, value, sizeof(date) / sizeof(char));
    date[sizeof(date) / sizeof(char) - 1] = 0;
}

int32_t get_var_brightness() {
    return brightness;
}

void set_var_brightness(int32_t value) {
    brightness = value;
}

const char *get_var_config_screen() {
    return config_screen;
}

void set_var_config_screen(const char *value) {
    strncpy(config_screen, value, sizeof(config_screen) / sizeof(char));
    config_screen[sizeof(config_screen) / sizeof(char) - 1] = 0;
}

extern "C" void action_toggle_luz_oficina_t() {
    bool isChecked = get_var_luz_oficina_t_state();  // EEZ-generated variable
    if (isChecked) {
        client.publish("esp32/office/light/set", "OFF");
        Serial.println("MQTT: Light OFF");
    } else {
        client.publish("esp32/office/light/set", "ON");
        Serial.println("MQTT: Light ON");
    }
}

extern "C" void action_toggle_luz_oficina_l() {
    bool isChecked = get_var_luz_oficina_l_state();  // EEZ-generated variable
    if (isChecked) {
        client.publish("esp32/office/light/pie/set", "OFF");
        Serial.println("MQTT: Light OFF");
    } else {
        client.publish("esp32/office/light/pie/set", "ON");
        Serial.println("MQTT: Light ON");
    }
}

extern "C" void action_toggle_luz_comedor() {
    bool isChecked = get_var_luz_comedor_state();  // EEZ-generated variable
    if (isChecked) {
        client.publish("esp32/comedor/light/mesa/set", "ON");
        Serial.println("MQTT: Light OFF");
    } else {
        client.publish("esp32/comedor/light/mesa/set", "OFF");
        Serial.println("MQTT: Light ON");
    }
}

extern "C" void action_toggle_luz_living() {
    bool isChecked = get_var_luz_living_state();  // EEZ-generated variable
    if (isChecked) {
        client.publish("esp32/comedor/light/lampara/set", "OFF");
        Serial.println("MQTT: Light OFF");
    } else {
        client.publish("esp32/comedor/light/lampara/set", "ON");
        Serial.println("MQTT: Light ON");
    }
}

extern "C" void action_toggle_luz_dormitorio_g() {
    bool isChecked = get_var_luz_dormitorio_g_state();  // EEZ-generated variable
    if (isChecked) {
        client.publish("esp32/dormitoriog/light/set", "OFF");
        Serial.println("MQTT: Light OFF");
    } else {
        client.publish("esp32/dormitoriog/light/set", "ON");
        Serial.println("MQTT: Light ON");
    }
}

extern "C" void action_toggle_luz_dormitorio_c() {
    bool isChecked = get_var_luz_dormitorio_c_state();  // EEZ-generated variable
    if (isChecked) {
        client.publish("esp32/dormitorioc/light/set", "OFF");
        Serial.println("MQTT: Light OFF");
    } else {
        client.publish("esp32/dormitorioc/light/set", "ON");
        Serial.println("MQTT: Light ON");
    }
}

extern "C" void action_config_comedor(lv_event_t * e) {
    select_light("comedor_mesa");
}

extern "C" void action_config_living(lv_event_t * e) {
    select_light("living_lampara");
}

extern "C" void action_config_dormg(lv_event_t * e) {
    select_light("dormg");
}

extern "C" void action_config_dormc(lv_event_t * e) {
    select_light("dormc");
}

extern "C" void action_config_office(lv_event_t * e) {
    select_light("office");
}

extern "C" void action_config_office_pie(lv_event_t * e) {
    select_light("office_pie");
}

extern "C" void action_go_to_main(lv_event_t *e) {
    loadScreen(SCREEN_ID_MAIN);
}

void select_light(const char* id) {

    for (auto &light : lights) {
        if (strcmp(light.id, id) == 0) {
            currentLight = &light;

            // Update title
            set_var_config_screen(light.title);
            tick_screen(1);

            // Go to config screen
            loadScreen(SCREEN_ID_CONFIG);
            
            char state_topic[128];
            snprintf(state_topic, sizeof(state_topic), "%s/brightness/state", currentLight->mqtt_base);
            client.subscribe(state_topic);

            Serial.print("Selected light: ");
            Serial.println(light.title);
            return;
        }
    }
}

extern "C" void action_change_brightness(lv_event_t * e) {

    if (!currentLight) return;

    int sliderValue = get_var_brightness();   // 0–100

    // Convert to 0–255
    int mqttBrightness = map(sliderValue, 0, 100, 0, 255);

    char topic[128];
    snprintf(topic, sizeof(topic), "%s/brightness/set", currentLight->mqtt_base);

    char payload[8];
    snprintf(payload, sizeof(payload), "%d", mqttBrightness);

    client.publish(topic, payload);

    Serial.print("Slider: ");
    Serial.print(sliderValue);
    Serial.print(" → MQTT: ");
    Serial.println(mqttBrightness);
}



void fetch_temperature_date() {
  if (WiFi.status() != WL_CONNECTED) return;

  HTTPClient http;
  http.begin("https://api.open-meteo.com/v1/forecast?latitude=-34.61&longitude=-58.38&current_weather=true");

  int httpCode = http.GET();
  if (httpCode == 200) {
    String payload = http.getString();

    StaticJsonDocument<1024> doc;
    if (deserializeJson(doc, payload) == DeserializationError::Ok) {
      float temperature = doc["current_weather"]["temperature"];
      const char* time_str = doc["current_weather"]["time"];
      Serial.println(time_str);

      char temp_str[16];
      snprintf(temp_str, sizeof(temp_str), "%.0f°C", temperature);
      set_var_temp(temp_str);
      Serial.println(temp);

      char date_str[16];
      // Extract YYYY-MM-DD from "YYYY-MM-DDTHH:MM"
      snprintf(date_str, sizeof(date_str), "%.10s", time_str);
      set_var_date(date_str);
      Serial.println(date);
    }
  }

  http.end();
}

void set_backlight(bool on) {
  if (!board) return;
  auto bl = board->getBacklight();
  if (bl) {
    if (on) bl->on();
    else bl->off();
  }
}

void lvgl_touch_activity_cb(lv_event_t * e) {
  lastTouchTime = millis();

  if (displaySleeping) {
    set_backlight(true);
    displaySleeping = false;
    Serial.println("Display waking");
  }
}

extern "C" void wake_display() {
  lastTouchTime = millis();
  if (displaySleeping) {
    set_backlight(true);
    displaySleeping = false;
    Serial.println("Display waking");
  }
}

void setup()
{

    Serial.begin(115200);

    //Board *board = new Board();
    board = new Board();
    board->init();
    assert(board->begin());

    setup_wifi();
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(mqtt_callback);

    fetch_temperature_date();

    #if LVGL_PORT_AVOID_TEARING_MODE
    auto lcd = board->getLCD();
    // When avoid tearing function is enabled, the frame buffer number should be set in the board driver
    lcd->configFrameBufferNumber(LVGL_PORT_DISP_BUFFER_NUM);
#if ESP_PANEL_DRIVERS_BUS_ENABLE_RGB && CONFIG_IDF_TARGET_ESP32S3
    auto lcd_bus = lcd->getBus();
    /**
     * As the anti-tearing feature typically consumes more PSRAM bandwidth, for the ESP32-S3, we need to utilize the
     * "bounce buffer" functionality to enhance the RGB data bandwidth.
     * This feature will consume `bounce_buffer_size * bytes_per_pixel * 2` of SRAM memory.
     */
    if (lcd_bus->getBasicAttributes().type == ESP_PANEL_BUS_TYPE_RGB) {
        static_cast<BusRGB *>(lcd_bus)->configRGB_BounceBufferSize(lcd->getFrameWidth() * 10);
    }
#endif
#endif

    // Initializing LVGL
    lvgl_port_init(board->getLCD(), board->getTouch());
    lv_indev_t * indev = lv_indev_get_next(NULL);
while (indev) {
  indev = lv_indev_get_next(indev);
}

    // EEZ Studio UI
    ui_init();

    // Register touch activity callback on the active screen
    lv_obj_add_event_cb(lv_scr_act(), lvgl_touch_activity_cb, LV_EVENT_ALL, NULL);
}

void loop() {
  if (!client.connected()) {
    reconnect_mqtt();
  }
  client.loop();

  unsigned long now = millis();

  if (!displaySleeping && (now - lastTouchTime > displayTimeout)) {
    set_backlight(false);
    displaySleeping = true;
    Serial.println("Display sleeping");
  }
  

  if (now - lastWeatherCheck > weatherInterval) {
    lastWeatherCheck = now;
    fetch_temperature_date();
  }

  delay(1000);
}

