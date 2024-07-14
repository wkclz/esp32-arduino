#include "SpBase.h"
#include "SpPir.h"
#include "SpRgb.h"

SpBase base;
// PIR (pin, interval)
SpPir pir(26, 1000);
// RGB (ping, interval, wait)
SpRgb rgb(16, 20, 60000);

void setup() {
  Serial.begin(115200);
  while(!Serial){delay(100);}
  Serial.println("esp32 starting & setup.....");

  // 打印基础信息
  base.print();

  Serial.println("esp32 setuped, will looping...");
}

void loop() {
  // delay 保证 watchdog 能正常工作
  delay(10);
  // 获取 PIR 状态值
  int lightSw = pir.get();
  // 更新 RGB 状态
  rgb.update(lightSw);
}
