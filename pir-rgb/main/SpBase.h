#ifndef SpBase_H
#define SpBase_H

#include "Arduino.h"

class SpBase {

  public:
    // 初始化 base
    SpBase();
    // 打印基础信息
    void print();

    // 芯片ID
    uint32_t chipId = 0;

};

#endif