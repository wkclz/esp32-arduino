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


/*******************************************************************************
* 函 数 名       : step_motor_28BYJ48_send_pulse
* 函数功能       : 输出一个数据给ULN2003从而实现向步进电机发送一个脉冲
* 输    入       : step：指定步进序号，可选值0~7
                  dir：方向选择,1：顺时针,0：逆时针
* 输    出       : 无
*******************************************************************************/
void SpStepMotor::sendPulse(unsigned char step,unsigned char dir) {
  unsigned char temp = step;

  //如果为逆时针旋转
  if(dir == 0) {
    // 调换节拍信号
    temp = 7 - step;
  }

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
    // 停止相序
    default: digitalWrite(ina_pin,0);digitalWrite(inb_pin,0);digitalWrite(inc_pin,0);digitalWrite(ind_pin,0);break;
  }
}
