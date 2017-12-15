/*********************************************************************
* GravityRtc.cpp
*
* Copyright (C)    2017   [DFRobot](http://www.dfrobot.com),
* GitHub Link :https://github.com/DFRobot/Gravity-I2C-SD2405-RTC-Module/
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Description:Get real-time clock data
*
* Product Links：https://www.dfrobot.com/wiki/index.php/Gravity:_I2C_SD2405_RTC_Module_SKU:_DFR0469
*
* Sensor driver pin：I2C
*
* author  :  Jason(jason.ling@dfrobot.com)
* version :  V1.0
* date    :  2017-04-18
**********************************************************************/

#include "GravityRtc.h"
#include "Arduino.h"
#include "Wire.h"


GravityRtc::GravityRtc() :year(2017), month(4), day(17), week(4), hour(14), minute(5),second(0)
{
}


GravityRtc::~GravityRtc()
{
}

//********************************************************************************************
// Function Name: setup()
// Function Declaration: Initializing sensor
//********************************************************************************************
void GravityRtc::setup()
{
	Wire.begin();
	//initRtc();
}


//********************************************************************************************
// Function Name: update()
// Function Declaration: Update the sensor value
//********************************************************************************************
void GravityRtc::update()
{
	if (millis() - timeUpdate > 1000)
	{
		timeUpdate = millis();
		readRtc();
		processRtc();
	}	
}

//********************************************************************************************
// Function Name: initRtc()
// Function Declaration: Initializing RTC Clock
//********************************************************************************************
void GravityRtc::initRtc(unsigned int year,	unsigned char month,unsigned char day,unsigned char week,
            	unsigned char hour,unsigned char minute,unsigned char second)
{
	WriteTimeOn();

	Wire.beginTransmission(RTC_Address);
	Wire.write(char(0));//Set the address for writing       
	Wire.write(this->decTobcd(second));
	Wire.write(this->decTobcd(minute));
	Wire.write(this->decTobcd(hour + 80));      // +80: sets 24 hours format
	Wire.write(this->decTobcd(week));       // days values come from 0 to 6: Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday
	Wire.write(this->decTobcd(day));
	Wire.write(this->decTobcd(month));
	Wire.write(this->decTobcd(year-2000));
	Wire.endTransmission();

	Wire.beginTransmission(RTC_Address);
	Wire.write(0x12);   //Set the address for writing       
	Wire.write(char(0));
	Wire.endTransmission();

	WriteTimeOff();
}


//********************************************************************************************
// Function Name: readRtc()
// Function Declaration: Read RTC Time
//********************************************************************************************
void GravityRtc::readRtc()
{
	unsigned char n = 0;

	Wire.requestFrom(RTC_Address, 7);
	while (Wire.available())
	{
		date[n++] = Wire.read();
	}
	delayMicroseconds(1);
	Wire.endTransmission();
}


//********************************************************************************************
// Function Name: processRtc()
// Function Declaration: Analysis RTC Data from readRtc
//********************************************************************************************
void GravityRtc::processRtc()
{
	unsigned char i;

	for (i = 0; i<7; i++)
	{
		if (i != 2)
			date[i] = (((date[i] & 0xf0) >> 4) * 10) + (date[i] & 0x0f);
		else
		{
			date[2] = (date[2] & 0x7f);
			date[2] = (((date[2] & 0xf0) >> 4) * 10) + (date[2] & 0x0f);
		}
	}
	year   = date[6] + 2000;
	month  = date[5];
	day    = date[4];
	week   = date[3];
	hour   = date[2];
	minute = date[1];
	second = date[0];

}


//********************************************************************************************
// Function Name: decTobcd()
// Function Declaration: Decimal turn to BCD
//********************************************************************************************
char GravityRtc::decTobcd(char num)
{
	return ((num / 10 * 16) + (num % 10));
}




void GravityRtc::WriteTimeOn(void)
{
	Wire.beginTransmission(RTC_Address);
	Wire.write(0x10);//Set the address for writing as 10H       
	Wire.write(0x80);//Set WRTC1=1      
	Wire.endTransmission();

	Wire.beginTransmission(RTC_Address);
	Wire.write(0x0F);//Set the address for writing as OFH       
	Wire.write(0x84);//Set WRTC2=1,WRTC3=1      
	Wire.endTransmission();
}

void GravityRtc::WriteTimeOff(void)
{
	Wire.beginTransmission(RTC_Address);
	Wire.write(0x0F);   //Set the address for writing as OFH        
	Wire.write(0);//Set WRTC2=0,WRTC3=0      
	Wire.write(0);//Set WRTC1=0  
	Wire.endTransmission();
}


/*************************************Test & Print Value***********************************/
//Serial.print("Year = ");//year
//Serial.print(rtc.year);
//Serial.print("   Month = ");//month
//Serial.print(rtc.month);
//Serial.print("   Day = ");//day
//Serial.print(rtc.day);
//Serial.print("   Week = ");//week
//Serial.print(rtc.week);
//Serial.print("   Hour = ");//hour
//Serial.print(rtc.hour);
//Serial.print("   Minute = ");//minute
//Serial.print(rtc.minute);
//Serial.print("   Second = ");//second
//Serial.print(rtc.second);
//	
//Serial.println();
