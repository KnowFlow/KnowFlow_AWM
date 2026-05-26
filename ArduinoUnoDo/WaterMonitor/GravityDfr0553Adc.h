#pragma once

#include <Arduino.h>
#include <Wire.h>

class GravityDfr0553Adc
{
public:
	GravityDfr0553Adc();

	void setup(uint8_t address, float vccMillivolts);
	bool isAvailable() const;
	float readMilliVolts(uint8_t channel, float fallbackMilliVolts);

private:
	static const uint8_t ConversionRegister = 0x00;
	static const uint8_t ConfigRegister = 0x01;

	uint8_t i2cAddress;
	float fullScaleMilliVolts;
	bool available;

	bool writeRegister(uint8_t reg, uint16_t value);
	bool readRegister(uint8_t reg, uint16_t &value);
	bool readRawSingleEnded(uint8_t channel, int16_t &rawValue);
};
