/*********************************************************************
* WaterMonitorESP32.ino
*
* Copyright (C)    2024   [KnowFlow Team]
* GitHub Link :https://github.com/KnowFlow/KnowFlow_AWM
* This Library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Description:
* This sample code is mainly used to monitor water quality on ESP32
* including ph, temperature, dissolved oxygen, ec and orp,etc.
*
* Software Environment: Arduino IDE 1.8.13+ with ESP32 board support
* ESP32 Board Manager URL: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
*
* Hardware platform: ESP32 (ESP32-DevKitC recommended)
* Sensor pin:
* EC  : GPIO35 (ADC1_CH7)
* PH  : GPIO34 (ADC1_CH6)
* ORP : GPIO32 (ADC1_CH4)
* RTC : I2C (GPIO21 SDA, GPIO22 SCL)
* DO  : GPIO33 (ADC1_CH5)
* Temperature: GPIO4 (OneWire)
*
* SD card attached to SPI bus as follows:
* ESP32:  MOSI - GPIO23, MISO - GPIO19, CLK - GPIO18, CS - GPIO5
*
* author  :  KnowFlow Team
* version :  V1.0
* date    :  2024
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
#include "Config.h"

// Alias clock module logic as rtc
GravityRtc rtc;

// Alias sensor logic as sensorHub 
GravitySensorHub sensorHub;

// Alias SD logic as sdService applied to sensors
SdService sdService = SdService(sensorHub.sensors);

void setup() {
	// Open communication at 115200 baud (ESP32 default)
	Serial.begin(115200);
	delay(1000);  // Give serial monitor time to connect
	
	// Initialize ESP32 ADC
	initESP32ADC();
	
	Debug::println("=== KnowFlow ESP32 Water Monitor ===");
	Debug::println("Serial begin");
	
	// Initialize RTC module
	Debug::println("rtc.setup");
	rtc.setup();

	// Reset and initialize sensors
	Debug::println("sensorHub setup");
	sensorHub.setup();

	// Apply calibration offsets
	// Calibrate pH
	((GravityPh*)(sensorHub.sensors[phSensor]))->setOffset(PHOFFSET);
	Debug::print("pH offset: ");
	Debug::println(PHOFFSET);
	
	// Calibrate EC if present
	#ifdef SELECTEC
	((GravityEc*)(sensorHub.sensors[ecSensor]))->setKValue(ECKVALUE);
	Debug::print("EC K Value: ");
	Debug::println(ECKVALUE);
	#endif
	
	// Check for SD card and configure datafile
	Debug::println("sdService setup");
	sdService.setup();
	
	Debug::println("Setup complete!");
}

// Create variable to track time
unsigned long updateTime = 0;

void loop() {
	// Update time from clock module
	rtc.update();

	// Collect sensor readings
	sensorHub.update();

	// Write data to SD card
	sdService.update();
	
	// Optional: Serial output for debugging (every 2 seconds)
	#ifdef DEBUG_ESP32
	if(millis() - updateTime > 2000)
	{
		updateTime = millis();
		Serial.print(F("pH= "));
		Serial.print(sensorHub.getValueBySensorNumber(phSensor));
		Serial.print(F("  Temp= "));
		Serial.print(sensorHub.getValueBySensorNumber(temperatureSensor));
		Serial.print(F("  DO= "));
		Serial.print(sensorHub.getValueBySensorNumber(doSensor));
		Serial.print(F("  EC= "));
		Serial.print(sensorHub.getValueBySensorNumber(ecSensor));
		Serial.print(F("  ORP= "));
		Serial.println(sensorHub.getValueBySensorNumber(orpSensor));
	}
	#endif
}

