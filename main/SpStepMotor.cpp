#include "Arduino.h"
#include "SpStepMotor.h"

// 初始化电机
SpStepMotor::SpStepMotor(int pina, int pinb, int pinc, int pind) {

  ina_pin = pina;
  inb_pin = pinb;
  inc_pin = pinc;
  ind_pin = pind;

  // previousMillis = 0;
}


SpStepMotor::setSpeed(int speed) {
  if (speed < -10) {
    speed = -10;
  }
  if (speed > 1000) {
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
}


/*******************************************************************************
* 函 数 名       : step_motor_28BYJ48_send_pulse
* 函数功能       : 输出一个数据给ULN2003从而实现向步进电机发送一个脉冲
* 输    入       : step：指定步进序号，可选值0~7
                  dir：方向选择,1：顺时针,0：逆时针
* 输    出       : 无
*******************************************************************************/
void SpStepMotor::sendPulse() {

  unsigned long currentMillis = millis();
  unsigned long checkInterval = 100 - currentSpeed;
  if((currentMillis - previousMillis < checkInterval)) {
    return;
  }
  previousMillis = currentMillis;
  // 速度为0， 不转动
  if (checkInterval >= maxSpeed) {
    return;
  }

  // 正向
  if (currentDir == 1) {
    currentStep = currentStep + 1;
    if (currentStep == 8) {
      currentStep == 0;
    }
  }
  // 逆向
  if (currentDir == 0) {
    currentStep = currentStep - 1;
    if (currentStep == -1) {
      currentStep == 7;
    }
  }

  // 8个节拍控制：A->AB->B->BC->C->CD->D->DA
  switch(currentStep) {
    case 0: digitalWrite(ina_pin,1);digitalWrite(inb_pin,0);digitalWrite(inc_pin,0);digitalWrite(ind_pin,0);break;
    case 1: digitalWrite(ina_pin,1);digitalWrite(inb_pin,1);digitalWrite(inc_pin,0);digitalWrite(ind_pin,0);break;
    case 2: digitalWrite(ina_pin,0);digitalWrite(inb_pin,1);digitalWrite(inc_pin,0);digitalWrite(ind_pin,0);break;
    case 3: digitalWrite(ina_pin,0);digitalWrite(inb_pin,1);digitalWrite(inc_pin,1);digitalWrite(ind_pin,0);break;
    case 4: digitalWrite(ina_pin,0);digitalWrite(inb_pin,0);digitalWrite(inc_pin,1);digitalWrite(ind_pin,0);break;
    case 5: digitalWrite(ina_pin,0);digitalWrite(inb_pin,0);digitalWrite(inc_pin,1);digitalWrite(ind_pin,1);break;
    case 6: digitalWrite(ina_pin,0);digitalWrite(inb_pin,0);digitalWrite(inc_pin,0);digitalWrite(ind_pin,1);break;
    case 7: digitalWrite(ina_pin,1);digitalWrite(inb_pin,0);digitalWrite(inc_pin,0);digitalWrite(ind_pin,1);break;
    // 停止相序
    default: digitalWrite(ina_pin,0);digitalWrite(inb_pin,0);digitalWrite(inc_pin,0);digitalWrite(ind_pin,0);break;
  }
}
