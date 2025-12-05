

This branch is for ongoing development


# KnowFlow - an open source river quality meter with Arduino

KnowFlow is an open source water monitoring device and an education program.

![](https://publiclab.org/system/images/photos/000/020/692/large/BOM.JPG)



For the device part, KnowFlow is designed for environmental activists, researchers, students... anyone
who wants to know the water quality using low cost and customized tools. It is based on Arduino Uno and 
can currently monitor 5 parameters: Temperature, pH, ORP, Electrical conductivity and Dissolved Oxygen. 
The data is stored on a micro SD card and can be read directly on phone by bluetooth (except for Dissolved Oxygen). 
All the modules are easy to change or add. Most of the sensors used are from DFRobot and Atlas Scientific, 
the main 2 sensor suppliers for Arduino users.

### Supported Hardware Platforms
- **Arduino Uno** (primary platform)
- **Arduino Mega 2560**
- **Arduino M0**
- **ESP32** ✅ (see [ESP32 README](ArduinoESP32/README.md))

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
KnowFlow is designed for beginners. You don't need to have experience with Arduino or software development. 
KnowFlow is packaged with supporting software libraries to make it easier for you to enable different sensor features 
for your application. Feel free to post your software questions on our wiki page on public lab or github.

### Firmware Versions

This repository contains multiple firmware versions for different hardware configurations:

#### 1. ArduinoUnoDo
- **Location**: `ArduinoUnoDo/WaterMonitor/`
- **DO Sensor**: Uses Serial port communication (Rx(0), Tx(1))
- **Best for**: Atlas Scientific DO sensor or similar serial-based DO sensors
- **Note**: DO sensor uses Serial port, which may conflict with USB debugging

#### 2. ArduinoUnoGravityDo
- **Location**: `ArduinoUnoGravityDo/WaterMonitorDo/`
- **DO Sensor**: Uses analog pin A0 (Gravity DO sensor)
- **Best for**: DFRobot Gravity DO sensor
- **Features**: Includes calibration support for pH and EC sensors
- **Recommended**: This is the most feature-complete version

#### 3. ArduinoESP32
- **Location**: `ArduinoESP32/WaterMonitorESP32/`
- **DO Sensor**: Uses analog pin GPIO33 (Gravity DO sensor)
- **Best for**: ESP32 development boards
- **Features**: 
  - Uses ESP32's 12-bit ADC for higher precision
  - Compatible with all 5 sensors
  - Ready for WiFi/IOT features (planned)
- **Note**: Requires ESP32 board support in Arduino IDE

#### 4. Firmware (Legacy)
- **Location**: `Firmware/WaterMonitor/WaterMonitor/`
- **Status**: Legacy version, contains compiled binaries
- **Note**: Use for reference only

### Installation Steps

1. **Download Arduino IDE** (version 1.8.2 or later)
   - Download link: https://www.arduino.cc/en/Main/Software

2. **Download KnowFlow code**
   ```bash
   git clone https://github.com/KnowFlow/KnowFlow_AWM.git
   ```

3. **Choose the appropriate firmware version**
   - For **ESP32**: Use `ArduinoESP32/WaterMonitorESP32/` (see [ESP32 README](ArduinoESP32/README.md))
   - For **Gravity DO sensor** (Arduino Uno): Use `ArduinoUnoGravityDo/WaterMonitorDo/`
   - For **Serial DO sensor** (Arduino Uno): Use `ArduinoUnoDo/WaterMonitor/`

4. **Install required libraries**
   - Copy libraries from `Firmware/libraries/` to your Arduino IDE libraries folder
   - Or install OneWire library via Library Manager: Sketch → Include Library → Manage Libraries → Search "OneWire"

5. **Configure your hardware**
   - Edit `config.h` (or `Config.h`) to match your sensor pins and calibration values
   - Enable/disable debug output by uncommenting `DEBUG_AVR` or `DEBUG_M0`

6. **Upload to board**
   - Open `WaterMonitor.ino` (or `WaterMonitorDo.ino`) in Arduino IDE
   - Connect your Arduino Uno board
   - Select Tools → Board: Arduino Uno
   - Select Tools → Port: (your USB port)
   - Click "Verify" then "Upload"

## FAQ

### Q: Why can't I verify the code?
**A:** The IDE may be missing a library, most often OneWire. 
Install the missing library from Sketch → Include Library → Manage Libraries. Search "OneWire" then install it.

### Q: Which firmware version should I use?
**A:** 
- Use **ArduinoUnoGravityDo** if you have DFRobot Gravity DO sensor (recommended)
- Use **ArduinoUnoDo** if you have Atlas Scientific or other serial-based DO sensors
- Check your DO sensor documentation to determine which type you have

### Q: How do I calibrate the sensors?
**A:** 
- Edit `config.h` (or `Config.h`) in your firmware directory
- Set `PHOFFSET` for pH calibration offset
- Set `ECKVALUE` for EC sensor K value
- Re-upload the firmware after calibration

### Q: Can I use both Serial DO and Gravity DO?
**A:** No, you need to choose one firmware version based on your hardware. The two versions are incompatible due to different DO sensor interfaces.

### Q: How do I enable debug output?
**A:** 
- Open `config.h` (or `Config.h`)
- Uncomment `#define DEBUG_AVR` for Arduino Uno/Mega
- Or uncomment `#define DEBUG_M0` for Arduino M0
- Re-upload the firmware


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
- [x] Support DO Sensor from DFRobot
- [x] Modify the construction of the files system
- [x] Code cleanup and configuration unification
- [ ] Add YouTube video tutorial
- [ ] Website setup (www.knowflow.org)
- [ ] IOT feature
- [x] Calibration function (partially implemented in ArduinoUnoGravityDo)
- [x] ESP32 support (basic sensor functionality)
- [ ] ESP32 WiFi/IOT features
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
