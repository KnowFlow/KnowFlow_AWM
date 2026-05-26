#pragma once

#include <Arduino.h>

#if defined(ARDUINO_ARCH_AVR)
#include <avr/sleep.h>
#include <avr/power.h>
#elif defined(ARDUINO_ARCH_ESP32)
#include <esp_sleep.h>
#endif

enum PowerMode {
    POWER_MODE_NORMAL,
    POWER_MODE_SLEEP,
    POWER_MODE_DEEP_SLEEP,
    POWER_MODE_POWER_DOWN
};

struct PowerConfig {
    unsigned long sleepInterval = 60000; // Default 1 minute
    bool enableSensorPowerControl = true;
    bool enableBatteryMonitoring = true;
    bool enableSolarCharging = false;
    float lowBatteryThreshold = 3.3; // Volts
    float criticalBatteryThreshold = 3.0; // Volts
};

class PowerManager {
public:
    PowerManager();

    void setup(PowerConfig config);
    void loop();

    void enterSleepMode();
    void enterDeepSleepMode();
    void enterPowerDownMode();
    void wakeUp();

    float getBatteryVoltage();
    int getBatteryPercentage();
    bool isLowBattery();
    bool isCriticalBattery();

    void setSleepInterval(unsigned long interval);
    void enableSensorPower(bool enable);
    void enableSolarCharging(bool enable);

    PowerMode getCurrentPowerMode();

private:
    PowerConfig _config;
    PowerMode _currentMode;
    unsigned long _lastWakeTime;
    unsigned long _lastBatteryCheck;

    void powerDownSensors();
    void powerUpSensors();
    void configureSleepMode();
    void configureDeepSleepMode();
    void configurePowerDownMode();

    // Battery voltage calculation
    static constexpr float VREF = 5.0;
    static constexpr float VOLTAGE_DIVIDER = 0.5; // Assuming 1:1 voltage divider
};
