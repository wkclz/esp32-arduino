#include "Arduino.h"
#include "SpRgb.h"

// 初始化 RGB
SpRgb::SpRgb(int pin, int interval, int delay) {
  _pin = pin;
  _interval = interval;
  _delay = delay;
  pinMode(_pin, OUTPUT);

  level = 0;
  current = 1;
  wait = 0;
  previousMillis = 0;
}

// 改变亮度
void SpRgb::update(int lightSw) {
  if (lightSw == 1) {
    if (level != 255) {
      level = 255;
      // 灯亮，重置等待时间
      wait = _delay;
      Serial.print("rgb on ");
      Serial.println(wait);
    }
  }

  if (lightSw == 0) {
    level = 0;
    if (level != 0) {
      Serial.println("rgb off ...");
    }
  }

  // 更新 RGB 状态

  // 每循环一次，经 wait 减值
  if (wait > 0) {
    wait = wait - _interval;
  }

  // 未到下个周期，下述逻辑不处理
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis < _interval) {
    return;
  }
  previousMillis = currentMillis;

  // 开灯
  if(current < level) {
    current = current + 1;
    neopixelWrite(_pin, current, current, current);
  }
  
  // 关灯
  if (current > level && wait <= 0) {
    current = current - 1;
    neopixelWrite(_pin, current, current, current);
  }
}
