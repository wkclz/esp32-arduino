#include "Arduino.h"
#include <PubSubClient.h>
#include "SpMqtt.h"



// 初始化 MQTT
SpMqtt::SpMqtt() {
  espClient.setCACert(ca_cert);
  client = PubSubClient(espClient);
  client.setKeepAlive(120);
  client.setServer(mqtt_server, mqtt_port);
  // client.setCallback(callback);
}

void SpMqtt::addCallback(void (*callBackPtr)(char*, byte*, unsigned int)) {
  client.setCallback(callBackPtr);
  Serial.println("MQTT added callback");
}


// 连接/重连 MQTT
void SpMqtt::reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(mqtt_client_id, mqtt_username, mqtt_password)) {
      Serial.println("connected: 连接成功");
      client.subscribe(mqtt_subscribe);
      // 连接成功，推送消息
      client.publish(mqtt_push, "reconnected: mqtt connect success!");
    } else {
      int state = client.state();
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.print(" try again in 5 seconds: ");
      if (state == 1) {
        Serial.println("拒绝连接, 服务器不支持该客户端请求的 MQTT 协议");
      }
      if (state == 2) {
        Serial.println("拒绝连接, 客户端 ID 是正确的 UTF-8 字符串，但是不被服务器允许, 或者心跳时间间隔不满足平台要求");
      }
      if (state == 3) {
        Serial.println("拒绝连接, 网络连接已经建立，但是 MQTT 服务不可用");
      }
      if (state == 4) {
        Serial.println("拒绝连接, 在用户名或密码中的数据是错误格式的");
      }
      if (state == 5) {
        Serial.println("拒绝连接, 客户端的连接未被授权");
      }
      delay(5000);
    }
  }
}

// 检查 MQTT 消息
void SpMqtt::checkMsg() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= checkInterval) {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
  }

}

