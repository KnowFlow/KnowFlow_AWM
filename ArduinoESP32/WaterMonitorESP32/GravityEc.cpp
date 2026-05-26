#include "GravityEc.h"
#include "Config.h"
#include "ESP32ADC.h"

extern uint16_t readMedianValue(int* dataArray, uint16_t arrayLength);

GravityEc::GravityEc() :kValue(1.0), pin(ECPIN)
{
}


GravityEc::~GravityEc()
{
}

void GravityEc::setup()
{
	pinMode(pin, INPUT);
}


void GravityEc::update()
{
	int ecValueBuffer[ARRAYLENGTH];
	float averageVoltage;
	for (uint8_t i = 0; i < ARRAYLENGTH; i++)
	{
		// Use ESP32-compatible analogRead (returns Arduino-compatible 10-bit value)
		ecValueBuffer[i] = analogReadESP32(this->pin);
		delay(10);
	}
	// ESP32: Convert to voltage (5000mV = 5V reference for compatibility)
	averageVoltage = readMedianValue(ecValueBuffer, ARRAYLENGTH)/1024.0*5000.0;
	this->ecValue = 1000 * averageVoltage / 820.0 / 196.0 /this->kValue;

}

double GravityEc::getValue()
{
	return this->ecValue;
}

void GravityEc::setKValue(float value)
{
	this->kValue = value;
}