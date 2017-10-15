/*********************************************************************************************
* GravitySensorHub.cpp
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
*********************************************************************************************/


#include "GravitySensorHub.h"
#include "GravityPh.h"
#include "GravityOrp.h"
#include "GravityEc.h"
#include "GravityTemperature.h"
#include "SensorDo.h"
#include "SdService.h"

//********************************************************************************************
// function name: sensors []
// Function Description: Store the array of sensors
// Parameters: 0 ph sensor
// Parameters: 1 temperature sensor
// Parameters: 2 Dissolved oxygen sensor
// Parameters: 3 Conductivity sensor
// Parameters: 4 Redox potential sensor
//********************************************************************************************

GravitySensorHub::GravitySensorHub()
{
	for (size_t i = 0; i < this->SensorCount; i++)
	{
		this->sensors[i] = NULL;
	}

	this->sensors[0] = new GravityPh();
	this->sensors[1] = new GravityTemperature(5);
	this->sensors[2] = new SensorDo();
	this->sensors[3] = new GravityEc(this->sensors[1]);
	this->sensors[4] = new GravityOrp();

}

//********************************************************************************************
// function name: ~ GravitySensorHub ()
// Function Description: Destructor, frees all sensors
//********************************************************************************************
GravitySensorHub::~GravitySensorHub()
{
	for (size_t i = 0; i < SensorCount; i++)
	{
		if (this->sensors[i])
		{
			delete this->sensors[i];
		}
	}
}


//********************************************************************************************
// function name: setup ()
// Function Description: Initializes all sensors
//********************************************************************************************
void GravitySensorHub::setup()
{
	for (size_t i = 0; i < SensorCount; i++)
	{
		if (this->sensors[i])
		{
			this->sensors[i]->setup();
		}
	}
}


//********************************************************************************************
// function name: update ()
// Function Description: Updates all sensor values
//********************************************************************************************
void GravitySensorHub::update()
{
	for (size_t i = 0; i < SensorCount; i++)
	{
		if (this->sensors[i])
		{
			this->sensors[i]->update();
		}
	}
}

//********************************************************************************************
// function name: getValueBySensorNumber ()
// Function Description: Get the sensor data
// Parameters: 0 ph sensor
// Parameters: 1 temperature sensor
// Parameters: 2 Dissolved oxygen sensor
// Parameters: 3 Conductivity sensor
// Parameters: 4 Redox potential sensor
// Return Value: Returns the acquired sensor data
//********************************************************************************************
double GravitySensorHub::getValueBySensorNumber(int num)
{
	if (num >= SensorCount)
	{
		return 0;
	}
	return this->sensors[num]->getValue();
}
