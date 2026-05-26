# ESP32 支持方案

## 需求确认

### 功能范围
- ✅ **支持现有 5 个传感器**：pH, Temperature, DO, EC, ORP
- ⚠️ **WiFi 数据上传**：待确认（建议实现，ESP32 的优势）
- ⚠️ **蓝牙功能**：待确认（ESP32 原生支持，可用于配置）

### 硬件兼容性分析

#### 传感器电压兼容性
根据 DFRobot Gravity 传感器规格：
- **pH/EC/ORP 传感器**：通常使用 5V 供电，但输出信号为 0-3.3V（兼容 ESP32）
- **DO 传感器**：Gravity DO 传感器输出 0-3.3V（兼容 ESP32）
- **温度传感器**：DS18B20 支持 3.3V 工作电压

**结论**：大部分传感器兼容 3.3V，但可能需要：
- 5V 转 3.3V 电平转换（如果传感器需要 5V 供电）
- 或者使用 5V 供电的 ESP32 开发板（如 ESP32-DevKitC）

#### ADC 差异
- **Arduino Uno**: 10-bit ADC (0-1023), 参考电压 5V
- **ESP32**: 12-bit ADC (0-4095), 参考电压 3.3V
- **需要适配**：ADC 读取值的转换和校准

### 实现优先级建议

**阶段 1：基本传感器功能**（优先）
1. 创建 ESP32 项目结构
2. 适配传感器驱动（ADC 转换）
3. 实现基本的数据采集和 SD 卡存储
4. 测试所有 5 个传感器

**阶段 2：WiFi/IOT 功能**（后续）
1. 实现 WiFi 连接
2. 实现数据上传到服务器
3. 实现 OTA 更新
4. 实现 Web 配置界面

**阶段 3：蓝牙功能**（可选）
1. 实现蓝牙配置
2. 实现蓝牙数据读取

## 技术方案

### 1. 项目结构
```
ArduinoESP32/
└── WaterMonitorESP32/
    ├── Config.h              # ESP32 特定配置
    ├── WaterMonitorESP32.ino
    ├── [传感器驱动文件]      # 复用现有驱动，适配 ESP32
    └── WiFiService.h/cpp     # WiFi 功能（阶段 2）
```

### 2. 关键适配点

#### ADC 适配
- ESP32 ADC 读取值需要转换：`value_arduino = (value_esp32 * 1023) / 4095`
- 或者直接使用 ESP32 的 12-bit 精度（更精确）

#### 引脚映射
- ESP32 有更多 GPIO，可以灵活配置
- 建议使用 ADC1 通道（GPIO32-39）

#### 多核利用
- Core 0: WiFi/蓝牙任务
- Core 1: 传感器采集和数据处理

### 3. 配置建议

#### 引脚配置（ESP32）
```cpp
// ESP32 GPIO pins (建议使用)
#define PHPIN  34    // ADC1_CH6
#define ECPIN  35    // ADC1_CH7
#define ORPPIN  32   // ADC1_CH4
#define DOPIN   33   // ADC1_CH5
#define TEMPPIN  4   // GPIO4 (OneWire)
```

#### WiFi 配置（阶段 2）
```cpp
#define WIFI_SSID "YourSSID"
#define WIFI_PASSWORD "YourPassword"
#define SERVER_URL "http://your-server.com/api/data"
```

## 实施步骤

### Step 1: 创建基础结构
1. 创建 `ArduinoESP32/WaterMonitorESP32/` 目录
2. 复制 `ArduinoUnoGravityDo` 的代码作为基础
3. 创建 ESP32 特定的 `Config.h`

### Step 2: 适配传感器驱动
1. 修改 ADC 读取函数适配 ESP32
2. 更新引脚定义
3. 测试每个传感器

### Step 3: 实现基本功能
1. 实现传感器数据采集
2. 实现 SD 卡存储（ESP32 可能需要 SPIFFS 或 LittleFS）
3. 实现 RTC（ESP32 可以使用 NTP 或硬件 RTC）

### Step 4: WiFi 功能（后续）
1. 实现 WiFi 连接
2. 实现 HTTP POST 数据上传
3. 实现配置界面

## 风险评估

### 低风险
- ✅ 传感器驱动适配（代码复用度高）
- ✅ 基本功能实现（ESP32 Arduino 框架兼容）

### 中风险
- ⚠️ ADC 精度和校准（需要测试）
- ⚠️ SD 卡兼容性（ESP32 可能需要不同的库）

### 高风险
- ⚠️ 5V 传感器供电（可能需要电平转换电路）
- ⚠️ WiFi 稳定性（需要处理断线重连）

## 下一步行动

1. **立即开始**：创建 ESP32 项目结构和基础代码
2. **测试验证**：先实现基本传感器功能，验证硬件兼容性
3. **逐步扩展**：在基本功能稳定后，添加 WiFi/IOT 功能

