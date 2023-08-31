#include "Arduino.h"
#include "SpStepMotor.h"

// 初始化电机
SpStepMotor::SpStepMotor(char pina, char pinb, char pinc, char pind) {
  ina_pin = pina;
  inb_pin = pinb;
  inc_pin = pinc;
  ind_pin = pind;
  // 设置引脚为输出模式
  pinMode(ina_pin, OUTPUT);
  pinMode(inb_pin, OUTPUT);
  pinMode(inc_pin, OUTPUT);
  pinMode(ind_pin, OUTPUT);
}

void SpStepMotor::setSpeed(int speed) {
  if (speed < -10) {
    speed = -10;
  }
  if (speed > 100) {
    speed = 100;
  }
  // 小于 0 时为逆向
  if (speed < 0) {
    currentSpeed = 0 - speed;
    currentDir = 0;
  }
  if (speed >= 0) {
    currentSpeed = speed;
    currentDir = 1;
  }

  Serial.print("currentDir --> ");
  Serial.print(currentDir);
  Serial.print("currentSpeed --> ");
  Serial.print(currentSpeed);
  Serial.println("");
}

void SpStepMotor::sendPulse() {

  unsigned long currentMillis = millis();
  unsigned long checkInterval = 101 - currentSpeed;
  if((currentMillis - previousMillis < checkInterval)) {
    return;
  }
  previousMillis = currentMillis;
  // 速度为0， 检查周期大于 100， 不转动
  if (checkInterval > maxSpeed) {
    return;
  }

  // 位置变动
  currentStep = currentStep + 1;
  if (currentStep == 8) {
    currentStep = 0;
  }

  unsigned char temp = currentStep;
  // 逆向
  if (currentDir == 0) {
    temp = 7 - temp;
  }

  Serial.print("setp --> ");
  Serial.print(temp);
  Serial.println("");

  // 8个节拍控制：A->AB->B->BC->C->CD->D->DA
  switch(temp) {
    case 0: digitalWrite(ina_pin,1);digitalWrite(inb_pin,0);digitalWrite(inc_pin,0);digitalWrite(ind_pin,0);break;
    case 1: digitalWrite(ina_pin,1);digitalWrite(inb_pin,1);digitalWrite(inc_pin,0);digitalWrite(ind_pin,0);break;
    case 2: digitalWrite(ina_pin,0);digitalWrite(inb_pin,1);digitalWrite(inc_pin,0);digitalWrite(ind_pin,0);break;
    case 3: digitalWrite(ina_pin,0);digitalWrite(inb_pin,1);digitalWrite(inc_pin,1);digitalWrite(ind_pin,0);break;
    case 4: digitalWrite(ina_pin,0);digitalWrite(inb_pin,0);digitalWrite(inc_pin,1);digitalWrite(ind_pin,0);break;
    case 5: digitalWrite(ina_pin,0);digitalWrite(inb_pin,0);digitalWrite(inc_pin,1);digitalWrite(ind_pin,1);break;
    case 6: digitalWrite(ina_pin,0);digitalWrite(inb_pin,0);digitalWrite(inc_pin,0);digitalWrite(ind_pin,1);break;
    case 7: digitalWrite(ina_pin,1);digitalWrite(inb_pin,0);digitalWrite(inc_pin,0);digitalWrite(ind_pin,1);break;
    default: digitalWrite(ina_pin,0);digitalWrite(inb_pin,0);digitalWrite(inc_pin,0);digitalWrite(ind_pin,0);break;//停止相序 
  }
}
