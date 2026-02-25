#include <Arduino.h>
#include <esp_display_panel.hpp>
#include <lvgl.h>
#include "lvgl_v8_port.h"
#include "vars.h"
#include "ui.h"
#include "secrets.h"
#include "mqtt_client.h"
#include "weather.h"
#include "display_power.h"
#include "lights.h"

using namespace esp_panel::drivers;
using namespace esp_panel::board;

#if LV_USE_LOG != 0
void my_print(const char *buf) {
  Serial.printf(buf);
  Serial.flush();
}
#endif

extern "C" void wake_display();

void setup_wifi() {
  delay(10);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}

void mqtt_message_callback(char* topic, uint8_t* payload, unsigned int length) {
  char msg[129];
  unsigned int len = length < 128 ? length : 128;
  for (unsigned int i = 0; i < len; i++) {
    msg[i] = (char)payload[i];
  }
  msg[len] = '\0';

  Serial.print("MQTT Received [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(msg);

  if (String(topic).indexOf("brightness/state") != -1) {
    int value = atoi(msg);
    set_var_brightness(value);
  }
}

static void mqtt_publish_wrapper(const char* topic, const char* payload) {
  mqtt_publish(topic, payload);
}

static void mqtt_subscribe_wrapper(const char* topic) {
  mqtt_subscribe(topic);
}

static void touch_activity_cb(lv_event_t* e) {
  (void)e;
  display_power_touch_activity();
}

Board* board = nullptr;

void setup() {
  Serial.begin(115200);

  board = new Board();
  board->init();
  assert(board->begin());

  setup_wifi();

  mqtt_setup();
  mqtt_set_callback(mqtt_message_callback);

  weather_setup();

#if LVGL_PORT_AVOID_TEARING_MODE
  auto lcd = board->getLCD();
  lcd->configFrameBufferNumber(LVGL_PORT_DISP_BUFFER_NUM);
#if ESP_PANEL_DRIVERS_BUS_ENABLE_RGB && CONFIG_IDF_TARGET_ESP32S3
  auto lcd_bus = lcd->getBus();
  if (lcd_bus->getBasicAttributes().type == ESP_PANEL_BUS_TYPE_RGB) {
    static_cast<BusRGB *>(lcd_bus)->configRGB_BounceBufferSize(lcd->getFrameWidth() * 10);
  }
#endif
#endif

  lvgl_port_init(board->getLCD(), board->getTouch());

  ui_init();

  lights_set_publish_func(mqtt_publish_wrapper);
  lights_set_subscribe_func(mqtt_subscribe_wrapper);
  lights_setup();

  display_power_init(board);
  lv_obj_add_event_cb(lv_scr_act(), touch_activity_cb, LV_EVENT_ALL, NULL);
}

void loop() {
  mqtt_loop();
  weather_loop();
  display_power_loop();
  delay(1000);
}
