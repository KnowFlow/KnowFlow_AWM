#pragma once

#include "GravitySensorHub.h"
#include "SdService.h"

enum CalibrationType {
    CALIBRATION_PH_3POINT,
    CALIBRATION_PH_2POINT,
    CALIBRATION_EC_1POINT,
    CALIBRATION_DO_2POINT,
    CALIBRATION_ORP_1POINT
};

struct CalibrationData {
    float ph7Calibration = 0.0;
    float ph4Calibration = 0.0;
    float ph10Calibration = 0.0;
    float ecCalibration = 0.0;
    float doZeroCalibration = 0.0;
    float doSpanCalibration = 0.0;
    float orpCalibration = 0.0;
    bool isCalibrated[5] = {false, false, false, false, false};
};

class CalibrationService {
public:
    CalibrationService(GravitySensorHub* sensorHub, SdService* sdService);

    void setup();
    void loop();

    void startCalibration(CalibrationType type);
    void stopCalibration();
    bool isCalibrating();

    void setPhCalibration(float ph7, float ph4, float ph10);
    void setEcCalibration(float ecValue);
    void setDoCalibration(float zeroValue, float spanValue);
    void setOrpCalibration(float orpValue);

    CalibrationData getCalibrationData();
    void saveCalibrationData();
    void loadCalibrationData();

    void printCalibrationInstructions();

private:
    GravitySensorHub* _sensorHub;
    SdService* _sdService;
    CalibrationData _calibrationData;
    bool _isCalibrating;
    CalibrationType _currentCalibrationType;
    unsigned long _calibrationStartTime;

    void calibratePh3Point();
    void calibratePh2Point();
    void calibrateEc1Point();
    void calibrateDo2Point();
    void calibrateOrp1Point();

    void applyCalibration();
    void resetCalibration();
};