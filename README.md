

# KnowFlow - an open source river quality meter with Arduino

KnowFlow is an open source water monitoring device and an education program.

********************************************************************************
CAUTION: THE BASELINE VERSION IS IN THE LIST


![](https://publiclab.org/system/images/photos/000/020/692/large/BOM.JPG)

For the device part, KnowFlow is designed for environmental activists, researchers, students... anyone who wants to know the water quality using low cost and customized tools. It is based on arduino uno, currently can monitor 5 parameters: Temperature, pH, ORP, Electronic conductivities, Dissolved Oxygen, the data is stored on a micro SD card, or read directly on phone by bluetooth (except for Dissolved Oxygen). All the modules are easy to change or add. Most of the sensor used are from DFRobot and Atlas Scientific, which are the main 2 sensor suppliers for Arduino users.

![](https://publiclab.org/system/images/photos/000/020/719/large/Lauren_Field_Test.jpg)

For the education program, KnowFlow is a 8 weeks online course and a learning group (launched on Greenseed Project platform). In which we will introduce the basic knowledge about water quality and indicators of water quality, Arduino and monitoring system, and show you how to build your own online monitor system based on arduino. Use Arduino as a master controller, and connected it to a variety of sensors. Except for the 5 parameters which are already included in the KnowFlow kits, you can add other environmental sensors on, such as carbon dioxide, ozone, dust, light, temperature, humidity sensors. Then use GPS and other communication module to connect all the data from distance. There will be step by step demos in the course to walk you through this learning process.


***************How to Run The Baseline Model***************

* Download Arduino IDE
* 下载 Arduino IDE
* Download Knowflow code
* 打包下载 KnowFlow 代码
* find "WaterMonitor.ino" from the downloaded file, open it with Arduino IDE
* 解压并在⽂件夹中找到 WaterMonitor.ino, 在 Arduino IDE 中打开
* Connect your Arduino Uno board, in menus, select "Tools - Board: Arduino Uno", and "Ports - /dev/cu.usb..."
*将 Arduino 和电脑连接，菜单中，⼯具-开发板 选择“Arduino Uno”，端⼝选择类似“/dev/
cu.usb....”
* click "Verify", than "Upload" the software to your board.
*点击验证（对勾），然后再点击上传（右箭头），程序被烧录进 Arduino 主板中。

Appendix: un-comment the whole serial debugging part to show the parameters in the serial monitor



***************************************
This page is a collective information 
