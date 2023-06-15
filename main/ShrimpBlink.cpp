#include "Arduino.h"
#include "ShrimpBlink.h"

ShrimpBlink::ShrimpBlink(int pin, long on, long off) {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);
  onTime = on;
  offTime = off;
  ledState = LOW;
  previousMillis = 0;
}

void ShrimpBlink::update() {
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