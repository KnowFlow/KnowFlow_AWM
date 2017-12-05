/*********************************************************************
* GravityEc.h
*
* Copyright (C)    2017   [DFRobot](http://www.dfrobot.com),
* GitHub Link :https://github.com/DFRobot/watermonitor
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Description:Monitoring water quality parameters Conductivity
*
* Product Links：http://www.dfrobot.com.cn/goods-882.html
* 
* Sensor driver pin：A1 (Can be modified in the .cpp file:ECsensorPin(A1);)
*
* author  :  Jason(jason.ling@dfrobot.com)
* version :  V1.0
* date    :  2017-04-17
**********************************************************************/

#pragma once
#include "GravityTemperature.h"
#include "ISensor.h"

// external GravityTemperature ecTemperature;

class GravityEc:public ISensor
{
public:
	// Conductivity sensor pin
	int ecSensorPin;

	// Conductivity values
	double ECcurrent;


public:
	GravityEc(ISensor*);
	~GravityEc();

	// initialization
	void  setup ();

	// update the sensor data
	void  update ();

	// Get the sensor data
	double getValue();

private:
	// point to the temperature sensor pointer
	ISensor* ecTemperature = NULL;


	static const int numReadings = 5;
	unsigned int readings[numReadings] = { 0 };      // the readings from the analog input
	int index;
	double sum;
	unsigned long AnalogValueTotal;      // the running total
	unsigned int AnalogAverage;
	unsigned int averageVoltage;
	unsigned long AnalogSampleTime;
	unsigned long printTime;
	unsigned  long tempSampleTime;
	unsigned long AnalogSampleInterval;
	unsigned long printInterval ;

	// Calculate the average
  void calculateAnalogAverage();

	// Calculate the conductivity
	void calculateEc();
};

