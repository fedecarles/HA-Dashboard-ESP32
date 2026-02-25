#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include "mqtt_client.h"

static std::function<void(char*, uint8_t*, unsigned int)> _userCallback;

MqttClient::MqttClient(const char* server, int port, const char* user, const char* password)
    : _client(_espClient), _server(server), _port(port), _user(user), _password(password), _clientId("esp32_eez_4_3") {
}

void MqttClient::begin() {
    _client.setServer(_server, _port);
    _client.setCallback(callbackWrapper);
}

void MqttClient::loop() {
    if (!_client.connected()) {
        reconnect();
    }
    _client.loop();
}

bool MqttClient::isConnected() {
    return _client.connected();
}

void MqttClient::publish(const char* topic, const char* payload) {
    _client.publish(topic, payload);
}

void MqttClient::subscribe(const char* topic) {
    _client.subscribe(topic);
}

void MqttClient::setCallback(std::function<void(char*, uint8_t*, unsigned int)> callback) {
    _userCallback = callback;
}

void MqttClient::reconnect() {
    while (!_client.connected()) {
        if (_client.connect(_clientId, _user, _password)) {
            Serial.println("MQTT connected");
            _client.subscribe("esp32/office/light/state");
            _client.subscribe("esp32/office/light/brightness/state");
        } else {
            delay(2000);
        }
    }
}

void MqttClient::callbackWrapper(char* topic, uint8_t* payload, unsigned int length) {
    if (_userCallback) {
        _userCallback(topic, payload, length);
    }
}

static MqttClient* _mqttInstance = nullptr;

void mqtt_setup() {
    if (!_mqttInstance) {
        _mqttInstance = new MqttClient(MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_PASS);
        _mqttInstance->begin();
    }
}

void mqtt_loop() {
    if (_mqttInstance) {
        _mqttInstance->loop();
    }
}

bool mqtt_is_connected() {
    return _mqttInstance && _mqttInstance->isConnected();
}

void mqtt_publish(const char* topic, const char* payload) {
    if (_mqttInstance) {
        _mqttInstance->publish(topic, payload);
    }
}

void mqtt_subscribe(const char* topic) {
    if (_mqttInstance) {
        _mqttInstance->subscribe(topic);
    }
}

void mqtt_set_callback(std::function<void(char*, uint8_t*, unsigned int)> callback) {
    if (_mqttInstance) {
        _mqttInstance->setCallback(callback);
    }
}
