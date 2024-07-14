#ifndef SpRgb_H
#define SpRgb_H

#include "Arduino.h"

class SpRgb {

  public:
    // 定义 RGB 引脚，最大亮度
    SpRgb(int pin, int interval, int delay);
    // 更新 RGB 状态
    void update(int lightSw);

  private:
    // RGB 引脚
    int _pin; 
    // 检测频率
    int _interval;
    // 延迟时间
    int _delay;

    // BUILTIN 亮度
    int level;
    // 当前 BUILTIN 亮度
    int current;
    // 等待时长
    int wait;
    // 上一次状态变更的时间
    unsigned long previousMillis; 

};

#endif