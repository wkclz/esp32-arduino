#include "Arduino.h"
#include "SpLed.h"

// 初始化 LED
SpLed::SpLed(int pin, long on, long off) {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);
  onTime = on;
  offTime = off;
  ledState = LOW;
  previousMillis = 0;
}

// 更新 LED 状态
void SpLed::update() {
  unsigned long currentMillis = millis();
  if(ledState == HIGH && (currentMillis - previousMillis >= onTime)) {
    ledState = LOW;
    previousMillis = currentMillis;
    digitalWrite(ledPin, ledState);
  } else if (ledState == LOW && (currentMillis - previousMillis >= offTime)) {
    ledState = HIGH;
    previousMillis = currentMillis;
    digitalWrite(ledPin, ledState);
  }
}