#include "Arduino.h"
uint16_t readMedianValue(int* dataArray, uint16_t arrayLength)
{
	uint16_t i, j, tempValue;
	// 用冒泡法对数组进行排序

	// Bubble sorting array

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

	// Calculated median
	if ((arrayLength & 1) > 0)
	{
		// 数组有奇数个元素，返回中间一个元素
		// The array has an odd number of elements, returning one element in the middle

		tempValue = dataArray[(arrayLength - 1) / 2];
	}
	else
	{
		// 数组有偶数个元素，返回中间两个元素平均值

		// The array has an even number of elements, return the average of the two elements in the middle

		tempValue = (dataArray[arrayLength / 2] + dataArray[arrayLength / 2 - 1]) / 2;
	}
	return tempValue;
}