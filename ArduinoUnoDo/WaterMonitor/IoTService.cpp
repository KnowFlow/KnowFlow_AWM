#include "IoTService.h"
#include "config.h"

IoTService::IoTService() :
    mqttClient(wifiClient),
    lastPublishTime(0),
    publishInterval(60000), // Default 1 minute
    calibrationMode(false) {
}

void IoTService::setup(const char* ssid, const char* password, const char* mqtt_server, int mqtt_port) {
    _ssid = ssid;
    _password = password;
    _mqtt_server = mqtt_server;
    _mqtt_port = mqtt_port;

    connectWiFi();
    mqttClient.setServer(_mqtt_server, _mqtt_port);
}

void IoTService::loop() {
    if (!mqttClient.connected()) {
        reconnect();
    }
    mqttClient.loop();
}

bool IoTService::isConnected() {
    return WiFi.status() == WL_CONNECTED && mqttClient.connected();
}

void IoTService::publishData(float ph, float temp, float doValue, float ec, float orp) {
    if (!isConnected()) return;

    unsigned long currentTime = millis();
    if (currentTime - lastPublishTime < publishInterval) return;

    StaticJsonDocument<200> doc;
    doc["timestamp"] = millis();
    doc["ph"] = ph;
    doc["temperature"] = temp;
    doc["dissolved_oxygen"] = doValue;
    doc["conductivity"] = ec;
    doc["orp"] = orp;
    doc["calibration_mode"] = calibrationMode;

    char jsonBuffer[200];
    serializeJson(doc, jsonBuffer);

    mqttClient.publish("knowflow/data", jsonBuffer);
    lastPublishTime = currentTime;
}

void IoTService::setPublishInterval(unsigned long interval) {
    publishInterval = interval;
}

void IoTService::setCalibrationMode(bool enabled) {
    calibrationMode = enabled;
}

void IoTService::connectWiFi() {
    WiFi.begin(_ssid, _password);

    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.print("Connected! IP address: ");
    Serial.println(WiFi.localIP());
}

void IoTService::connectMQTT() {
    mqttClient.setServer(_mqtt_server, _mqtt_port);

    while (!mqttClient.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (mqttClient.connect("KnowFlowClient")) {
            Serial.println("connected");
            mqttClient.subscribe("knowflow/commands");
        } else {
            Serial.print("failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void IoTService::reconnect() {
    while (!mqttClient.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (mqttClient.connect("KnowFlowClient")) {
            Serial.println("connected");
            mqttClient.subscribe("knowflow/commands");
        } else {
            Serial.print("failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}