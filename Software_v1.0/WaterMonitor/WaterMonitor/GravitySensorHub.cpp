/*********************************************************************************************
* GravitySensorHub.cpp
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
*********************************************************************************************/


#include "GravitySensorHub.h"
#include "GravityPh.h"
#include "GravityOrp.h"
#include "GravityEc.h"
#include "GravityTemperature.h"
#include "SensorDo.h"
#include "SdService.h"

//********************************************************************************************
// 函数名称: sensors[]
// 函数说明：存放传感器的数组   
// 参    数: 0  ph传感器  
// 参    数: 1  温度值传感器   
// 参    数: 2  溶解氧传感器 
// 参    数: 3  电导率传感器 
// 参    数: 4  氧化还原电位传感器 
//********************************************************************************************

GravitySensorHub::GravitySensorHub()
{
	for (size_t i = 0; i < this->SensorCount; i++)
	{
		this->sensors[i] = NULL;
	}

	this->sensors[0] = new GravityPh();
	this->sensors[1] = new GravityTemperature(5);
	this->sensors[2] = new SensorDo();
	this->sensors[3] = new GravityEc(this->sensors[1]);
	this->sensors[4] = new GravityOrp();

}

//********************************************************************************************
// 函数名称: ~GravitySensorHub()
// 函数说明：析构函数，释放所有的传感器 
//********************************************************************************************
GravitySensorHub::~GravitySensorHub()
{
	for (size_t i = 0; i < SensorCount; i++)
	{
		if (this->sensors[i])
		{
			delete this->sensors[i];
		}
	}
}


//********************************************************************************************
// 函数名称: setup()
// 函数说明：初始化所有传感器
//********************************************************************************************
void GravitySensorHub::setup()
{
	for (size_t i = 0; i < SensorCount; i++)
	{
		if (this->sensors[i])
		{
			this->sensors[i]->setup();
		}
	}
}


//********************************************************************************************
// 函数名称: update()
// 函数说明：更新所有传感器数值
//********************************************************************************************
void GravitySensorHub::update()
{
	for (size_t i = 0; i < SensorCount; i++)
	{
		if (this->sensors[i])
		{
			this->sensors[i]->update();
		}
	}
}

//********************************************************************************************
// 函数名称: getValueBySensorNumber()
// 函数说明：获取传感器数据
// 参    数: 0  ph传感器  
// 参    数: 1  温度值传感器   
// 参    数: 2  溶解氧传感器 
// 参    数: 3  电导率传感器 
// 参    数: 4  氧化还原电位传感器 
// 返 回 值: 返回获取的传感器数据
//********************************************************************************************
double GravitySensorHub::getValueBySensorNumber(int num)
{
	if (num >= SensorCount)
	{
		return 0;
	}
	return this->sensors[num]->getValue();
}
