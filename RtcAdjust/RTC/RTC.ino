#include "GravityRtc.h"
#include "Wire.h"  

GravityRtc rtc;     //RTC Initialization

void setup() {
  Serial.begin(9600);
  rtc.setup();

  //设置完时间后，请注释掉此行，以保证下次启动时，不会重置时间！！！！！！！
  //rtc.initRtc(2017,12,15,3,10,31,0);  //设置时间;2017/12/15，周三，10点31分0秒
  // After setting the time, please comment out this line to ensure that the next time you start, it will not reset the time! ! ! ! ! ! !
  // rtc.initRtc(2017,12,15,3,10,31,0); //setting time; 2017/12/15, Wednesday, 10:31:00:00
 

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

