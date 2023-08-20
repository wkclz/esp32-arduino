# esp32-arduino


## arduino 环境搭建
- http://doc.wkclz.com/other/arduino/


## SpBase

### print 打印ESP32基本信息

> 在系统启动时输出一次

- 芯片信息
- 内存信息
- SPI信息
- Flash 信息
- 固件信息

### syncTime 同步时间

> WIFI 连接成功后执行一次 

- 从 ntp 同步时间


## SpWifi


### 连接

> 若 WIFI 未连接，将进行一次连接，若连接失败，将 0.5s 尝试一次，最多10次


### 检查连接状态

> 若未连接，将发起连接. 非阻塞定制


## SpLed

### SpLed(int pin, long on, long off)

> 初始化 LED, 定义输出口，开启时长，关闭时长

### update

> 更新 LED 状态，若时钟到来，将会触发状态翻转


### SpMqtt


## SpMqtt

### 