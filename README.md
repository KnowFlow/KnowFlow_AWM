# KnowFlow - an open source river quality meter with Arduino

KnowFlow is an open source water monitoring device and an education program.

![](https://publiclab.org/system/images/photos/000/020/692/large/BOM.JPG)



For the device part, KnowFlow is designed for environmental activists, researchers, students... anyone who wants to know the water quality using low cost and customized tools. It is based on arduino uno, currently can monitor 5 parameters: Temperature, pH, ORP, Electronic conductivities, Dissolved Oxygen, the data is stored on a micro SD card, or read directly on phone by bluetooth (except for Dissolved Oxygen). All the modules are easy to change or add. Most of the sensor used are from DFRobot and Atlas Scientific, which are the main 2 sensor suppliers for Arduino users.

![](https://publiclab.org/system/images/photos/000/020/719/large/Lauren_Field_Test.jpg)

For the education program, KnowFlow is a 8 weeks online course and a learning group (launched on Greenseed Project platform). In which we will introduce the basic knowledge about water quality and indicators of water quality, Arduino and monitoring system, and show you how to build your own online monitor system based on arduino. Use Arduino as a master controller, and connected it to a variety of sensors. Except for the 5 parameters which are already included in the KnowFlow kits, you can add other environmental sensors on, such as carbon dioxide, ozone, dust, light, temperature, humidity sensors. Then use GPS and other communication module to connect all the data from distance. There will be step by step demos in the course to walk you through this learning process.

This page is a collective information lists for KnowFlow, it can also be found on github, [Youku](http://v.youku.com/v_show/id_XMTYzNTA1NzU1Mg==.html?spm=a2hzp.8253876.0.0&f=27620513).
Will release this series video tutorial on youtube later soon!



## KnowFlow Hardware 

[You can buy all KnowFlow Components online, the comprehansive list is here.](https://docs.google.com/spreadsheets/d/1rwVUIwqTOvZiKi_0vdBPrXMIw2YB-nsFnhaVy5seE-M/edit?usp=sharing)

Central Control Unit: Arduino Uno (DFRobot Bluno in this case) and Expansion Shield (DFRobot Expansion Shield V7.1 in this case)
Water Sensors: pH (pH probe and pH circuit board); EC (EC probe and EC circuit board); ORP (ORP probe and ORP circuit board); Temperature (temperature probe and temperature circuit board); Dissolved Oxygen (DO probe, BNC and circuit board); real time clock circuit board
Data Storage: Micro-SD module, Micro SD card
Fit and fix: mounting plate, water proof box( 200mm_150mm_75mm), water proof joint
Other parts: Cables (Wires), bread board, bolts and nuts, screws, battery, double-sided adhesive, write on tape, small wrench, spiral cable wrap
The size, modal, drawings, and other specifications of the materials can be found here at google docs.
We are still working with DFRobot team to release a KnowFlow starter kit, which will be available in next several months. If you’re interested in our product. Please contact with us via email. 
Email addr - @ShanHe

## KnowFlow Firmware

Download Arduino IDE

Download Knowflow code from KnowFlow github

find "WaterMonitor.ino" from the downloaded file, open it with Arduino IDE

Connect your Arduino Uno board, in menus, select "Tools - Board: Arduino Uno", and "Ports - /dev/cu.usb..."

click "Verify", than "Upload" the software to your board.

Note: KnowFlow software library is designed for the beginner level users. 
You don’t need to have rich experience on Arduino or software development. 
KnowFlow team packaged 7 software libraries to make it easier for you to enable different sensor features for your application. 
Feel free to commit your software question via our wiki page on public lab or github.

## How to build KnowFlow 

https://publiclab.org/notes/shanlter/06-08-2017/knowflow-automatic-water-meter


## To DO List
- support DO Senser from DFRobot.
- add the video tutorial.
- Website.
- Modify the construction of the files system.
- other issues.


### Documents

 * [tutorial][15]
 * [GreenSeed online courses][16]
 * [application:非洲茶园水质调研][17]
 * [application:Willow Creek Water Quality Monitoring][18]

## License

All KnowFlow related materials are released under the [Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)] [25]
 


  [1]: https://www.dfrobot.com/product-1071.html
  [2]: https://www.dfrobot.com/product-489.html
  [3]: https://www.dfrobot.com/product-1190.html
  [4]: https://www.dfrobot.com/product-770.html
  [5]: https://publiclab.org/system/images/photos/000/020/692/large/BOM.JPG
  [6]: https://www.dfrobot.com/product-1044.html
  [7]: https://www.dfrobot.com/product-1025.html
  [8]: https://www.dfrobot.com/product-1123.html
  [9]: https://www.dfrobot.com/product-1009.html
  [10]: https://www.dfrobot.com/product-1600.html
  [11]: https://www.dfrobot.com/product-875.html
  [12]: https://www.dfrobot.com/product-1621.html
  [13]: https://www.dfrobot.com/product-1190.html
  [14]: https://github.com/KnowFlow/KnowFlow_AWM
  [15]: https://publiclab.org/notes/shanlter/06-08-2017/knowflow-automatic-water-meter
  [16]: http://blog.sina.com.cn/s/blog_9f86b6d50102w9m1.html
  [17]: http://www.dfrobot.com.cn/community/thread-26733-1-1.html
  [18]: https://publiclab.org/notes/MadTinker/07-31-2017/willow-creek-water-quality-monitoring
  [19]: https://www.dfrobot.com/wiki/index.php/PH_meter%28SKU:_SEN0161%29
  [20]: https://www.dfrobot.com/wiki/index.php/Analog_EC_Meter_SKU:DFR0300
  [21]: https://www.dfrobot.com/wiki/index.php/Gravity:_I2C_SD2405_RTC_Module_SKU:_DFR0469
  [22]: https://github.com/Arduinolibrary/DFRobot_Gravity_Analog_Signal_Isolator_DFR0504/raw/master/Analog%20Isolation%20Module%28V1.0%29%20Schematic.pdf
  [23]: https://github.com/Arduinolibrary/DFRobot_Gravity_Analog_Signal_Isolator_DFR0504/raw/master/Analog%20Isolation%20Module%28V1.0%29%20Layout.pdf
  [24]: https://github.com/Arduinolibrary/DFRobot_Gravity_Analog_Signal_Isolator_DFR0504/raw/master/Datasheet.zip
  [25]:https://creativecommons.org/licenses/by-nc-sa/4.0/
  
