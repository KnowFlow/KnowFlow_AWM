/*********************************************************************
* GravityTemperature.h
*
* Copyright (C)    2017   [DFRobot](http://www.dfrobot.com),
* GitHub Link :https://github.com/DFRobot/watermonitor
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Description:
*
* author  :  Jason(jason.ling@dfrobot.com)
* version :  V1.0
* date    :  2017-04-12
**********************************************************************/

#pragma once
#include "ISensor.h"
#include "OneWire.h"
#define StartConvert 0
#define ReadTemperature 1

class GravityTemperature : public ISensor
{
public:
	// temperature sensor pin
	int temperaturePin;
	double temperature;

public:
	GravityTemperature(int pin);
	~GravityTemperature();

	// initialization
	void  setup ();

	// update the sensor data
	void  update ();

	// Get the sensor data
	double getValue();

private:

	OneWire * oneWire;
	unsigned  long tempSampleInterval = 850 ;
	unsigned  long tempSampleTime;

	// Analyze temperature data
	double TempProcess(bool ch);
};

