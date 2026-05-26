#include "CalibrationService.h"
#include <EEPROM.h>

CalibrationService::CalibrationService(GravitySensorHub* sensorHub, SdService* sdService) :
    _sensorHub(sensorHub),
    _sdService(sdService),
    _isCalibrating(false),
    _currentCalibrationType(CALIBRATION_PH_3POINT),
    _calibrationStartTime(0) {
}

void CalibrationService::setup() {
    loadCalibrationData();
    applyCalibration();
}

void CalibrationService::loop() {
    if (!_isCalibrating) return;

    unsigned long currentTime = millis();
    if (currentTime - _calibrationStartTime < 10000) return; // Wait 10 seconds for stability

    switch (_currentCalibrationType) {
        case CALIBRATION_PH_3POINT:
            calibratePh3Point();
            break;
        case CALIBRATION_PH_2POINT:
            calibratePh2Point();
            break;
        case CALIBRATION_EC_1POINT:
            calibrateEc1Point();
            break;
        case CALIBRATION_DO_2POINT:
            calibrateDo2Point();
            break;
        case CALIBRATION_ORP_1POINT:
            calibrateOrp1Point();
            break;
    }

    _isCalibrating = false;
    saveCalibrationData();
    Serial.println(F("Calibration completed!"));
}

void CalibrationService::startCalibration(CalibrationType type) {
    _currentCalibrationType = type;
    _isCalibrating = true;
    _calibrationStartTime = millis();
    printCalibrationInstructions();
}

void CalibrationService::stopCalibration() {
    _isCalibrating = false;
}

bool CalibrationService::isCalibrating() {
    return _isCalibrating;
}

void CalibrationService::setPhCalibration(float ph7, float ph4, float ph10) {
    _calibrationData.ph7Calibration = ph7;
    _calibrationData.ph4Calibration = ph4;
    _calibrationData.ph10Calibration = ph10;
    _calibrationData.isCalibrated[0] = true;
    applyCalibration();
}

void CalibrationService::setEcCalibration(float ecValue) {
    _calibrationData.ecCalibration = ecValue;
    _calibrationData.isCalibrated[3] = true;
    applyCalibration();
}

void CalibrationService::setDoCalibration(float zeroValue, float spanValue) {
    _calibrationData.doZeroCalibration = zeroValue;
    _calibrationData.doSpanCalibration = spanValue;
    _calibrationData.isCalibrated[2] = true;
    applyCalibration();
}

void CalibrationService::setOrpCalibration(float orpValue) {
    _calibrationData.orpCalibration = orpValue;
    _calibrationData.isCalibrated[4] = true;
    applyCalibration();
}

CalibrationData CalibrationService::getCalibrationData() {
    return _calibrationData;
}

void CalibrationService::saveCalibrationData() {
    EEPROM.put(0, _calibrationData);
    Serial.println(F("Calibration data saved to EEPROM"));
}

void CalibrationService::loadCalibrationData() {
    EEPROM.get(0, _calibrationData);
    Serial.println(F("Calibration data loaded from EEPROM"));
}

void CalibrationService::printCalibrationInstructions() {
    switch (_currentCalibrationType) {
        case CALIBRATION_PH_3POINT:
            Serial.println(F("PH 3-Point Calibration:"));
            Serial.println(F("1. Place probe in pH 7 buffer"));
            Serial.println(F("2. Wait for stable reading (10s)"));
            Serial.println(F("3. Repeat for pH 4 and pH 10 buffers"));
            break;
        case CALIBRATION_EC_1POINT:
            Serial.println(F("EC 1-Point Calibration:"));
            Serial.println(F("1. Place probe in 1413 uS/cm solution"));
            Serial.println(F("2. Wait for stable reading (10s)"));
            break;
        case CALIBRATION_DO_2POINT:
            Serial.println(F("DO 2-Point Calibration:"));
            Serial.println(F("1. Place probe in zero oxygen solution"));
            Serial.println(F("2. Wait for stable reading (10s)"));
            Serial.println(F("3. Place probe in air-saturated water"));
            Serial.println(F("4. Wait for stable reading (10s)"));
            break;
        case CALIBRATION_ORP_1POINT:
            Serial.println(F("ORP 1-Point Calibration:"));
            Serial.println(F("1. Place probe in 225 mV solution"));
            Serial.println(F("2. Wait for stable reading (10s)"));
            break;
    }
}

void CalibrationService::calibratePh3Point() {
    Serial.println(F("Performing pH 3-point calibration..."));
    // Implementation depends on sensor library integration
    float ph7Reading = _sensorHub->getValueBySensorNumber(0);
    float offset = 7.0 - ph7Reading;
    setPhCalibration(offset, offset, offset);
}

void CalibrationService::calibratePh2Point() {
    Serial.println(F("Performing pH 2-point calibration..."));
    // Similar to 3-point but with 2 buffers
}

void CalibrationService::calibrateEc1Point() {
    Serial.println(F("Performing EC 1-point calibration..."));
    float ecReading = _sensorHub->getValueBySensorNumber(3);
    float factor = 1413.0 / ecReading;
    setEcCalibration(factor);
}

void CalibrationService::calibrateDo2Point() {
    Serial.println(F("Performing DO 2-point calibration..."));
    float zeroReading = _sensorHub->getValueBySensorNumber(2);
    float spanReading = _sensorHub->getValueBySensorNumber(2);
    setDoCalibration(zeroReading, spanReading);
}

void CalibrationService::calibrateOrp1Point() {
    Serial.println(F("Performing ORP 1-point calibration..."));
    float orpReading = _sensorHub->getValueBySensorNumber(4);
    float offset = 225.0 - orpReading;
    setOrpCalibration(offset);
}

void CalibrationService::applyCalibration() {
    Serial.println(F("Applying calibration data..."));
    // Apply calibration factors to sensors
}

void CalibrationService::resetCalibration() {
    for (int i = 0; i < 5; i++) {
        _calibrationData.isCalibrated[i] = false;
    }
    saveCalibrationData();
    Serial.println(F("Calibration data reset"));
}