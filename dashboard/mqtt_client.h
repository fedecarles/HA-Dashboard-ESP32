#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <stdint.h>
#include <PubSubClient.h>
#include <WiFiClient.h>

class MqttClient {
public:
    MqttClient(const char* server, int port, const char* user, const char* password);
    void begin();
    void loop();
    bool isConnected();
    void publish(const char* topic, const char* payload);
    void subscribe(const char* topic);
    void setCallback(std::function<void(char*, uint8_t*, unsigned int)> callback);

private:
    WiFiClient _espClient;
    PubSubClient _client;
    const char* _server;
    int _port;
    const char* _user;
    const char* _password;
    const char* _clientId;
    void reconnect();
    static void callbackWrapper(char* topic, uint8_t* payload, unsigned int length);
};

void mqtt_setup();
void mqtt_loop();
bool mqtt_is_connected();
void mqtt_publish(const char* topic, const char* payload);
void mqtt_subscribe(const char* topic);
void mqtt_set_callback(std::function<void(char*, uint8_t*, unsigned int)> callback);

#endif // MQTT_CLIENT_H
