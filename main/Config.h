#ifndef Config_H
#define Config_H

#include "Arduino.h"

class Config {

  public:

    String ssid     = "own";
    String password = "Shrimp123";

    const char* mqtt_server = "example.emqxsl.cn";
    const int mqtt_port = 8883;
    const char* mqtt_username = "xxxx";
    const char* mqtt_password = "xxxx";
};

#endif