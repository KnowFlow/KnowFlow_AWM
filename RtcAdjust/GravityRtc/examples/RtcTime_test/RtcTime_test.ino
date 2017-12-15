#include "GravityRtc.h"
#include "Wire.h"  


GravityRtc rtc;     //RTC Initialization

void setup() {
  Serial.begin(9600);
  rtc.setup();

  //rtc.initRtc(2017,6,19,1,12,7,0);  //Set Time: 2017/June/19th/Monday/12:07:0 am
  //Please comment it after you have set time successfully!!!!!!!

}

void loop() {
  rtc.update();
  //*************************Time********************************
  Serial.print("   Year = ");//year
  Serial.print(rtc.year);
  Serial.print("   Month = ");//month
  Serial.print(rtc.month);
  Serial.print("   Day = ");//day
  Serial.print(rtc.day);
  Serial.print("   Week = ");//week
  Serial.print(rtc.week);
  Serial.print("   Hour = ");//hour
  Serial.print(rtc.hour);
  Serial.print("   Minute = ");//minute
  Serial.print(rtc.minute);
  Serial.print("   Second = ");//second
  Serial.println(rtc.second);
  delay(1000);

}

