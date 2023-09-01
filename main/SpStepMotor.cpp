#include "Arduino.h"
#include "SpStepMotor.h"

// 初始化电机
SpStepMotor::SpStepMotor(char pina, char pinb, char pinc, char pind) {
  pa = pina;
  pb = pinb;
  pc = pinc;
  pd = pind;
  // 设置引脚为输出模式
  pinMode(pa, OUTPUT);
  pinMode(pb, OUTPUT);
  pinMode(pc, OUTPUT);
  pinMode(pd, OUTPUT);
}

void SpStepMotor::setSpeed(int speed) {
  if (speed < -10) {
    speed = -10;
  }
  if (speed > 10) {
    speed = 10;
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
  unsigned long checkInterval = 11 - currentSpeed;
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
    case 0: digitalWrite(pa,1);digitalWrite(pb,0);digitalWrite(pc,0);digitalWrite(pd,0);break;
    case 1: digitalWrite(pa,1);digitalWrite(pb,1);digitalWrite(pc,0);digitalWrite(pd,0);break;
    case 2: digitalWrite(pa,0);digitalWrite(pb,1);digitalWrite(pc,0);digitalWrite(pd,0);break;
    case 3: digitalWrite(pa,0);digitalWrite(pb,1);digitalWrite(pc,1);digitalWrite(pd,0);break;
    case 4: digitalWrite(pa,0);digitalWrite(pb,0);digitalWrite(pc,1);digitalWrite(pd,0);break;
    case 5: digitalWrite(pa,0);digitalWrite(pb,0);digitalWrite(pc,1);digitalWrite(pd,1);break;
    case 6: digitalWrite(pa,0);digitalWrite(pb,0);digitalWrite(pc,0);digitalWrite(pd,1);break;
    case 7: digitalWrite(pa,1);digitalWrite(pb,0);digitalWrite(pc,0);digitalWrite(pd,1);break;
    default: digitalWrite(pa,0);digitalWrite(pb,0);digitalWrite(pc,0);digitalWrite(pd,0);break;//停止相序
  }
}
