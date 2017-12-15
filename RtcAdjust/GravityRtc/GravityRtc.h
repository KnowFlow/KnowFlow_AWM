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

#define RTC_Address   0x32  //RTC_Address 

class GravityRtc
{
public:
	GravityRtc();
	~GravityRtc();

public:
	//Year Month Day Weekday Minute Second
	unsigned int year;
	unsigned char month;
	unsigned char day;
	unsigned char week;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
	
	//Initialize RTC time to set the corresponding year, month, day, Weekday Minute Second
	void initRtc(unsigned int year,	unsigned char month,unsigned char day,unsigned char week,
            	unsigned char hour,unsigned char minute,unsigned char second);

	//initialization
	void setup();

	//Update sensor data
	void update();
	

private:
	unsigned char date[7];

	//Read RTC Time
	void readRtc();

	//Analysis RTC Time
	void processRtc();

	//Decimal turn to BCD
	char decTobcd(char num);
	void WriteTimeOn(void);
	void WriteTimeOff(void);
	unsigned long timeUpdate;


};

