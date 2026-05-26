#pragma once

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

class IoTService {
public:
    IoTService();
    void setup(const char* ssid, const char* password, const char* mqtt_server, int mqtt_port = 1883);
    void loop();
    bool isConnected();
    void publishData(float ph, float temp, float doValue, float ec, float orp);
    void setPublishInterval(unsigned long interval);
    void setCalibrationMode(bool enabled);

private:
    WiFiClient wifiClient;
    PubSubClient mqttClient;
    unsigned long lastPublishTime;
    unsigned long publishInterval;
    bool calibrationMode;

    void connectWiFi();
    void connectMQTT();
    void reconnect();

    // WiFi credentials
    const char* _ssid;
    const char* _password;
    const char* _mqtt_server;
    int _mqtt_port;
};