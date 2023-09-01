#include <ArduinoJson.h>
#include "SpBase.h"
#include "SpWifi.h"
#include "SpLed.h"
#include "SpMqtt.h"
#include "SpServo.h"
#include "SpStepMotor.h"

SpBase base;
SpWifi wifi;
// pin, on, off
SpLed led1(18, 100, 100);
// pin, on, off
SpLed led2(19, 1000, 1000);
SpMqtt mqtt;
// pin, chanel,freq,resolution
SpServo servo(17, 8, 50, 8);
// pina, pinb, pinc, pind
SpStepMotor stepMotor(15, 12, 0, 4);

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
  // 初始化位置
  servo.update(0);
}

void loop() {
  // 检查 WIFI 连接情况
  wifi.checkAndConnect();
  led1.update();
  led2.update();
  mqtt.checkMsg();
  stepMotor.sendPulse();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  String payloadStr = String((char*)payload, length);
  Serial.print(payloadStr);

  DynamicJsonDocument data(1024);
  deserializeJson(data, payloadStr);

  String op = data["op"];
  if (op == "servo") {
    long degree = data[String("degree")];
    Serial.print("servo --> ");
    Serial.print(degree);
    servo.update(degree);
  } else if (op == "stepMotor") {
    long speed = data[String("speed")];
    Serial.print("speed --> ");
    Serial.print(speed);
    stepMotor.setSpeed(speed);
  } else {
    // 无法识别时，发送错误消息
    Serial.print("unknown op: ");
    Serial.print(op);
    Serial.print("  ");

    StaticJsonDocument<200> doc;
    doc["msg"] = "unknown op!";
    mqtt.sendMsg(doc);
  }

  /*
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  */
  Serial.println();
}