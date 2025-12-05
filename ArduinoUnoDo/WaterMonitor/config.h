#pragma once

// Serial print switch
// Uncomment one of the following to enable debug output
//#define DEBUG_AVR  // For Arduino Uno, Mega2560
//#define DEBUG_M0   // For Arduino M0

// The maximum length of the sensor filter array
#define ARRAYLENGTH 10

// SD card update data time, 60,000 is 1 minute
#define SDUPDATEDATATIME 60000

// EC sensor is selected by default, comment this line to use TDS sensor
#define SELECTEC 

// Sensor pin settings
// DO sensor uses Serial port Rx(0), Tx(1) for ArduinoUnoDo version
#define DOPIN  A0  // Not used in this version (DO uses Serial)
#define ECPIN  A1
#define TDSPIN A1
#define PHPIN  A2
#define ORPPIN A3
#define TEMPPIN 5

// Set sensor offset (calibration data)
// These values can be adjusted based on calibration
#define PHOFFSET 0.0  // pH calibration offset
#define ECKVALUE 1.0  // EC K value for calibration

// The maximum number of sensors
#define SENSORCOUNT 5

// The sensor corresponds to the array number
// ph=0, temperature=1..., the maximum number is SENSORCOUNT-1
enum SensorNumber
{
	phSensor = 0,
	temperatureSensor,
	doSensor,
	ecSensor,
	tdsSensor = 3,
	orpSensor
};
