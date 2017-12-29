#pragma once
#include "ISensor.h"
#include "Arduino.h"
class GravityEc : public ISensor
{
public:
	GravityEc();
	~GravityEc();

public:
	void setup();
	void update();
	double getValue();
	void setKValue(float value);

	int pin;
	double ecValue;
	float kValue;

};

