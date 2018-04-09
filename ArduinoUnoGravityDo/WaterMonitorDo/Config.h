#pragma once

//串口打印开关

//Serial print switch

#define DEBUG_AVR
//#define DEBUG_M0

//传感器滤波数组的最大长度

//The maximum length of the sensor filter array
#define ARRAYLENGTH 10

//SD卡更新数据的时间，60000为1分钟
//SD card update data time, 60,000 is 1 minute
#define SDUPDATEDATATIME 60000

//默认选择使用EC传感器，注释下面这行则使用TDS传感器
//EC sensor is selected by default, note this line uses TDS sensor
#define SELECTEC 

//传感器的引脚设置
//Sensor pin settings

#define DOPIN  A0
#define ECPIN  A1
#define TDSPIN A1
#define PHPIN  A2
#define ORPPIN A3
#define TEMPPIN 5


//设置传感器偏移量（校准数据
//Set sensor offset (calibration data)

#define PHOFFSET 0.12
#define ECKVALUE 0.6


//传感器最大个数

//The maximum number of sensors
#define SENSORCOUNT 5

//传感器对应数组编号，ph=0，temperature=1...,最大编号为SENSORCOUNT-1
//The sensor corresponds to the array number, ph=0, temperature=1..., the maximum number is SENSORCOUNT-1

enum SensorNumber
{
	phSensor = 0,
	temperatureSensor,
	doSensor,
	ecSensor,
	tdsSensor = 3,
	orpSensor
};
