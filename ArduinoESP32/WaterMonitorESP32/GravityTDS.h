#pragma once

#include "ISensor.h"
#include "Arduino.h"

#define COUNT  10

class GravityTDS: public ISensor
{
public:
	GravityTDS();
	~GravityTDS();

public:
	void setup();
	void update();
	double getValue();
    void setPin(int pin);
    float setTemperature(float temp);
    float setVref(float value);


private:
    int pin;
    float vref;
    float temperature;
    int analogBuffer[COUNT];    // store the analog value in the array, read from ADC
    float averageVoltage = 0;
    double tdsValue = 0;

    uint16_t readMedianValue(int* dataArray, uint16_t arrayLength);
    
    
};  


