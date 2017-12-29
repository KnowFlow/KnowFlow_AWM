#pragma once

//串口打印开关
#define DEBUG_AVR
//#define DEBUG_M0

//传感器滤波数组的最大长度
#define ARRAYLENGTH 10

//SD卡更新数据的时间，60000为1分钟
#define SDUPDATEDATATIME 60000

//默认选择使用EC传感器，注释下面这行则使用TDS传感器
#define SELECTEC 

//传感器的引脚设置
#define DOPIN  A0
#define ECPIN  A1
#define TDSPIN A1
#define PHPIN  A2
#define ORPPIN A3
#define TEMPPIN 5

//设置传感器偏移量（校准数据）
#define PHOFFSET 0.12
#define ECKVALUE 0.6


//传感器最大个数
#define SENSORCOUNT 5

//传感器对应数组编号，ph=0，temperature=1...,最大编号为SENSORCOUNT-1
enum SensorNumber
{
	phSensor = 0,
	temperatureSensor,
	doSensor,
	ecSensor,
	tdsSensor = 3,
	orpSensor
};
