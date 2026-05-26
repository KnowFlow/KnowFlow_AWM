/*********************************************************************
* GravityPh.h
*
* Copyright (C)    2017   [DFRobot](http://www.dfrobot.com),
* GitHub Link :https://github.com/DFRobot/watermonitor
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Description:Monitoring water quality parameters ph
*
* Product Links：http://www.dfrobot.com.cn/goods-812.html
*
* Sensor driver pin：A2 
*
* author  :  Jason(jason.ling@dfrobot.com)
* version :  V1.0
* date    :  2017-04-07
**********************************************************************/

#pragma once
#include <Arduino.h>
#include "ISensor.h"
#include "Config.h"

class GravityPh:public ISensor
{
public:
	// ph sensor pin
	int pin;

	// offset compensation
	float offset;

private:
	int pHArray[ARRAYLENGTH];    // stores the average value of the sensor return data
	double pHValue;

public:
	GravityPh();
	~GravityPh() {};
	// initialization
	void  setup ();

	// update the sensor data
	void  update ();

	// Get the sensor data
	double getValue();

	//set offset
	void setOffset(float offset);
};

