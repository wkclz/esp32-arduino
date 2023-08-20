#ifndef SpServo_H
#define SpServo_H

#include "Arduino.h"

class SpServo {

  public:
    // 舵机(PWM) 初始化
    // pin：引脚号
    // chanel：PWM输出通道0-15，0-7高速通道，由80M时钟驱动，8-15低速通道，有1M时钟驱动
    // freq：PWM输出频率，单位HZ
    // resolution：PWM占空比的分辨率1-16，比如设置8，分辨率范围0-255
    SpServo(unsigned char pin,unsigned char chanel,unsigned char freq,unsigned char resolution);
    // 更新 LED 状态
    void update(unsigned char degree);

  private:
    // pin：引脚号
    unsigned char sPin;
    // PWM输出通道0-15，0-7高速通道，由80M时钟驱动，8-15低速通道，有1M时钟驱动
    unsigned char sChanel;
    // PWM输出频率，单位HZ
    unsigned char sFreq;
    // PWM占空比的分辨率1-16，比如设置8，分辨率范围0-255
    unsigned char sResolution;
    // 初始化时角度
    unsigned int init_degree = 90;;


    // 上一次状态变更的时间
    unsigned long previousMillis;
    // 检查周期
    unsigned long checkInterval = 2000;
};

#endif