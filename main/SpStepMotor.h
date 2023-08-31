#ifndef SpStepMotor_H
#define SpStepMotor_H

#include "Arduino.h"

class SpStepMotor {

  public:
    // 初始化电机
    SpStepMotor(char pina, char pinb, char pinc, char pind);
    // 设置速度
    void setSpeed(int speed);
    // 发送消息
    void sendPulse();

  private:

    // 定义步进电机控制管脚
    char ina_pin; //   15
    char inb_pin; //   2
    char inc_pin; //   0
    char ind_pin; //   4

    // 定义步进电机速度，需要转换为时差，驱动时差才是速度
    int maxSpeed = 100;
    int minSpeed = -10;

    // 1正向，0逆向
    int currentDir = 1;
    // 当前速度
    int currentSpeed = 0;
    // 当前 step
    unsigned char currentStep = 0;

    // 上一次状态变更的时间
    unsigned long previousMillis;

};

#endif