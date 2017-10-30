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
 * DO  : Serial port Rx(0),Tx(1)
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
#include <Arduino.h>
#include "GravitySensorHub.h"
#include <stdlib.h>
#include "GravityRtc.h"
#include "OneWire.h"
#include "SdService.h"
#include "Debug.h"

//############################################################################################
/*
#include <LiquidCrystal.h>					 //COMMENT*** import a new library here
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);         //COMMENT*** select the pins used on the LCD panel
											 //COMMENT*** define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
*/
//############################################################################################

// clock module
GravityRtc rtc;

// sensor monitor
GravitySensorHub sensorHub;
SdService sdService = SdService(sensorHub.sensors);              

void setup() {
	Serial.begin(9600);
	rtc.setup();
	sensorHub.setup();
	sdService.setup();

//############################################################################################
//* ***************************** LCD screen initialize setting ************** ************ * /

// 	lcd.begin(16, 2);              //COMMENT*** Start the screen
// 	lcd.setCursor(0,0);			   //COMMENT*** Initial the cursor 
// 	lcd.print("Hello, World");	   //COMMENT*** Print 'Hello, World' on the screen
//############################################################################################

}


//********************************************************************************************
// function name: sensorHub.getValueBySensorNumber (0)
// Function Description: Get the sensor's values, and the different parameters represent the acquisition of different sensor data     
// Parameters: 0 ph value  
// Parameters: 1 temperature value    
// Parameters: 2 Dissolved Oxygen
// Parameters: 3 Conductivity
// Parameters: 4 Redox potential
// return value: returns a double type of data
//********************************************************************************************

unsigned long updateTime = 0;

void loop() {
	rtc.update();
	sensorHub.update();
	sdService.update();


		// ************************* Serial debugging ******************
//	if(millis() - updateTime > 1000)
//  {
//    updateTime = millis();
//    Serial.print(F("ph= "));
//    Serial.print(sensorHub.getValueBySensorNumber(0));
//    Serial.print(F("  Temp= "));
//    Serial.print(sensorHub.getValueBySensorNumber(1));
//    Serial.print(F("  Do= "));
//    Serial.print(sensorHub.getValueBySensorNumber(2));
//    Serial.print(F("  Ec= "));
//    Serial.print(sensorHub.getValueBySensorNumber(3));
//    Serial.print(F("  Orp= "));
//    Serial.println(sensorHub.getValueBySensorNumber(4));
//  }

//############################################################################################
		//* ***************************** LCD screen & Buttons debugging **************

/*
lcd.setCursor(9,1);             // move cursor to second line "1" and 9 spaces over
   lcd.print(millis()/1000);       // display seconds elapsed since power-up

   lcd.setCursor(0,1);             // move to the begining of the second line
   lcd_key = read_LCD_buttons();   // read the buttons

   switch (lcd_key){               // depending on which button was pushed, we perform an action

       case btnRIGHT:{             //  push button "RIGHT" and show the word on the screen
            lcd.print("RIGHT ");
            break;
       }
       case btnLEFT:{
             lcd.print("LEFT   "); //  push button "LEFT" and show the word on the screen
             break;
       }    
       case btnUP:{
             lcd.print("UP    ");  //  push button "UP" and show the word on the screen
             break;
       }
       case btnDOWN:{
             lcd.print("DOWN  ");  //  push button "DOWN" and show the word on the screen
             break;
       }
       case btnSELECT:{
             lcd.print("SELECT");  //  push button "SELECT" and show the word on the screen
             break;
       }
       case btnNONE:{
             lcd.print("NONE  ");  //  No action  will show "None" on the screen
             break;
       }
   }
*/
//############################################################################################	

}



//* ***************************** Print the relevant debugging information ************** ************ * /
// Note: Arduino M0 need to replace Serial with SerialUSB when printing debugging information

// ************************* Serial debugging ******************
//Serial.print("ph= ");
//Serial.print(sensorHub.getValueBySensorNumber(0));
//Serial.print("  Temp= ");
//Serial.print(sensorHub.getValueBySensorNumber(1));
//Serial.print("  Orp= ");
//Serial.println(sensorHub.getValueBySensorNumber(4));
//Serial.print("  EC= ");
//Serial.println(sensorHub.getValueBySensorNumber(3));


// ************************************************************ time ********************** **********
//Serial.print("   Year = ");//year
//Serial.print(rtc.year);
//Serial.print("   Month = ");//month
//Serial.print(rtc.month);
//Serial.print("   Day = ");//day
//Serial.print(rtc.day);
//Serial.print("   Week = ");//week
//Serial.print(rtc.week);
//Serial.print("   Hour = ");//hour
//Serial.print(rtc.hour);
//Serial.print("   Minute = ");//minute
//Serial.print(rtc.minute);
//Serial.print("   Second = ");//second
//Serial.println(rtc.second);


//############################################################################################
//* ***************************** LCD screen & Buttons debugging (Function)************** ************ * /
/*
int read_LCD_buttons(){               // read the buttons
    adc_key_in = analogRead(0);       // read the value from the sensor 

    // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
    // we add approx 50 to those values and check to see if we are close
    // We make this the 1st option for speed reasons since it will be the most likely result

    if (adc_key_in > 1000) return btnNONE; 

    // For V1.1 us this threshold
    if (adc_key_in < 50)   return btnRIGHT;  
    if (adc_key_in < 250)  return btnUP; 
    if (adc_key_in < 450)  return btnDOWN; 
    if (adc_key_in < 650)  return btnLEFT; 
    if (adc_key_in < 850)  return btnSELECT;  

   // For V1.0 comment the other threshold and use the one below:
   /*
     if (adc_key_in < 50)   return btnRIGHT;  
     if (adc_key_in < 195)  return btnUP; 
     if (adc_key_in < 380)  return btnDOWN; 
     if (adc_key_in < 555)  return btnLEFT; 
     if (adc_key_in < 790)  return btnSELECT;   
   */

    return btnNONE;                // when all others fail, return this.
}
*/
//############################################################################################


















