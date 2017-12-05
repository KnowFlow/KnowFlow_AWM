/*********************************************************************
* GravityTemperature.cpp
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

#include "GravityTemperature.h"
#include <OneWire.h>
#include "Debug.h"

GravityTemperature::GravityTemperature(int pin)
{
	this->oneWire = new OneWire(pin);
}

GravityTemperature::~GravityTemperature()
{
}


//********************************************************************************************
// function name: setup ()
// Function Description: Initializes the sensor
//********************************************************************************************
void GravityTemperature::setup()
{
}


//********************************************************************************************
// function name: update ()
// Function Description: Update the sensor value
//********************************************************************************************
void GravityTemperature::update()
{
	if ( millis () - tempSampleTime >= tempSampleInterval)
	{
		tempSampleTime = millis ();
		temperature = TempProcess(ReadTemperature);  // read the current temperature from the  DS18B20
		TempProcess(StartConvert);                   //after the reading,start the convert for next reading
	}
}


//********************************************************************************************
// function name: getValue ()
// Function Description: Returns the sensor data
//********************************************************************************************
double GravityTemperature::getValue()
{
	return temperature;
}


//********************************************************************************************
// function name: TempProcess ()
// Function Description: Analyze the temperature data
//********************************************************************************************
double GravityTemperature::TempProcess(bool ch)
{
	static byte data[12];
	static byte addr[8];
	static float TemperatureSum;
	if (!ch) {
		if (!oneWire->search(addr)) {
			Debug::println("no temperature sensors on chain, reset search!");
			oneWire->reset_search();
			return 0;
		}
		if (OneWire::crc8(addr, 7) != addr[7]) {
			Debug::println("CRC is not valid!");
			return 0;
		}
		if (addr[0] != 0x10 && addr[0] != 0x28) {
			Debug::println("Device is not recognized!");
			return 0;
		}
		oneWire->reset();
		oneWire->select(addr);
		oneWire->write(0x44, 1); // start conversion, with parasite power on at the end
	}
	else {
		byte present = oneWire->reset();
		oneWire->select(addr);
		oneWire->write(0xBE); // Read Scratchpad
		for (int i = 0; i < 9; i++) { // we need 9 bytes
			data[i] = oneWire->read();
		}
		oneWire->reset_search();
		byte MSB = data[1];
		byte LSB = data[0];
		float tempRead = ((MSB << 8) | LSB); //using two's compliment
		TemperatureSum = tempRead / 16;
	}
	return TemperatureSum;
}
