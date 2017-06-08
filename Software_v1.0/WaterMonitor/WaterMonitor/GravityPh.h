/*********************************************************************
* GravityPh.h
*
* Copyright (C)    2017   [DFRobot](http://www.dfrobot.com),
* GitHub Link :https://github.com/DFRobot/watermonitor
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Description:Monitoring water quality parameters ph
*
* Product Links：http://www.dfrobot.com.cn/goods-812.html
*
* Sensor driver pin：A2 
*
* author  :  Jason(jason.ling@dfrobot.com)
* version :  V1.0
* date    :  2017-04-07
**********************************************************************/

#pragma once
#include <Arduino.h>
#include "ISensor.h"
class GravityPh:public ISensor
{
public:
	//ph传感器引脚
	int phSensorPin;          

	//偏移补偿
	float offset;   

	//抽取样本间隔
	int samplingInterval;   
private:
	static const int arrayLength = 5;
	int pHArray[arrayLength];   //储存传感器返回数据的平均值 
	double pHValue, voltage;
	double averageVoltage;
	double sum;

public:
	GravityPh();
	~GravityPh() {};
	//初始化
	void setup();

	//更新传感器数据
	void update();

	//获取传感器数据
	double getValue();
};

