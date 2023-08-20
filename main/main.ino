#include "SpBase.h"
#include "SpWifi.h"
#include "SpLed.h"
#include "SpMqtt.h"
#include "SpServo.h"

SpBase base;
SpWifi wifi;
SpLed led1(15, 100, 100);
SpLed led2(2, 1000, 1000);
SpMqtt mqtt;
SpServo servo(17,8,50,8);

void setup() {
  Serial.begin(115200);
  while(!Serial){delay(100);}
  Serial.println("esp32 starting & setup.....");

  // 打印基础信息
  // base.print();
  // 连接 WIFI
  wifi.connect();
  mqtt.init(callback);
  Serial.println("esp32 setuped, will looping...");
}

void loop() {
  // 检查 WIFI 连接情况
  wifi.checkAndConnect();
  led1.update();
  led2.update();
  mqtt.checkMsg();
  // servo.update(12);
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  String payloadStr = String((char*)payload, length);
  Serial.print(payloadStr);
  /*
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  */
  Serial.println();
}