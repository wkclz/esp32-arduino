#ifndef SpBase_H
#define SpBase_H

#include "Arduino.h"

class SpBase {

  public:
    // 初始化 base
    SpBase();
    // 打印基础信息
    void print();
    // 同步时间
    void setTime();

    // 芯片ID
    uint32_t chipId = 0;
  private:

    // 时间同步
    const char* ntpServer1 = (char*)"pool.ntp.org";
    const char* ntpServer2 = (char*)"time.nist.gov";
    const long  gmtOffsetSec = 8 * 60 * 60;
    const int   daylightOffsetSec = 0;
    const String timeZone = "CET-1CEST,M3.5.0,M10.5.0/3";

};

#endif