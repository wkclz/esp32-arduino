#ifndef SpWifi_H
#define SpWifi_H

#include "Arduino.h"

class SpWifi {

  public:
    // 初始化 base
    SpWifi();
    // 连接 WIFI
    void connect();
    // 检查连接状态，若未连接，将尝试连接
    void checkAndConnect();

  private:
    unsigned long previousMillis = 0;
    unsigned long checkInterval = 60000;
    String ssid     = "my_ssid";
    String password = "my_password";

};

#endif