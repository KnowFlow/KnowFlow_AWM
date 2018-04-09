#include "GravityTDS.h"
#include "Config.h"

GravityTDS::GravityTDS():pin(TDSPIN),vref(5.0),temperature(25.0)
{
}

GravityTDS::~GravityTDS()
{

}

void GravityTDS::setPin(int pin)
{
	this->pin = pin;
}


void GravityTDS::setup()
{
	    pinMode(this->pin,INPUT);

}

float GravityTDS::setTemperature(float temp)
{
	this->temperature = temp;
}

float GravityTDS::setVref(float value)
{
	this->vref = value;
}

extern uint16_t readMedianValue(int* dataArray, uint16_t arrayLength);

void GravityTDS::update()
{
	for (uint8_t i = 0; i < COUNT; i++)
	{
		analogBuffer[i] = analogRead(this->pin);    //read an analog value every 20ms
		delay(10);
	}
	averageVoltage = readMedianValue(analogBuffer, COUNT);
	averageVoltage = averageVoltage* vref / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
	float compensationCoefficient=1.0+0.02*(temperature-25.0);    //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
	float compensationVolatge=averageVoltage/compensationCoefficient;  //temperature compensation
	tdsValue=(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 255.86*compensationVolatge*compensationVolatge + 857.39*compensationVolatge)*0.5; //convert voltage value to tds value
}

double GravityTDS::getValue()
{
	return tdsValue;
}

uint16_t GravityTDS::readMedianValue(int* dataArray, uint16_t arrayLength)
{
	uint16_t i, j, tempValue;
	// 用冒泡法对数组进行排序

	// Bubble sort array

	for (j = 0; j < arrayLength - 1; j++)
	{
		for (i = 0; i < arrayLength - 1 - j; i++)
		{
			if (dataArray[i] > dataArray[i + 1])
			{
				tempValue = dataArray[i];
				dataArray[i] = dataArray[i + 1];
				dataArray[i + 1] = tempValue;
			}
		}
	}
	// 计算中值

	// Calculate median
	if ((arrayLength & 1) > 0)
	{
		// 数组有奇数个元素，返回中间一个元素
		// The array has an odd number of elements, returning one element in the middle

		tempValue = dataArray[(arrayLength - 1) / 2];
	}
	else
	{
		// 数组有偶数个元素，返回中间两个元素平均值

		// The array has an even number of elements, returning the average of the two elements in the middle

		tempValue = (dataArray[arrayLength / 2] + dataArray[arrayLength / 2 - 1]) / 2;
	}
	return tempValue;
}

