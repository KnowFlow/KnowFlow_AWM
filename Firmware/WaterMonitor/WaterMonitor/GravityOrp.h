/*********************************************************************************
* GravityOrp.h
*
* Copyright (C)    2017   [DFRobot](http://www.dfrobot.com),
* GitHub Link :https://github.com/DFRobot/watermonitor
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Description:Monitoring water quality parameters Oxidation-Reduction Potential
*
* Product Links：http://www.dfrobot.com.cn/goods-840.html
*
* Sensor driver pin：A3 
*
* author  :  Jason(jason.ling@dfrobot.com)
* version :  V1.0
* date    :  2017-04-14
**********************************************************************************/

#pragma once
#include <Arduino.h>
#include "ISensor.h"
class GravityOrp:public ISensor
{
public:
	// orp sensor pin
	int orpSensorPin;

	// voltage value
	double voltage;

	// Calibrate the offset
	float offset;
private:
	// orp value
	double orpValue;


	static const int arrayLength = 5;
	int orpArray[arrayLength];
	double sum;

	double previousOrp;
	double currentOrp;
	double averageOrp;

public:
	GravityOrp();
	~GravityOrp();

	// initialize the sensor
	void  setup ();

	// update the sensor data
	void  update ();

	// Get the sensor data
	double getValue();
};

