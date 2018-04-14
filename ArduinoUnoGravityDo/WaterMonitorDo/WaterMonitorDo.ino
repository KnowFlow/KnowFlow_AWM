/*********************************************************************
* WaterMonitor.ino
*
* Copyright (C)    2017   [DFRobot](http://www.dfrobot.com)
* GitHub Link :https://github.com/DFRobot/watermonitor
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Description:
* This sample code is mainly used to monitor water quality
* including ph, temperature, dissolved oxygen, ec and orp,etc.
*
* Software Environment: Arduino IDE 1.8.2
* Software download link: https://www.arduino.cc/en/Main/Software
*
* Install the library file：
* Copy the files from the github repository folder libraries to the libraries
* in the Arduino IDE 1.8.2 installation directory
*
* Hardware platform   : Arduino M0 Or Arduino Mega2560
* Sensor pin:
* EC  : A1
* PH  : A2
* ORP : A3
* RTC : I2C
* DO  : A0
* GravityDO：A4
* temperature:D5
*
* SD card attached to SPI bus as follows:
* Mega:  MOSI - pin 51, MISO - pin 50, CLK - pin 52, CS - pin 53
* and pin #53 (SS) must be an output
* M0:   Onboard SPI pin,CS - pin 4 (CS pin can be changed)
*
* author  :  Jason(jason.ling@dfrobot.com)
* version :  V1.0
* date    :  2017-04-06
**********************************************************************/

#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "GravitySensorHub.h"
#include "GravityRtc.h"
#include "GravityEc.h"
#include "GravityPh.h"
#include "GravityDo.h"
#include "OneWire.h"
#include "SdService.h"
#include "Debug.h"

// Alias clock module logic as rtc
GravityRtc rtc;

// Alias sensor logic as sensorHub 
GravitySensorHub sensorHub;

// Alias SD logic as sdService applied to sensors
SdService sdService = SdService(sensorHub.sensors);

void setup() {
	
	//Open communication at 9600 baud
	Serial.begin(9600);
	Debug::println("Serial begin");
	
	//initialize RTC module with computer time
	Debug::println("rtc.setup");
	rtc.setup();

	//Reset and initialize sensors
	Debug::println("sensorHub setup");
	sensorHub.setup();

	//Apply calibration offsets
	//Calibrate pH
	((GravityPh*)(sensorHub.sensors[phSensor]))->setOffset(PHOFFSET);
	Debug::print("pH offset: ");
	Debug::println(PHOFFSET);
	
	// Calibrate EC if present
	#ifdef SELECTEC
	((GravityEc*)(sensorHub.sensors[ecSensor]))->setKValue(ECKVALUE);
	Debug::print("EC K Value: ");
	Debug::println(ECKVALUE);
	#endif
	
	//Check for SD card and configure datafile
	Debug::println("sdService setup");
	sdService.setup();
}

//Create variable to track time
unsigned long updateTime = 0;

void loop() {
	//Update time from clock module
	rtc.update();

	//Collect sensor readings
	sensorHub.update();

	//Write data to SD card
	sdService.update();
}
