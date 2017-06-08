/*********************************************************************
* GravityRtc.h
*
* Copyright (C)    2017   [DFRobot](http://www.dfrobot.com),
* GitHub Link :https://github.com/DFRobot/watermonitor
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Description:Get real-time clock data
*
* Product Links：
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
	//年月日周时分秒
	unsigned int year;
	unsigned char month;
	unsigned char day;
	unsigned char week;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
	
	//初始化RTC时间设置相应的年月日周时分秒
	void initRtc();

	//初始化
	void setup();

	//更新传感器数据
	void update();
	

private:
	unsigned char date[7];

	//读取时钟数据
	void readRtc();

	//解析RTC数据
	void processRtc();

	//十进制转BCD
	char decTobcd(char num);
	void WriteTimeOn(void);
	void WriteTimeOff(void);
	unsigned long timeUpdate;


};

