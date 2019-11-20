

This branch is for ongoing development


# KnowFlow - an open source river quality meter with Arduino

KnowFlow is an open source water monitoring device and an education program.

![](https://publiclab.org/system/images/photos/000/020/692/large/BOM.JPG)



For the device part, KnowFlow is designed for environmental activists, researchers, students... anyone
who wants to know the water quality using low cost and customized tools. It is based on arduino uno and 
can currently monitor 5 parameters: Temperature, pH, ORP, Electrical conductivity and Dissolved Oxygen. 
The data is stored on a micro SD card and can be read directly on phone by bluetooth (except for Dissolved Oxygen). 
All the modules are easy to change or add. Most of the sensors used are from DFRobot and Atlas Scientific, 
the main 2 sensor suppliers for Arduino users.

![](https://publiclab.org/system/images/photos/000/020/719/large/Lauren_Field_Test.jpg)

For the education program, KnowFlow is an 8 week online course and a learning group hosted on 
Greenseed Project platform. During the course, we cover the fundamentals of water quality, indicators of water quality, 
Arduino and monitoring systems and show you how to build your own monitoring system based on Arduino. In addition to 
the 5 included in the KnowFlow kits, you can add other environmental sensors, such as carbon dioxide, ozone, 
dust, light, temperature, or humidity sensors, then add GPS and a communication module to connect data from a distance. 
Step by step demos in the course walk you through the learning process.

This page is a collective information for KnowFlow, it can also be found on github, [Youku](http://v.youku.com/v_show/id_XMTYzNTA1NzU1Mg==.html?spm=a2hzp.8253876.0.0&f=27620513).
Will release this series video tutorial on youtube later soon!



## KnowFlow Hardware 

A complete list of components, measurements, drawings, and other specifications can be found [here](https://docs.google.com/spreadsheets/d/1rwVUIwqTOvZiKi_0vdBPrXMIw2YB-nsFnhaVy5seE-M).
DFRobot also offers a [KnowFlow starter kit.](https://www.dfrobot.com/product-1649.html)

#### Central Control Unit: 
* Arduino Uno (DFRobot Bluno in this case) and 
* Expansion Shield (DFRobot Expansion Shield V7.1 in this case)  
* real time clock circuit board
#### Water Sensors: 
* pH (pH probe and pH circuit board)
* EC (EC probe and EC circuit board)
* ORP (ORP probe and ORP circuit board)
* Temperature (temperature probe and temperature circuit board)
* Dissolved Oxygen (DO probe, BNC and circuit board)
#### Data Storage:
* Micro-SD module
* Micro SD card
#### Fit and finish:
* Mounting plate
* Water proof box(200mm_150mm_75mm)
* Water proof bushing
#### Other parts: 
* Wires
* Bread board
* Bolts and nuts
* Screws
* Battery
* Double-sided adhesive
* Write on tape
* Basic hand tools
* Spiral cable wrap 

## Installing KnowFlow Firmware
KnowFlow is designed for beginners. You don’t need to have experience with Arduino or software development. 
KnowFlow is packaged wtth supporting software libraries to make it easier for you to enable different sensor features 
for your application. Feel free to post your software questions on our wiki page on public lab or github.

1. Download Arduino IDE
1. Download Knowflow code from [github](https://github.com/KnowFlow/KnowFlow_AWM)
1. Open "WaterMonitor.ino" from the downloaded file with Arduino IDE
1. Connect your Arduino Uno board
1. Select Tools>Board: Arduino Uno and Tools>Ports: /dev/cu.usb...
1. Click "Verify" then "Upload" the software to your board.

## FAQ
**Why can't I verify the code.**  
The IDE may be missing a library, most often OneWire. 
Install the missing library library from Sketch->include library->manage libraries. Search "OneWire" then install it.

## FAQ
1. Q:why I can't not verify the code.
A:Some user may not verify the code.
It's maybe the IDE lack of some library, the most possiable is OneWire. 
Please find library OneWire in Sketch->include library->manage libraries, searth OneWire then install it.
It should be solve the problem.


## How to build KnowFlow 
Instructions are available [here.](https://publiclab.org/notes/shanlter/06-08-2017/knowflow-automatic-water-meter)

## How to contribute:
See this [tutorial.](https://help.github.com/articles/creating-a-pull-request/)
1. Fork the repository!
1. Create your feature branch: git checkout -b my-new-feature
1. Commit your changes: git commit -am 'Add some feature'
1. Push to the branch: git push origin my-new-feature
1. Submit a pull request
 
## About Branches
**master** is the current stable release.

**development** is the research version. It has experimental features that are not fully tested. For example, IOT
integrations, new sensors, etc.


**test** is for the team to practice with github. We will delete when we figure out how to use github. (We are newbees
to github, so please forgive any stupid errors. Suggestions are welcome!) :)


## To DO List
- [x] support DO Senser from DFRobot.
- [ ] add youtube video tutorial.
- [ ] Website setup. www.knowflow.org
- [x] Modify the construction of the files system.
- [ ] IOT feature.
- [ ] Calibration function
- [ ] Low power function

## Contact

Email addresses for the KnowFlow team.

* Rockets <Rockets.xia@dfrobot.com>
* He Shan  <shanh0510@gmail.com>
* Lauren <Lauren.pan@hotmail.com>
* Jason <jason.liang@dfrobot.com>



## Documents

 * [Tutorial][1]
 * [GreenSeed online courses][2]
 * [Application:非洲茶园水质调研][3]
 * [Application:Willow Creek Water Quality Monitoring][4]
 * [KnowFlow Special Design][6]

## License

All KnowFlow related materials are released under the [Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)][5]

## This project has benefited from the support from the following funders:

* GreenSeed Foundation
* Mushroom Cloud Maker Space

  [1]: https://publiclab.org/notes/shanlter/06-08-2017/knowflow-automatic-water-meter
  [2]: http://blog.sina.com.cn/s/blog_9f86b6d50102w9m1.html
  [3]: http://www.dfrobot.com.cn/community/thread-26733-1-1.html
  [4]: https://publiclab.org/notes/MadTinker/07-31-2017/willow-creek-water-quality-monitoring
  [5]: https://creativecommons.org/licenses/by-nc-sa/4.0/
  [6]:https://www.instructables.com/id/KnowFlow-Special-Design/
