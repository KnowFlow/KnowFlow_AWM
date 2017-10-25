#include <avr/pgmspace.h>
#include <EEPROM.h>
#include "GravityDo.h"


#define EEPROM_write(address, p) {int i = 0; byte *pp = (byte*)&(p);for(; i < sizeof(p); i++) EEPROM.write(address+i, pp[i]);}
#define EEPROM_read(address, p)  {int i = 0; byte *pp = (byte*)&(p);for(; i < sizeof(p); i++) pp[i]=EEPROM.read(address+i);}


#define SaturationDoVoltageAddress 12          //the address of the Saturation Oxygen voltage stored in the EEPROM
#define SaturationDoTemperatureAddress 16      //the address of the Saturation Oxygen temperature stored in the EEPROM

const float SaturationValueTab[41] PROGMEM = {      //saturation dissolved oxygen concentrations at various temperatures
14.46, 14.22, 13.82, 13.44, 13.09,
12.74, 12.42, 12.11, 11.81, 11.53,
11.26, 11.01, 10.77, 10.53, 10.30,
10.08, 9.86,  9.66,  9.46,  9.27,
9.08,  8.90,  8.73,  8.57,  8.41,
8.25,  8.11,  7.96,  7.82,  7.69,
7.56,  7.43,  7.30,  7.18,  7.07,
6.95,  6.84,  6.73,  6.63,  6.53,
6.41,
};


GravityDo::GravityDo()
{
    _pin = A4;
    _vref = 500;
    _temperature = 25;
    _doValue = 0;
    _receivedBufferIndex = 0;
    _analogBufferIndex = 0;
    _copyIndex = 0;
    _saturationDoVoltage = 0;
    _saturationDoTemperature = 0;
    _averageVoltage = 0;
}

GravityDo::~GravityDo()
{

}

void GravityDo::setPin(int pin)
{
    this->_pin = pin;
    pinMode(this->_pin,INPUT);
}
void GravityDo::setTemperature(float temperature)
{
    this->_temperature = temperature;
}

void GravityDo::setup()
{
    readDoCharacteristicValues();      //read Characteristic Values calibrated from the EEPROM
}


void GravityDo::readDoCharacteristicValues()
{
    EEPROM_read(SaturationDoVoltageAddress, this->_saturationDoVoltage);  
    EEPROM_read(SaturationDoTemperatureAddress, this->_saturationDoTemperature);
    if(EEPROM.read(SaturationDoVoltageAddress)==0xFF && EEPROM.read(SaturationDoVoltageAddress+1)==0xFF && EEPROM.read(SaturationDoVoltageAddress+2)==0xFF && EEPROM.read(SaturationDoVoltageAddress+3)==0xFF)
    {
      this->_saturationDoVoltage = 1127.6;   //default voltage:1127.6mv
      EEPROM_write(SaturationDoVoltageAddress, this->_saturationDoVoltage);
    }
    if(EEPROM.read(SaturationDoTemperatureAddress)==0xFF && EEPROM.read(SaturationDoTemperatureAddress+1)==0xFF && EEPROM.read(SaturationDoTemperatureAddress+2)==0xFF && EEPROM.read(SaturationDoTemperatureAddress+3)==0xFF)
    {
      this->_saturationDoTemperature = 25.0;   //default temperature is 25^C
      EEPROM_write(SaturationDoTemperatureAddress, this->_saturationDoTemperature);
    }    

}


void GravityDo::update()
{
    static unsigned long analogSampleTimepoint = millis();
    static unsigned long printTimepoint = millis();
    if(millis()-analogSampleTimepoint > 30U)     //every 30 milliseconds,read the analog value from the ADC
    {
        analogSampleTimepoint = millis();
        analogBuffer[this->_analogBufferIndex] = analogRead(this->_pin);    //read the analog value and store into the buffer
        this->_analogBufferIndex++;
        if(this->_analogBufferIndex == scount) 
            this->_analogBufferIndex = 0;
    }
   if(millis()-printTimepoint > 1000U)
   {
      printTimepoint = millis();
      for(this->_copyIndex=0;this->_copyIndex<scount;this->_copyIndex++)
      {
        analogBufferTemp[this->_copyIndex]= analogBuffer[this->_copyIndex];
      }
      this->_averageVoltage = getMedianNum(analogBufferTemp,scount) * (float)this->_vref / 1024.0; // read the value more stable by the median filtering algorithm
      this->_doValue = pgm_read_float_near( &SaturationValueTab[0] + (int)(this->_saturationDoTemperature+0.5) ) * this->_averageVoltage / this->_saturationDoVoltage;  //calculate the do value, doValue = Voltage / this->_saturationDoVoltage * SaturationDoValue(with temperature compensation)
   }
   if(serialDataAvailable() > 0)
   {
      byte modeIndex = uartParse();  //parse the uart command received
      doCalibration(modeIndex);    // If the correct calibration command is received, the calibration function should be called.
   }
}

bool GravityDo::serialDataAvailable()
{
  char receivedChar;
  static unsigned long receivedTimeOut = millis();
  while ( Serial.available() > 0 ) 
  {   
    if (millis() - receivedTimeOut > 500U) 
    {
        this->_receivedBufferIndex = 0;
        memset(receivedBuffer,0,(receivedBufferLength));
    }
    receivedTimeOut = millis();
    receivedChar = Serial.read();
    if (receivedChar == '\n' || this->_receivedBufferIndex == receivedBufferLength)
    {
        this->_receivedBufferIndex = 0;
        strupr(receivedBuffer);
        return true;
    }
    else
    {
        receivedBuffer[this->_receivedBufferIndex] = receivedChar;
        this->_receivedBufferIndex++;
    }
  }
  return false;
}

byte GravityDo::uartParse()
{
    byte modeIndex = 0;
    if(strstr(receivedBuffer, "CALIBRATION") != NULL) 
        modeIndex = 1;
    else if(strstr(receivedBuffer, "EXIT") != NULL) 
        modeIndex = 3;
    else if(strstr(receivedBuffer, "SATCAL") != NULL)   
        modeIndex = 2;
    return modeIndex;
}

void GravityDo::doCalibration(byte mode)
{
    char *receivedBufferPtr;
    static byte doCalibrationFinishFlag = 0;
    static byte enterCalibrationFlag = 0;
    switch(mode)
    {
      case 0:
      if(enterCalibrationFlag)
         Serial.println(F("Command Error"));
      break;
      
      case 1:
      enterCalibrationFlag = 1;
      doCalibrationFinishFlag = 0;
      Serial.println();
      Serial.println(F(">>>Enter Calibration Mode<<<"));
      Serial.println(F(">>>Please put the probe into the saturation oxygen water! <<<"));
      Serial.println();
      break;
     
     case 2:
      if(enterCalibrationFlag)
      {
         Serial.println();
         Serial.println(F(">>>Saturation Calibration Finish!<<<"));
         Serial.println();
         EEPROM_write(SaturationDoVoltageAddress, this->_averageVoltage);
         EEPROM_write(SaturationDoTemperatureAddress, this->_temperature);
         this->_saturationDoVoltage = this->_averageVoltage;
         this->_saturationDoTemperature = this->_temperature;
         doCalibrationFinishFlag = 1;
      }
      break;

        case 3:
        if(enterCalibrationFlag)
        {
            Serial.println();
            if(doCalibrationFinishFlag)      
               Serial.print(F(">>>Calibration Successful"));
            else 
              Serial.print(F(">>>Calibration Failed"));       
            Serial.println(F(",Exit Calibration Mode<<<"));
            Serial.println();
            doCalibrationFinishFlag = 0;
            enterCalibrationFlag = 0;
        }
        break;
    }
}

int GravityDo::getMedianNum(int bArray[], int iFilterLen) 
{
      int bTab[iFilterLen];
      for (byte i = 0; i<iFilterLen; i++)
      {
	  bTab[i] = bArray[i];
      }
      int i, j, bTemp;
      for (j = 0; j < iFilterLen - 1; j++) 
      {
	  for (i = 0; i < iFilterLen - j - 1; i++) 
          {
	    if (bTab[i] > bTab[i + 1]) 
            {
		bTemp = bTab[i];
	        bTab[i] = bTab[i + 1];
		bTab[i + 1] = bTemp;
	     }
	  }
      }
      if ((iFilterLen & 1) > 0)
	bTemp = bTab[(iFilterLen - 1) / 2];
      else
	bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
      return bTemp;
}


double GravityDo::getValue()
{
    return this->_doValue;
}

float GravityDo::getTemperature() const
{
    return this->_temperature;
}
