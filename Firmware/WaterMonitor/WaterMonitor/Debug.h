/*********************************************************************
* Debug.h
*
* Copyright (C)    2017   [DFRobot](http://www.dfrobot.com),
* GitHub Link :https://github.com/DFRobot/watermonitor
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Description: Debug the print serial message,Cancel the comment //#define DEBUG_AVR 
* or //#define DEBUG_M0 can print the Arduino UNO, Mega2560 or M0 debugging information
*
*
* author  :  Jason(jason.ling@dfrobot.com)
* version :  V1.0
* date    :  2017-04-27
**********************************************************************/

#pragma once
#include <string.h>

//#define DEBUG_AVR
//#define DEBUG_M0

class Debug
{
public:
	static void print(double info)
	{
		
#ifdef DEBUG_M0
				SerialUSB.print(info);
#endif // DEBUG_M0

#ifdef DEBUG_AVR
				Serial.print(info);
#endif // DEBUG_AVR

	}

	
	static void print(const PROGMEM char* info)
	{

#ifdef DEBUG_M0
			SerialUSB.print(info);
#endif // DEBUG_M0

#ifdef DEBUG_AVR
			Serial.print(info);
#endif // DEBUG_AVR

	}

	static void print(String info)
	{

#ifdef DEBUG_M0
		SerialUSB.print(info);
#endif // DEBUG_M0

#ifdef DEBUG_AVR
		Serial.print(info);
#endif // DEBUG_AVR
	}
	
	static void println(double info)
	{

#ifdef DEBUG_M0
		SerialUSB.println(info);
#endif // DEBUG_M0

#ifdef DEBUG_AVR
		Serial.println(info);
#endif // DEBUG_AVR

	}

	static void println(const PROGMEM char* info)
	{

#ifdef DEBUG_M0
		SerialUSB.println(info);
#endif // DEBUG_M0

#ifdef DEBUG_AVR
		Serial.println(info);
#endif // DEBUG_AVR

	}

	static void println(String info)
	{

#ifdef DEBUG_M0
		SerialUSB.println(info);
#endif // DEBUG_M0

#ifdef DEBUG_AVR
		Serial.println(info);
#endif // DEBUG_AVR
}

};
