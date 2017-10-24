

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

## About Branch
We have 3 Branch.

master is for the reales vision.

devlop is for the research vision. It will have some new feature, something like IOT, new sensor, etc, but will not fully tested.

test is for the learning github, so we will delete when we know how to use github.

We are newbee with github, please forgive us some stupid movement.


## To DO List
- support DO Senser from DFRobot.
- add the video tutorial.
- Website.
- Modify the construction of the files system.
- other issues.


## Documents

 * [Tutorial][1]
 * [GreenSeed online courses][2]
 * [Application:非洲茶园水质调研][3]
 * [Application:Willow Creek Water Quality Monitoring][4]

## License

All KnowFlow related materials are released under the [Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)][5]
 


  [1]: https://publiclab.org/notes/shanlter/06-08-2017/knowflow-automatic-water-meter
  [2]: http://blog.sina.com.cn/s/blog_9f86b6d50102w9m1.html
  [3]: http://www.dfrobot.com.cn/community/thread-26733-1-1.html
  [4]: https://publiclab.org/notes/MadTinker/07-31-2017/willow-creek-water-quality-monitoring
  [5]: https://creativecommons.org/licenses/by-nc-sa/4.0/
