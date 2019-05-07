#pragma once

#include "ISensor.h"
#include "Arduino.h"

class GravityDo: public ISensor
{
public:
	GravityDo();
	~GravityDo();

public:
	void setup();
	void update();
    void setPin(int pin);
	double getValue();
    float getTemperature() const;
    void setTemperature(float temperature);

private:
    int    _pin;
    int    _vref;
    float  _temperature;
	double _doValue;
    byte   _receivedBufferIndex;
    int    _analogBufferIndex;
    int    _copyIndex;
    float  _saturationDoVoltage;
    float  _saturationDoTemperature;
    float  _averageVoltage;
    static const int scount = 30;
    static const int receivedBufferLength = 20;
    char receivedBuffer[receivedBufferLength];    // store the serial command
    int analogBuffer[scount];    //store the analog value in the array, readed from ADC
    int analogBufferTemp[scount];

    void readDoCharacteristicValues();  
    bool serialDataAvailable();
    byte uartParse();
    void doCalibration(byte mode);
    int getMedianNum(int bArray[], int iFilterLen);
};  

