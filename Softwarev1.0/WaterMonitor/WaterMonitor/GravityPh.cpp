/*********************************************************************
* GravityPh.cpp
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
* Sensor driver pin：A2 (phSensorPin(A2))
*
* author  :  Jason(jason.ling@dfrobot.com)
* version :  V1.0
* date    :  2017-04-07
**********************************************************************/

#include "GravityPh.h"


GravityPh::GravityPh():phSensorPin(A2), offset(0.0f), 
samplingInterval(30),pHValue(0),voltage(0), sum(0)
{
}

//********************************************************************************************
// 函数名称: setup()
// 函数说明：初始化ph传感器
//********************************************************************************************
void GravityPh::setup()
{
	pinMode(phSensorPin, INPUT);
}


//********************************************************************************************
// 函数名称: update()
// 函数说明：更新传感器数值
//********************************************************************************************
void GravityPh::update()
{
	static unsigned long samplingTime = millis();
	static unsigned long printTime = millis();
	static int pHArrayIndex = 0;
	if (millis() - samplingTime > samplingInterval)
	{
		samplingTime = millis();
		pHArray[pHArrayIndex++] = analogRead(this->phSensorPin);

		if (pHArrayIndex == arrayLength)  // 5*20 = 100ms计算一次
		{
			pHArrayIndex = 0;
			for (int i = 0; i < arrayLength; i++)
				this->sum += pHArray[i];
			averageVoltage = this->sum / arrayLength;
			this->sum = 0;
			voltage = averageVoltage*5.0 / 1024.0;
			pHValue = 3.5*voltage + this->offset;
		}	
		
	}
}


//********************************************************************************************
// 函数名称: getValue()
// 函数说明：返回传感器数据
//********************************************************************************************
double GravityPh::getValue()
{
	return this->pHValue;
}


