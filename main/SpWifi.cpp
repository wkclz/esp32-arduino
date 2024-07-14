#include "Arduino.h"
#include "SpWifi.h"

#include <WiFi.h>

// 初始化 wifi
SpWifi::SpWifi() {
}

// 连接 WIFI
void SpWifi::connect() {
  Serial.println();
  Serial.println("******************************************************");
  Serial.print("Connecting to ");
  Serial.println(config.ssid);

  WiFi.begin(config.ssid, config.password);
  int times = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    times ++;
    if (times > 10) {
      Serial.println();
      Serial.println("WiFi connecting for 5 seconds, it will be retry after 1 minute!");
      return;
    }
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // 初次连接成功 WIFI, 网络对时
  if (firstConnect) {
    firstConnect = false;
    base.syncTime();
  }
}


// 检查并连接 WIFI
void SpWifi::checkAndConnect() {
  unsigned long currentMillis = millis();
  if((currentMillis - previousMillis < interval)) {
    return;
  }
  previousMillis = currentMillis;

  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("wifi is not connected --->");
    connect();
  }
}

