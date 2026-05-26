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
#include "GravityDfr0553Adc.h"
#include "config.h"


GravityPh::GravityPh():phSensorPin(PH_PIN), offset(0.0f),
adc(NULL), adcChannel(0),
samplingInterval(30),pHValue(0),voltage(0), sum(0)
{
}

GravityPh::GravityPh(GravityDfr0553Adc* adc, uint8_t adcChannel):phSensorPin(PH_PIN), offset(0.0f),
adc(adc), adcChannel(adcChannel),
samplingInterval(30),pHValue(0),voltage(0), sum(0)
{
}

//********************************************************************************************
// function name: setup ()
// Function Description: Initializes the ph sensor
//********************************************************************************************
void GravityPh::setup()
{
	pinMode(phSensorPin, INPUT);
}


//********************************************************************************************
// function name: update ()
// Function Description: Update the sensor value
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

		if (pHArrayIndex == arrayLength)   // 5 * 20 = 100ms
		{
			pHArrayIndex = 0;
			for (int i = 0; i < arrayLength; i++)
				this->sum += pHArray[i];
			averageVoltage = this->sum / arrayLength;
			this->sum = 0;
			voltage = averageVoltage*5.0 / 1024.0;
			if (this->adc && this->adc->isAvailable())
			{
				voltage = this->adc->readMilliVolts(this->adcChannel, voltage * 1000.0f) / 1000.0f;
			}
			pHValue = 3.5*voltage + this->offset;
		}

	}
}


//********************************************************************************************
// function name: getValue ()
// Function Description: Returns the sensor data
//********************************************************************************************
double GravityPh::getValue()
{
	return this->pHValue;
}
