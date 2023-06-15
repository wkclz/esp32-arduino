#include "SpBase.h"
#include "SpLed.h"

SpBase base;
SpLed led1(15, 100, 100);
SpLed led2(2, 1000, 1000);

void setup() {
  Serial.begin(115200);
  while(!Serial){delay(100);}

  // 打印基础信息
  base.print();
}

void loop() {
  led1.update();
  led2.update();
}
