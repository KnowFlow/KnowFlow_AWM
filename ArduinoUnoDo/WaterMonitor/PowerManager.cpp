#include "PowerManager.h"
#include "config.h"

PowerManager::PowerManager() :
    _currentMode(POWER_MODE_NORMAL),
    _lastWakeTime(0),
    _lastBatteryCheck(0) {
}

void PowerManager::setup(PowerConfig config) {
    _config = config;
    _lastWakeTime = millis();

    // Configure power control pins
    pinMode(SENSOR_POWER_PIN, OUTPUT);
    pinMode(SOLAR_CHARGE_PIN, OUTPUT);
    pinMode(BATTERY_MONITOR_PIN, INPUT);

    // Enable sensors by default
    enableSensorPower(true);

    // Configure solar charging
    if (_config.enableSolarCharging) {
        enableSolarCharging(true);
    }

    Serial.println(F("Power manager initialized"));
    Serial.print(F("Sleep interval: "));
    Serial.print(_config.sleepInterval / 1000);
    Serial.println(F(" seconds"));
}

void PowerManager::loop() {
    unsigned long currentTime = millis();

    // Check battery status periodically
    if (_config.enableBatteryMonitoring &&
        (currentTime - _lastBatteryCheck > 30000)) { // Check every 30 seconds
        float voltage = getBatteryVoltage();
        int percentage = getBatteryPercentage();

        Serial.print(F("Battery: "));
        Serial.print(voltage);
        Serial.print(F("V ("));
        Serial.print(percentage);
        Serial.println(F("%)"));

        if (isCriticalBattery()) {
            Serial.println(F("CRITICAL: Battery level critical!"));
            enterPowerDownMode();
        } else if (isLowBattery()) {
            Serial.println(F("WARNING: Battery level low"));
        }

        _lastBatteryCheck = currentTime;
    }

    // Auto sleep based on interval
    if (_currentMode == POWER_MODE_NORMAL &&
        (currentTime - _lastWakeTime > _config.sleepInterval)) {
        enterSleepMode();
    }
}

void PowerManager::enterSleepMode() {
    Serial.println(F("Entering sleep mode..."));
    _currentMode = POWER_MODE_SLEEP;

    powerDownSensors();
    configureSleepMode();

    // Sleep for configured interval
#if !defined(ARDUINO_ARCH_ESP32)
    delay(_config.sleepInterval);
#endif

    wakeUp();
}

void PowerManager::enterDeepSleepMode() {
    Serial.println(F("Entering deep sleep mode..."));
    _currentMode = POWER_MODE_DEEP_SLEEP;

    powerDownSensors();
    configureDeepSleepMode();

    // Use watchdog timer for wake-up
    // This is a simplified version - actual implementation would use WDT
    delay(_config.sleepInterval);

    wakeUp();
}

void PowerManager::enterPowerDownMode() {
    Serial.println(F("Entering power down mode..."));
    _currentMode = POWER_MODE_POWER_DOWN;

    powerDownSensors();
    configurePowerDownMode();

    // Wait for external interrupt or manual reset
    // In real implementation, this would use external wake-up
    delay(_config.sleepInterval * 10); // Much longer sleep

    wakeUp();
}

void PowerManager::wakeUp() {
    Serial.println(F("Waking up..."));
    _currentMode = POWER_MODE_NORMAL;
    _lastWakeTime = millis();

    powerUpSensors();

    // Allow sensors to stabilize
    delay(1000);
}

float PowerManager::getBatteryVoltage() {
    int rawValue = analogRead(BATTERY_MONITOR_PIN);
    float voltage = (rawValue * VREF / 1023.0) / VOLTAGE_DIVIDER;
    return voltage;
}

int PowerManager::getBatteryPercentage() {
    float voltage = getBatteryVoltage();

    // Simple linear mapping (3.0V = 0%, 4.2V = 100%)
    float percentage = ((voltage - _config.criticalBatteryThreshold) /
                       (_config.lowBatteryThreshold - _config.criticalBatteryThreshold)) * 100.0;

    return constrain(percentage, 0, 100);
}

bool PowerManager::isLowBattery() {
    return getBatteryVoltage() < _config.lowBatteryThreshold;
}

bool PowerManager::isCriticalBattery() {
    return getBatteryVoltage() < _config.criticalBatteryThreshold;
}

void PowerManager::setSleepInterval(unsigned long interval) {
    _config.sleepInterval = interval;
}

void PowerManager::enableSensorPower(bool enable) {
    digitalWrite(SENSOR_POWER_PIN, enable ? HIGH : LOW);
}

void PowerManager::enableSolarCharging(bool enable) {
    digitalWrite(SOLAR_CHARGE_PIN, enable ? HIGH : LOW);
}

PowerMode PowerManager::getCurrentPowerMode() {
    return _currentMode;
}

void PowerManager::powerDownSensors() {
    enableSensorPower(false);

    // Disable ADC to save power
#if defined(ARDUINO_ARCH_AVR)
    ADCSRA = 0;
#endif

    Serial.println(F("Sensors powered down"));
}

void PowerManager::powerUpSensors() {
    enableSensorPower(true);

    // Re-enable ADC
#if defined(ARDUINO_ARCH_AVR)
    ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
#endif

    Serial.println(F("Sensors powered up"));
}

void PowerManager::configureSleepMode() {
#if defined(ARDUINO_ARCH_AVR)
    // Set sleep mode to IDLE
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    sleep_cpu();
    sleep_disable();
#elif defined(ARDUINO_ARCH_ESP32)
    esp_sleep_enable_timer_wakeup(_config.sleepInterval * 1000ULL);
    esp_light_sleep_start();
#else
    delay(_config.sleepInterval);
#endif
}

void PowerManager::configureDeepSleepMode() {
#if defined(ARDUINO_ARCH_AVR)
    // Set sleep mode to POWER_SAVE
    set_sleep_mode(SLEEP_MODE_PWR_SAVE);
    sleep_enable();
    sleep_cpu();
    sleep_disable();
#elif defined(ARDUINO_ARCH_ESP32)
    esp_sleep_enable_timer_wakeup(_config.sleepInterval * 1000ULL);
    esp_deep_sleep_start();
#else
    delay(_config.sleepInterval);
#endif
}

void PowerManager::configurePowerDownMode() {
#if defined(ARDUINO_ARCH_AVR)
    // Set sleep mode to POWER_DOWN (lowest power)
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_cpu();
    sleep_disable();
#elif defined(ARDUINO_ARCH_ESP32)
    esp_sleep_enable_timer_wakeup(_config.sleepInterval * 10ULL * 1000ULL);
    esp_deep_sleep_start();
#else
    delay(_config.sleepInterval * 10);
#endif
}
