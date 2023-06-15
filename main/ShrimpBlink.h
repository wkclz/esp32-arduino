#include "Arduino.h"

class ShrimpBlink {

  public:
    // 定义 LED 引脚，on 时长, off 时长
    ShrimpBlink(int pin, long on, long off);
    // 更新 Blink 状态
    void update();

  private:
    // LED 引脚
    int ledPin; 
    // on 时长
    long onTime; 
    // off 时长
    long offTime;
    // 当前 LED 状态
    int ledState;
    // 上一次状态变更的时间
    unsigned long previousMillis; 

};