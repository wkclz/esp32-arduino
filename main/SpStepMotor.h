#ifndef SpStepMotor_H
#define SpStepMotor_H

#include "Arduino.h"

class SpStepMotor {

  public:
    // 初始化电机
    SpStepMotor(int pina, int pinb, int pinc, int pind);

    void setSpeed(int speed);

    /********************************************************************
    * 函 数 名       : sendPulse
    * 函数功能       : 输出一个数据给ULN2003从而实现向步进电机发送一个脉冲
    * 输    入       : step：指定步进序号，可选值0~7
                      dir：方向选择,1：顺时针,0：逆时针
    * 输    出       : 无
    ********************************************************************/
    void sendPulse();

  private:

    // 定义步进电机控制管脚
    int ina_pin; //   15
    int inb_pin; //   2
    int inc_pin; //   0
    int ind_pin; //   4

    // 定义步进电机速度，需要转换为时差，驱动时差才是速度
    int maxSpeed = 100;
    int minSpeed = -10;

    // 当前 step
    int currentStep = 0;

    // 1 正向，0逆向
    int currentDir = 1;

    // 当前速度
    int currentSpeed = 0;

    // 上一次状态变更的时间
    unsigned long previousMillis;

};

#endif