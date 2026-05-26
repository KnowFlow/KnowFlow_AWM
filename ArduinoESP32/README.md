# KnowFlow ESP32 版本

这是 KnowFlow 水质监测系统的 ESP32 移植版本，支持 ESP32 开发板运行原有的 5 个传感器（pH, Temperature, DO, EC, ORP）。

## 特性

- ✅ 支持所有 5 个传感器（pH, Temperature, DO, EC, ORP）
- ✅ 利用 ESP32 的 12-bit ADC 获得更高精度
- ✅ 兼容现有的传感器驱动代码
- ✅ 支持 SD 卡数据存储
- ✅ 支持 RTC 时间记录
- 🔜 WiFi 数据上传（计划中）
- 🔜 蓝牙配置（计划中）

## 硬件要求

### 开发板
- ESP32 开发板（推荐 ESP32-DevKitC）
- 支持 Arduino IDE 的 ESP32 开发环境

### 传感器
- pH 传感器（DFRobot Gravity pH Sensor）
- EC 传感器（DFRobot Gravity EC Sensor）
- ORP 传感器（DFRobot Gravity ORP Sensor）
- DO 传感器（DFRobot Gravity DO Sensor）
- 温度传感器（DS18B20）

### 其他
- Micro SD 卡模块（SPI 接口）
- RTC 模块（I2C 接口，可选，可使用 NTP）

## 引脚配置

### 传感器引脚（ESP32 GPIO）
- **pH**: GPIO34 (ADC1_CH6)
- **EC**: GPIO35 (ADC1_CH7)
- **ORP**: GPIO32 (ADC1_CH4)
- **DO**: GPIO33 (ADC1_CH5)
- **Temperature**: GPIO4 (OneWire)

### SD 卡引脚（SPI）
- **MOSI**: GPIO23
- **MISO**: GPIO19
- **CLK**: GPIO18
- **CS**: GPIO5

### I2C 引脚（RTC）
- **SDA**: GPIO21
- **SCL**: GPIO22

## 安装步骤

### 1. 安装 Arduino IDE 和 ESP32 支持

1. 下载并安装 [Arduino IDE](https://www.arduino.cc/en/software)（1.8.13 或更高版本）

2. 添加 ESP32 开发板支持：
   - 打开 Arduino IDE
   - 文件 → 首选项
   - 在"附加开发板管理器网址"中添加：
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - 工具 → 开发板 → 开发板管理器
   - 搜索 "ESP32" 并安装

### 2. 安装必要的库

从 `Firmware/libraries/` 目录复制以下库到 Arduino IDE 的 libraries 文件夹：
- OneWire
- Wire（ESP32 已内置，但可能需要）

或者通过库管理器安装：
- OneWire（搜索 "OneWire"）

### 3. 配置项目

1. 打开 `WaterMonitorESP32.ino`
2. 编辑 `Config.h` 调整以下配置：
   - 传感器校准值（`PHOFFSET`, `ECKVALUE`）
   - 调试输出（`DEBUG_ESP32`）
   - 引脚配置（如果需要修改）

### 4. 上传代码

1. 连接 ESP32 开发板到电脑
2. 选择开发板：工具 → 开发板 → ESP32 Arduino → ESP32 Dev Module
3. 选择端口：工具 → 端口 → （你的 ESP32 端口）
4. 点击"上传"

## ADC 精度说明

ESP32 使用 12-bit ADC（0-4095），比 Arduino 的 10-bit ADC（0-1023）精度更高。代码中包含了适配层，可以将 ESP32 的 ADC 值转换为 Arduino 兼容的值，同时也可以直接使用 ESP32 的更高精度。

### 使用 Arduino 兼容模式（默认）
传感器驱动会自动将 ESP32 的 12-bit 值转换为 10-bit 值，保持与 Arduino 版本的兼容性。

### 使用 ESP32 高精度模式
如果需要更高的精度，可以修改传感器驱动代码，直接使用 ESP32 的 12-bit ADC 值。

## 电压兼容性

### 传感器输出
- DFRobot Gravity 传感器通常输出 0-3.3V 信号，兼容 ESP32 的 3.3V 逻辑电平
- 传感器模块可能需要 5V 供电，但输出信号是 3.3V 兼容的

### 注意事项
- 如果传感器需要 5V 供电，确保 ESP32 开发板有 5V 输出引脚，或使用外部 5V 电源
- 不要将 5V 信号直接连接到 ESP32 GPIO（会损坏芯片）
- 如果传感器输出超过 3.3V，需要使用电平转换电路

## 故障排除

### 问题：编译错误
- 确保已安装 ESP32 开发板支持
- 确保所有必要的库都已安装
- 检查 Arduino IDE 版本（需要 1.8.13+）

### 问题：传感器读数不准确
- 检查引脚配置是否正确
- 检查传感器供电是否正常
- 检查 ADC 配置（`initESP32ADC()` 函数）
- 可能需要重新校准传感器

### 问题：SD 卡无法识别
- 检查 SPI 引脚连接
- 检查 SD 卡格式（建议使用 FAT32）
- 检查 CS 引脚配置

## 未来计划

- [ ] WiFi 数据上传功能
- [ ] 蓝牙配置功能
- [ ] NTP 时间同步
- [ ] OTA 固件更新
- [ ] Web 配置界面
- [ ] 低功耗模式

## 贡献

欢迎提交 Issue 和 Pull Request！

## 许可证

与主项目相同：GNU General Public License v3.0

