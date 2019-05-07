/*********************************************************************
* GravityRtc.h
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

#pragma once
#include <Arduino.h>
#include "Debug.h"

#define RTC_Address   0x32  //RTC_Address 


class GravityRtc
{
public:
	GravityRtc() {};
	~GravityRtc() {};

public:
	//Year Month Day Weekday Minute Second
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t week;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	
	//Initialize RTC time to set the corresponding year, month, day, Weekday Minute Second
	void init(const __FlashStringHelper* date, const __FlashStringHelper* time);
	
	void adjustRtc(uint16_t year,uint8_t month,uint8_t day,uint8_t week,
            	uint8_t hour,uint8_t minute,uint8_t second);

	//initialization
	void setup();

	//Update sensor data
	void update();

private:
	uint8_t date[7];

	//Read RTC Time
	void readRtc();

	//Analyze RTC Time
	void processRtc();

	//Decimal turn to BCD
	uint8_t decTobcd(uint8_t num);
	void WriteTimeOn(void);
	void WriteTimeOff(void);
	unsigned long timeUpdate;

	//adjust RTC
	uint8_t dayOfTheWeek();

	// number of days since 2000/01/01, valid for 2001..2099
 	uint16_t date2days(uint16_t y, uint8_t m, uint8_t d);
	
	uint8_t conv2d(const char* p);

};

