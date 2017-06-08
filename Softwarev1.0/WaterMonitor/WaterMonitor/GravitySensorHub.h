/*********************************************************************
* GravitySensorHub.h
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
* date    :  2017-04-07
**********************************************************************/

#pragma once
#include "ISensor.h"
/*
sensors :
0,ph
1,ec
2.orp
*/
class GravitySensorHub
{
private:
	static const int SensorCount = 10;

public:
	//********************************************************************************************
	// 函数名称: sensors[]
	// 函数说明：存放传感器的数组   
	// 参    数: 0  ph传感器  
	// 参    数: 1  温度值传感器   
	// 参    数: 2  溶解氧传感器 
	// 参    数: 3  电导率传感器 
	// 参    数: 4  氧化还原电位传感器 
	//********************************************************************************************
	ISensor *sensors[SensorCount] = {0};
public:
	GravitySensorHub();
	~GravitySensorHub();

	//初始化所有传感器
	void setup();

	//更新所有传感器数值
	void update();

	//获取传感器数据
	double getValueBySensorNumber(int num);
};
