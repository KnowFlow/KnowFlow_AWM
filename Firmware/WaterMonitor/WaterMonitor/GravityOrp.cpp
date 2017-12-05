/*********************************************************************
* GravityOrp.cpp
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
* Sensor driver pin：A3 (orpSensorPin(A3))
*
* author  :  Jason(jason.ling@dfrobot.com)
* version :  V1.0
* date    :  2017-04-14
**********************************************************************/

#include "GravityOrp.h"


GravityOrp::GravityOrp():orpSensorPin(A3), voltage(5.0), offset(0), orpValue(0.0), sum(0)
{
}


GravityOrp::~GravityOrp()
{
}

//********************************************************************************************
// function name: setup ()
// Function Description: Initializes the sensor
//********************************************************************************************
void GravityOrp::setup()
{
}



//********************************************************************************************
// function name: update ()
// Function Description: Update the sensor value
//********************************************************************************************
void GravityOrp::update()
{
	static unsigned long orpTimer = millis();   //analog sampling interval
	static unsigned long printTime = millis();
	static int orpArrayIndex = 0;
	if (millis() >= orpTimer)
	{
		orpTimer = millis() + 20;
		orpArray[orpArrayIndex++] = analogRead(orpSensorPin);    //read an analog value every 20ms

		if (orpArrayIndex == arrayLength)    // 5 * 20 = 100ms calculated once
		{
			orpArrayIndex = 0;
			for(int i = 0; i < arrayLength; i++)
				this->sum += orpArray[i];
			averageOrp = this->sum / arrayLength;
			this->sum = 0;
			//convert the analog value to orp according the circuit
			this->orpValue = ((30 * this->voltage * 1000) - (75 * averageOrp*this->voltage * 1000 / 1024)) / 75 - this->offset;
		}
	}
}


//********************************************************************************************
// function name: getValue ()
// Function Description: Returns the sensor data
//********************************************************************************************
double GravityOrp::getValue()
{
	return this->orpValue;
}
