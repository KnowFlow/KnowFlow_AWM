#pragma once

// Serial print switch
// Uncomment one of the following to enable debug output
//#define DEBUG_AVR  // For Arduino Uno, Mega2560
//#define DEBUG_M0   // For Arduino M0

// WiFi Configuration
#define WIFI_SSID "YourWiFiNetwork"
#define WIFI_PASSWORD "YourWiFiPassword"
#define MQTT_SERVER "your.mqtt.server.com"
#define MQTT_PORT 1883
#define MQTT_TOPIC "knowflow/data"
#define MQTT_CLIENT_ID "KnowFlowDevice"

// Power Management Configuration
#define POWER_SLEEP_INTERVAL 60000  // milliseconds (1 minute)
#define LOW_BATTERY_THRESHOLD 3.3   // Volts
#define CRITICAL_BATTERY_THRESHOLD 3.0  // Volts
#define ENABLE_BATTERY_MONITORING true
#define ENABLE_SENSOR_POWER_CONTROL true
#define ENABLE_SOLAR_CHARGING false

// Calibration Configuration
#define CALIBRATION_EEPROM_ADDR 0
#define ENABLE_AUTO_CALIBRATION true
#define CALIBRATION_STABILITY_TIME 10000  // milliseconds
#define PHOFFSET 0.0  // pH calibration offset
#define ECKVALUE 1.0  // EC K value for calibration

// The maximum length of the sensor filter array
#define ARRAYLENGTH 10

// SD card update data time, 60,000 is 1 minute
#define SDUPDATEDATATIME 60000

// EC sensor is selected by default, comment this line to use TDS sensor
#define SELECTEC

// Sensor pin settings
// DO sensor uses Serial port Rx(0), Tx(1) for ArduinoUnoDo version
#if defined(ARDUINO_ARCH_ESP32)
#define ECPIN 34
#define PHPIN 35
#define ORPPIN 32
#define DOPIN 33
#define BATTERY_MONITOR_PIN 36
#else
#define DOPIN A0  // Not used in this version (DO uses Serial)
#define ECPIN A1
#define PHPIN A2
#define ORPPIN A3
#define BATTERY_MONITOR_PIN A7
#endif
#define TDSPIN ECPIN
#define TEMPPIN 5
#define RTC_SDA A4
#define RTC_SCL A5

// Compatibility aliases used by the enhanced WaterMonitor services.
#define EC_PIN ECPIN
#define PH_PIN PHPIN
#define ORP_PIN ORPPIN
#define DO_PIN DOPIN
#define TEMP_PIN TEMPPIN

// DFRobot Gravity DFR0553 I2C ADS1115 16-bit ADC
#define ENABLE_DFR0553_ADC true
#define DFR0553_I2C_ADDRESS 0x48
#define DFR0553_FULL_SCALE_MV 6144.0f
#define DFR0553_EC_CHANNEL 0
#define DFR0553_PH_CHANNEL 1
#define DFR0553_ORP_CHANNEL 2
#define DFR0553_AUX_CHANNEL 3

// Power Control Pins
#define SENSOR_POWER_PIN 8
#define SOLAR_CHARGE_PIN 9

// SD Card Configuration
#define SD_CS_PIN 4
#define ENABLE_SD_LOGGING true

// Debug Configuration
#define ENABLE_DEBUG true
#define DEBUG_BAUD_RATE 9600

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
