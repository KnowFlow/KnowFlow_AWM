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
#include "string.h"
#include <SPI.h>
#include "Debug.h"
#include "GravityRtc.h"

extern GravityRtc rtc;
String dataString = "";

SdService :: SdService (ISensor * gravitySensor []): chipSelect (CsPin), sdDataUpdateTime ( 0 )
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

	pinMode(SS, OUTPUT);

	if (!SD.begin(chipSelect))
	{
		Debug::println("Card failed, or not present");
		// don't do anything more:
		return;
	}

	Debug::println("card initialized.");

	// write the file header
	dataFile = SD.open("sensor.csv", FILE_WRITE);
	if (dataFile && dataFile.position() == 0) {
		dataFile.println("Year,Month,Day,Hour,Minues,Second,pH,temp(C),DO(mg/l0,ec(s/m),orp(mv)");
		dataFile.close();
	}

}


//********************************************************************************************
// function name: update ()
// Function Description: Update the data in the SD card
//********************************************************************************************
void SdService::update()
{
	if (millis() - sdDataUpdateTime > 2000) //2000ms
	{

		dataString = "";
		// Year Month Day Hours Minute Seconds
		dataString += String(rtc.year,10);
		dataString += ",";
		dataString += String(rtc.month, 10);
		dataString += ",";
		dataString += String(rtc.day, 10);
		dataString += ",";
		dataString += String(rtc.hour, 10);
		dataString += ",";
		dataString += String(rtc.minute, 10);
		dataString += ",";
		dataString += String(rtc.second, 10);
		dataString += ",";

		// write SD card, write data twice, to prevent a single write data caused by the loss of too large
		dataFile = SD.open("sensor.csv", FILE_WRITE);
		if (dataFile)
		{
			dataFile.print(dataString);
			dataFile.close();
			Debug::print(dataString);

		}

		dataString = "";
		//ph
		if (this->gravitySensor[0] != NULL) {
			connectString(this->gravitySensor[0]->getValue());
		}
		else
			connectString(0);

		// temperature
		if (this->gravitySensor[1] != NULL) {
			connectString(this->gravitySensor[1]->getValue());
		}
		else
			connectString(0);

		//DO
		if (this->gravitySensor[2] != NULL) {
			connectString(this->gravitySensor[2]->getValue());
		}
		else
			connectString(0);

		//EC
		if (this->gravitySensor[3] != NULL) {
			connectString(this->gravitySensor[3]->getValue());
		}
		else
			connectString(0);

		//Orp
		if (this->gravitySensor[4] != NULL) {
			connectString(this->gravitySensor[4]->getValue());
		}
		else
			connectString(0);

		// write SD card
		dataFile = SD.open("sensor.csv", FILE_WRITE);
		if (dataFile)
		{
			dataFile.println(dataString);
			dataFile.close();
			Debug::println(dataString);

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
