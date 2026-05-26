# KnowFlow 代码库结构说明

## 项目结构

```
KnowFlow_AWM/
├── ArduinoUnoDo/              # 串口 DO 传感器版本
│   └── WaterMonitor/
│       ├── config.h           # 配置文件（已统一）
│       ├── WaterMonitor.ino   # 主程序
│       └── [传感器驱动文件]
│
├── ArduinoUnoGravityDo/       # Gravity DO 传感器版本（推荐）
│   └── WaterMonitorDo/
│       ├── Config.h           # 配置文件
│       ├── WaterMonitorDo.ino # 主程序
│       └── [传感器驱动文件]
│
└── Firmware/                  # 编译后的固件（参考用）
    └── WaterMonitor/
```

## 代码统一策略

### 1. 配置文件统一
- ✅ 两个版本都使用 `config.h` / `Config.h`
- ✅ 使用枚举值代替硬编码数字
- ✅ 统一的引脚定义和校准参数

### 2. 传感器驱动统一
- ✅ 使用 `GravitySensorHub` 统一管理传感器
- ✅ 使用枚举值 `phSensor`, `temperatureSensor` 等
- ✅ 统一的 `setup()` 和 `update()` 接口

### 3. 主要差异点

#### DO 传感器实现
- **ArduinoUnoDo**: 使用 `SensorDo` 类，通过 Serial 端口通信
- **ArduinoUnoGravityDo**: 使用 `GravityDo` 类，通过模拟引脚 A0

#### EC 传感器实现
- **ArduinoUnoDo**: `GravityEc` 构造函数需要温度传感器指针
- **ArduinoUnoGravityDo**: `GravityEc` 构造函数不需要参数

#### 校准功能
- **ArduinoUnoDo**: 未实现校准功能
- **ArduinoUnoGravityDo**: 支持 pH 和 EC 校准

## 未来统一方向

### 短期目标
1. ✅ 统一配置文件格式
2. ✅ 统一代码风格
3. ✅ 清理注释掉的代码

### 中期目标
1. 统一传感器驱动接口
2. 在所有版本中实现校准功能
3. 创建统一的传感器抽象层

### 长期目标
1. 使用条件编译支持多种硬件配置
2. 创建统一的代码库，通过配置选择硬件版本
3. 支持 ESP32 等新平台

## ESP32 支持考虑

### 需要适配的部分
1. **引脚定义**: ESP32 有更多 GPIO，需要重新映射
2. **ADC**: ESP32 使用 12-bit ADC（vs Arduino 10-bit）
3. **WiFi/Bluetooth**: ESP32 原生支持，可用于 IOT 功能
4. **多核**: 可以利用双核进行传感器数据采集和通信
5. **低功耗**: ESP32 有更好的低功耗模式

### 建议的实现方式
1. 创建 `ArduinoESP32/` 目录
2. 复用现有的传感器驱动类
3. 适配 ESP32 特定的硬件抽象层
4. 利用 ESP32 的 WiFi 功能实现 IOT 数据上传

