#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "vars.h"

static const unsigned long WEATHER_INTERVAL = 1800000;
static unsigned long _lastWeatherCheck = 0;

void weather_setup() {
    weather_fetch();
}

void weather_loop() {
    unsigned long now = millis();
    if (now - _lastWeatherCheck > WEATHER_INTERVAL) {
        _lastWeatherCheck = now;
        weather_fetch();
    }
}

void weather_fetch() {
    if (WiFi.status() != WL_CONNECTED) return;

    HTTPClient http;
    http.begin("https://api.open-meteo.com/v1/forecast?latitude=-34.61&longitude=-58.38&current_weather=true");

    int httpCode = http.GET();
    if (httpCode == 200) {
        String payload = http.getString();

        StaticJsonDocument<1024> doc;
        DeserializationError error = deserializeJson(doc, payload);
        if (error == DeserializationError::Ok) {
            float temperature = doc["current_weather"]["temperature"];
            const char* time_str = doc["current_weather"]["time"];

            char temp_str[16];
            snprintf(temp_str, sizeof(temp_str), "%.0f°C", temperature);
            set_var_temp(temp_str);

            char date_str[16];
            snprintf(date_str, sizeof(date_str), "%.10s", time_str);
            set_var_date(date_str);

            Serial.println("Weather updated");
        }
    }
    http.end();
}
