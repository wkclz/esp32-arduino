#ifndef SpPir_H
#define SpPir_H

#include "Arduino.h"

class SpPir {

  public:
    // 定义 PIR 引脚，最大亮度
    SpPir(int pin, int interval);
    // PIR 循环获取值
    int get();

  private:
    // PIR 引脚
    int _pin; 
    // 读数间隔
    int _interval;

    //当前值
    int current;
    // 上一次状态变更的时间
    unsigned long previousMillis; 

};

#endif