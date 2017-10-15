/*********************************************************************************************
* SensorDo.h
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
* Sensor driver pin：Serial,Rx(0),Tx(1)
*
* author  :  Jason(jason.ling@dfrobot.com)
* version :  V1.0
* date    :  2017-04-19
*********************************************************************************************/
#pragma once
#include "ISensor.h"
#include "Arduino.h"

class SensorDo: public ISensor
{
public:
	SensorDo();
	~SensorDo();

public:
	// initialization
	void  setup ();

	// update the sensor data
	void  update ();

	// Get the sensor data
	double getValue();

private:

	String sensorstring = "";

	// do the data
	double doValue;

};

