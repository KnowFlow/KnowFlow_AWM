/*********************************************************************************************
* SensorDo.cpp
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

#include "SensorDo.h"

SensorDo::SensorDo()
{

}


SensorDo::~SensorDo()
{
}


//********************************************************************************************
// function name: setup ()
// Function Description: Initializes the sensor
//********************************************************************************************
void SensorDo::setup()
{
	sensorstring.reserve(30);
}


//********************************************************************************************
// function name: update ()
// Function Description: Update the sensor value
//********************************************************************************************
void SensorDo::update()
{
	static boolean sensorStringComplete = false;
	if (Serial.available() > 0)
	{
		char inchar = (char)Serial.read();
		this->sensorstring += inchar;
		if (inchar == '\r')
			sensorStringComplete = true;
	}
	if (sensorStringComplete == true)
	{
		if (isdigit(this->sensorstring[0]))
			doValue = this->sensorstring.toFloat();
		this->sensorstring = "";
		sensorStringComplete = false;
	}
}

//********************************************************************************************
// function name: getValue ()
// Function Description: Returns the sensor data
//********************************************************************************************
double SensorDo::getValue()
{
	return doValue;
}

//
//void serialEvent() {                                  //if the hardware serial port_0 receives a char
//	inputstring = Serial.readStringUntil(13);           //read the string until we see a <CR>
//	input_string_complete = true;                       //set the flag used to tell if we have received a completed string from the PC 
//}
