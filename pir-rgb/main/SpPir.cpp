#include "Arduino.h"
#include "SpPir.h"

// 初始化 PIR
SpPir::SpPir(int pin, int interval) {
  _pin = pin;
  _interval = interval;
  pinMode(_pin, INPUT);

  current = 0;
  previousMillis = 0;
}

// 更新 PIR 状态
int SpPir::get() {
  unsigned long currentMillis = millis();
  if((currentMillis - previousMillis >= _interval)) {
    current = digitalRead(_pin);
    Serial.print("PIR value: ");
    Serial.println(current);
    previousMillis = currentMillis;
  }
  return current;
}
