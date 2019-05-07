/*********************************************************************
* SdService.cpp
*
* Copyright (C)    2017   [DFRobot](http://www.dfrobot.com),
* GitHub Link :https://github.com/DFRobot/watermonitor
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Description:SD card datalogger,Data write format:
* "Year,Month,Day,Hour,Minues,Second,pH,temp(C),DO(mg/l0,ec(s/m),orp(mv)"
*
* Product Links:http://www.dfrobot.com.cn/goods-1142.html
*
* SD card attached to SPI bus as follows:
* UNO:  MOSI - pin 11, MISO - pin 12, CLK - pin 13, CS - pin 4 (CS pin can be changed)
* and pin #10 (SS) must be an output
* Mega:  MOSI - pin 51, MISO - pin 50, CLK - pin 52, CS - pin 53
* and pin #53 (SS) must be an output
* M0:   Onboard SPI pin,CS - pin 4 (CS pin can be changed)
*
* author  :  Jason(jason.ling@dfrobot.com)
* version :  V1.0
* date    :  2017-04-19
**********************************************************************/



// SD card select pin
//#if defined(__SAMD21G18A__)
#if  defined(__AVR_ATmega2560__)
const int CsPin = 53;
#else
const int CsPin = 4;
#endif

#include "SdService.h"
#include <SPI.h>
#include "Debug.h"
#include "GravityRtc.h"
#include "config.h"
#include "Debug.h"

extern GravityRtc rtc;

//Initialize variable to hold data
String dataString = "";


SdService::SdService(ISensor * gravitySensor []): chipSelect(CsPin), sdDataUpdateTime( 0 )
{
	this->gravitySensor = gravitySensor;
}


SdService :: ~ SdService ()
{
}

//********************************************************************************************
// function name: setup ()
// Function Description: Initialize the SD card
//********************************************************************************************
void SdService::setup()
{
	Debug::println("Initializing SD card...");

	//Make sure SS pin is set to output
	pinMode(SS, OUTPUT);

	//Open communication with SD card
	if (!SD.begin(chipSelect))
	{
		Debug::println("Card failed, or not present");
		// don't do anything more:
		return;
	}
	sdReady = true;
	Debug::println("card initialized.");

	// write the file header
	dataFile = SD.open("sensor.csv", FILE_WRITE);
	if (dataFile && dataFile.position() == 0) {
		Debug::println(F("Writing file header to SD"));
		// dataFile.println(F("Year,Month,Day,Hour,Minues,Second,pH,temp(C),DO(mg/l),ec(s/m),orp(mv)"));
		dataFile.println(F("date,pH,temp(C),DO(mg/l),ec(ms/cm),orp(mv)"));
		dataFile.close();
	}
}

//********************************************************************************************
// function name: update ()
// Function Description: Update data and write to SD card
//********************************************************************************************
void SdService::update()
{
	//sdReady 
	if (sdReady && millis() - sdDataUpdateTime > SDUPDATEDATATIME)
	{
		Debug::println("Writing time to Sd card");

		//Update time from clock module
		rtc.update();

		//add time to dataString
		// Year Month Day Hours Minute Seconds
		dataString = "";
		dataString += String(rtc.year,10);
		dataString += "/";
		dataString += String(rtc.month, 10);
		dataString += "/";
		dataString += String(rtc.day, 10);
		dataString += "/";
		dataString += String(rtc.hour, 10);
		dataString += "/";
		dataString += String(rtc.minute, 10);
		dataString += "/";
		dataString += String(rtc.second, 10);
		dataString += ",";

		// write time to SD card, write in two operations to keep write size small
		dataFile = SD.open("sensor.csv", FILE_WRITE);
		if (dataFile)
		{
			Debug::println(F("Writing Time to card"));
			Debug::print(dataString);
			dataFile.print(dataString);
			dataFile.close();
		}

		//Empty dataString and add sensor readings
		dataString = "";
		for (int i = 0; i < SENSORCOUNT; i++)
		{
			if (this->gravitySensor[i] != NULL)
				connectString(this->gravitySensor[i]->getValue());			
			else
				connectString(0);
		}

		//Write sensor readings to SD card
		dataFile = SD.open("sensor.csv", FILE_WRITE);
		if (dataFile)
		{
			Debug::println(dataString);
			dataFile.println(dataString);
			dataFile.close();
		}
		sdDataUpdateTime = millis();
	}
}

//********************************************************************************************
// function name: connectString ()
// Function Description: Connects the string data
//********************************************************************************************
void SdService::connectString(double value)
{
	dataString += String(value, 10);
	dataString += ",";
}
