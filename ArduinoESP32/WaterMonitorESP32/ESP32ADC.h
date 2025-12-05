/*********************************************************************
* ESP32ADC.h
*
* Copyright (C)    2024   [KnowFlow Team]
* ESP32 ADC adapter for compatibility with Arduino sensor drivers
*
* Description:
* This file provides ADC reading functions that are compatible with
* Arduino sensor drivers while utilizing ESP32's 12-bit ADC precision.
*
* ESP32 ADC characteristics:
* - 12-bit resolution (0-4095)
* - 3.3V reference voltage
* - ADC1 channels: GPIO32-39
*
* Arduino ADC characteristics:
* - 10-bit resolution (0-1023)
* - 5V reference voltage (typically)
*
* author  :  KnowFlow Team
* version :  V1.0
* date    :  2024
**********************************************************************/

#pragma once
#include <Arduino.h>
#include "Config.h"

/**
 * ESP32-compatible analogRead function
 * Returns value compatible with Arduino 10-bit ADC (0-1023)
 * This allows existing sensor drivers to work without modification
 */
inline int analogReadESP32(int pin) {
	// ESP32 analogRead returns 12-bit value (0-4095)
	int esp32Value = analogRead(pin);
	
	// Convert ESP32 12-bit value to Arduino-compatible 10-bit value
	// This maintains compatibility with existing sensor calibration code
	return ESP32_TO_ARDUINO_ADC(esp32Value);
}

/**
 * Get ESP32 native 12-bit ADC value
 * Use this for higher precision when needed
 */
inline int analogReadESP32_12bit(int pin) {
	return analogRead(pin);
}

/**
 * Convert ESP32 ADC value to voltage in millivolts
 */
inline float analogReadToVoltage(int pin) {
	int adcValue = analogRead(pin);
	return ESP32_ADC_TO_VOLTAGE(adcValue);
}

/**
 * Initialize ESP32 ADC
 * Sets ADC width and attenuation for optimal sensor reading
 */
inline void initESP32ADC() {
	// Set ADC width to 12 bits (default, but explicit for clarity)
	analogSetWidth(ESP32_ADC_RESOLUTION);
	
	// Set ADC attenuation to 11dB (0-3.3V range)
	// This is suitable for most sensors that output 0-3.3V
	analogSetAttenuation(ADC_11db);
}

