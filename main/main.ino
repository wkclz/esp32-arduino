#include "SpBase.h"
#include "SpWifi.h"
#include "SpLed.h"

SpBase base;
SpWifi wifi;
SpLed led1(15, 100, 100);
SpLed led2(2, 1000, 1000);

void setup() {
  Serial.begin(115200);
  while(!Serial){delay(100);}

  // 打印基础信息
  base.print();
  // 连接 WIFI
  wifi.connect();
}

void loop() {
  // 检查 WIFI 连接情况
  wifi.checkAndConnect();
  led1.update();
  led2.update();
}
