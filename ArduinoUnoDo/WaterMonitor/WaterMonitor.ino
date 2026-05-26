/*********************************************************************
 * WaterMonitor.ino - Enhanced KnowFlow with IoT, Calibration, and Power Management
 *
 * Copyright (C)    2024   KnowFlow Team
 * Enhanced version with WiFi/IoT connectivity, calibration, and power management
 *
 * Description:
 * Enhanced water quality monitoring system with:
 * - WiFi/IoT connectivity via MQTT
 * - Automatic sensor calibration
 * - Power management with sleep modes
 * - Battery monitoring and solar charging support
 * - Real-time data transmission
 *
 * Hardware platform   : Arduino Uno with WiFi shield or ESP32
 * New features added  : IoT connectivity, calibration, power management
 * version :  V2.0
 * date    :  2024-07-21
 **********************************************************************/

#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <EEPROM.h>
#include "config.h"

// Core modules
#include "GravitySensorHub.h"
#include "GravityRtc.h"
#include "SdService.h"
#include "Debug.h"

// New enhanced features
#include "IoTService.h"
#include "CalibrationService.h"
#include "PowerManager.h"

// Clock module
GravityRtc rtc;

// Sensor monitoring
GravitySensorHub sensorHub;
SdService sdService = SdService(sensorHub.sensors);

// New services
IoTService iotService;
CalibrationService calibrationService(&sensorHub, &sdService);
PowerManager powerManager;

// System state
unsigned long lastUpdateTime = 0;
unsigned long updateInterval = 5000; // 5 seconds between readings
bool systemInitialized = false;

void setup() {
    Serial.begin(DEBUG_BAUD_RATE);
    Serial.println(F("KnowFlow Enhanced Water Monitor v2.0"));
    Serial.println(F("====================================="));

    // Initialize EEPROM for calibration data
    EEPROM.begin(512);

    // Initialize RTC
    rtc.setup();

    // Initialize sensor hub
    sensorHub.setup();

    // Initialize SD service
    sdService.setup();

    // Initialize calibration service
    calibrationService.setup();

    // Initialize power manager
    PowerConfig powerConfig;
    powerConfig.sleepInterval = POWER_SLEEP_INTERVAL;
    powerConfig.lowBatteryThreshold = LOW_BATTERY_THRESHOLD;
    powerConfig.criticalBatteryThreshold = CRITICAL_BATTERY_THRESHOLD;
    powerConfig.enableBatteryMonitoring = ENABLE_BATTERY_MONITORING;
    powerConfig.enableSensorPowerControl = ENABLE_SENSOR_POWER_CONTROL;
    powerConfig.enableSolarCharging = ENABLE_SOLAR_CHARGING;

    powerManager.setup(powerConfig);

    // Initialize IoT service (WiFi/MQTT)
    Serial.print(F("Initializing IoT service..."));
    iotService.setup(WIFI_SSID, WIFI_PASSWORD, MQTT_SERVER, MQTT_PORT);
    Serial.println(F("OK"));

    systemInitialized = true;
    Serial.println(F("System initialization complete!"));
    Serial.println(F("====================================="));
}

void loop() {
    if (!systemInitialized) return;

    unsigned long currentTime = millis();

    // Update all services
    rtc.update();
    sensorHub.update();
    sdService.update();
    calibrationService.loop();
    powerManager.loop();
    iotService.loop();

    // Main update cycle
    if (currentTime - lastUpdateTime > updateInterval) {
        lastUpdateTime = currentTime;

        // Get all sensor readings
        float ph = sensorHub.getValueBySensorNumber(0);
        float temp = sensorHub.getValueBySensorNumber(1);
        float doValue = sensorHub.getValueBySensorNumber(2);
        float ec = sensorHub.getValueBySensorNumber(3);
        float orp = sensorHub.getValueBySensorNumber(4);

        // Print readings
        printSensorReadings(ph, temp, doValue, ec, orp);

        // Publish to IoT
        if (iotService.isConnected()) {
            iotService.publishData(ph, temp, doValue, ec, orp);
        }

        // Check for calibration commands
        handleSerialCommands();
    }
}

void printSensorReadings(float ph, float temp, float doValue, float ec, float orp) {
    Serial.println(F("=== Current Readings ==="));
    Serial.print(F("pH:        "));
    Serial.println(ph, 2);
    Serial.print(F("Temperature: "));
    Serial.println(temp, 2);
    Serial.print(F("DO:        "));
    Serial.println(doValue, 2);
    Serial.print(F("EC:        "));
    Serial.println(ec, 2);
    Serial.print(F("ORP:       "));
    Serial.println(orp, 2);

    // Print battery status
    Serial.print(F("Battery:   "));
    Serial.print(powerManager.getBatteryVoltage(), 2);
    Serial.print(F("V ("));
    Serial.print(powerManager.getBatteryPercentage());
    Serial.println(F("%)"));

    Serial.print(F("WiFi:      "));
    Serial.println(iotService.isConnected() ? F("Connected") : F("Disconnected"));
    Serial.println(F("========================"));
}

void handleSerialCommands() {
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        command.trim();

        if (command == "calibrate_ph") {
            Serial.println(F("Starting pH calibration..."));
            calibrationService.startCalibration(CALIBRATION_PH_3POINT);
        } else if (command == "calibrate_ec") {
            Serial.println(F("Starting EC calibration..."));
            calibrationService.startCalibration(CALIBRATION_EC_1POINT);
        } else if (command == "calibrate_do") {
            Serial.println(F("Starting DO calibration..."));
            calibrationService.startCalibration(CALIBRATION_DO_2POINT);
        } else if (command == "calibrate_orp") {
            Serial.println(F("Starting ORP calibration..."));
            calibrationService.startCalibration(CALIBRATION_ORP_1POINT);
        } else if (command == "sleep") {
            Serial.println(F("Entering sleep mode..."));
            powerManager.enterSleepMode();
        } else if (command == "deep_sleep") {
            Serial.println(F("Entering deep sleep mode..."));
            powerManager.enterDeepSleepMode();
        } else if (command == "battery") {
            Serial.print(F("Battery: "));
            Serial.print(powerManager.getBatteryVoltage());
            Serial.print(F("V ("));
            Serial.print(powerManager.getBatteryPercentage());
            Serial.println(F("%)"));
        } else if (command == "help") {
            printHelp();
        }
    }
}

void printHelp() {
    Serial.println(F("KnowFlow Enhanced Commands:"));
    Serial.println(F("  calibrate_ph   - Start pH 3-point calibration"));
    Serial.println(F("  calibrate_ec   - Start EC 1-point calibration"));
    Serial.println(F("  calibrate_do   - Start DO 2-point calibration"));
    Serial.println(F("  calibrate_orp  - Start ORP 1-point calibration"));
    Serial.println(F("  sleep          - Enter sleep mode"));
    Serial.println(F("  deep_sleep     - Enter deep sleep mode"));
    Serial.println(F("  battery        - Show battery status"));
    Serial.println(F("  help           - Show this help"));
}
