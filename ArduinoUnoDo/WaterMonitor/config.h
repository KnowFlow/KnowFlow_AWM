#pragma once

// WiFi Configuration
#define WIFI_SSID "YourWiFiNetwork"
#define WIFI_PASSWORD "YourWiFiPassword"
#define MQTT_SERVER "your.mqtt.server.com"
#define MQTT_PORT 1883
#define MQTT_TOPIC "knowflow/data"
#define MQTT_CLIENT_ID "KnowFlowDevice"

// Power Management Configuration
#define POWER_SLEEP_INTERVAL 60000  // milliseconds (1 minute)
#define LOW_BATTERY_THRESHOLD 3.3   // Volts
#define CRITICAL_BATTERY_THRESHOLD 3.0  // Volts
#define ENABLE_BATTERY_MONITORING true
#define ENABLE_SENSOR_POWER_CONTROL true
#define ENABLE_SOLAR_CHARGING false

// Calibration Configuration
#define CALIBRATION_EEPROM_ADDR 0
#define ENABLE_AUTO_CALIBRATION true
#define CALIBRATION_STABILITY_TIME 10000  // milliseconds

// Sensor Pins (existing configuration)
#if defined(ARDUINO_ARCH_ESP32)
#define EC_PIN 34
#define PH_PIN 35
#define ORP_PIN 32
#define DO_PIN 33
#define BATTERY_MONITOR_PIN 36
#else
#define EC_PIN A1
#define PH_PIN A2
#define ORP_PIN A3
#define DO_PIN A4
#define BATTERY_MONITOR_PIN A7
#endif
#define TEMP_PIN 5
#define RTC_SDA A4
#define RTC_SCL A5

// DFRobot Gravity DFR0553 I2C ADS1115 16-bit ADC
#define ENABLE_DFR0553_ADC true
#define DFR0553_I2C_ADDRESS 0x48
#define DFR0553_FULL_SCALE_MV 6144.0f
#define DFR0553_EC_CHANNEL 0
#define DFR0553_PH_CHANNEL 1
#define DFR0553_ORP_CHANNEL 2
#define DFR0553_AUX_CHANNEL 3

// Power Control Pins
#define SENSOR_POWER_PIN 8
#define SOLAR_CHARGE_PIN 9

// SD Card Configuration
#define SD_CS_PIN 4
#define ENABLE_SD_LOGGING true

// Debug Configuration
#define ENABLE_DEBUG true
#define DEBUG_BAUD_RATE 9600
