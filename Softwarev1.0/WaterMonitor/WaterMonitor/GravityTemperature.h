/*********************************************************************
* GravityTemperature.h
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

#pragma once
#include "ISensor.h"
#include "OneWire.h"
#define StartConvert 0
#define ReadTemperature 1

class GravityTemperature : public ISensor 
{
public:
	//温度传感器引脚
	int temperaturePin;
	double temperature;

public:
	GravityTemperature(int pin);
	~GravityTemperature();

	//初始化
	void setup();

	//更新传感器数据
	void update();

	//获取传感器数据
	double getValue();

private:

	OneWire *oneWire;
	unsigned long tempSampleInterval = 850;
	unsigned long tempSampleTime;

	//解析温度数据
	double TempProcess(bool ch);
};

