#include "GravityDfr0553Adc.h"

GravityDfr0553Adc::GravityDfr0553Adc() :
	i2cAddress(0x48),
	fullScaleMilliVolts(6144.0f),
	available(false)
{
}

void GravityDfr0553Adc::setup(uint8_t address, float vccMillivolts)
{
	i2cAddress = address;
	fullScaleMilliVolts = vccMillivolts;

	Wire.begin();
	Wire.beginTransmission(i2cAddress);
	available = (Wire.endTransmission() == 0);
}

bool GravityDfr0553Adc::isAvailable() const
{
	return available;
}

float GravityDfr0553Adc::readMilliVolts(uint8_t channel, float fallbackMilliVolts)
{
	int16_t rawValue = 0;
	if (!readRawSingleEnded(channel, rawValue))
	{
		return fallbackMilliVolts;
	}

	if (rawValue < 0)
	{
		rawValue = 0;
	}

	return (rawValue * fullScaleMilliVolts) / 32768.0f;
}

bool GravityDfr0553Adc::readRawSingleEnded(uint8_t channel, int16_t &rawValue)
{
	if (!available || channel > 3)
	{
		return false;
	}

	const uint16_t mux = 0x04 + channel;
	const uint16_t config =
		0x8000 |          // Start single conversion.
		(mux << 12) |     // AIN0..AIN3 to GND.
		0x0000 |          // +/-6.144V full-scale range for 0..VCC sensors.
		0x0100 |          // Single-shot mode.
		0x0080 |          // 128 samples per second.
		0x0003;           // Disable comparator.

	if (!writeRegister(ConfigRegister, config))
	{
		available = false;
		return false;
	}

	delay(9);

	uint16_t rawRegister = 0;
	if (!readRegister(ConversionRegister, rawRegister))
	{
		available = false;
		return false;
	}

	rawValue = static_cast<int16_t>(rawRegister);
	return true;
}

bool GravityDfr0553Adc::writeRegister(uint8_t reg, uint16_t value)
{
	Wire.beginTransmission(i2cAddress);
	Wire.write(reg);
	Wire.write(static_cast<uint8_t>(value >> 8));
	Wire.write(static_cast<uint8_t>(value & 0xFF));
	return Wire.endTransmission() == 0;
}

bool GravityDfr0553Adc::readRegister(uint8_t reg, uint16_t &value)
{
	Wire.beginTransmission(i2cAddress);
	Wire.write(reg);
	if (Wire.endTransmission() != 0)
	{
		return false;
	}

	if (Wire.requestFrom(i2cAddress, static_cast<uint8_t>(2)) != 2)
	{
		return false;
	}

	value = static_cast<uint16_t>(Wire.read()) << 8;
	value |= static_cast<uint16_t>(Wire.read());
	return true;
}
