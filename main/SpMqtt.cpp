#include "Arduino.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "SpMqtt.h"


// 初始化 MQTT
SpMqtt::SpMqtt() {
}

void SpMqtt::init(void (*callBackPtr)(char*, byte*, unsigned int)) {
  espClient.setCACert(ca_cert);
  client = PubSubClient(espClient);
  client.setKeepAlive(120);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callBackPtr);
  Serial.println("MQTT added callback");
}

// 连接/重连 MQTT
void SpMqtt::reconnect() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("wifi is not ready, do not connect to MQTT");
    return;
  }

  if (!client.connected()) {
    uint32_t chipId = base.chipId;

    char mqttClientId[32];
    char mqttPush[32];
    char mqttSubscribe[32];
    sprintf(mqttClientId, "%s%d", mqtt_client_id, chipId);
    sprintf(mqttPush, "%s%d", mqtt_push, chipId);
    sprintf(mqttSubscribe, "%s%d", mqtt_subscribe, chipId);
    Serial.print("mqttClientId: "); Serial.println(mqttClientId);
    Serial.print("mqttPush: "); Serial.println(mqttPush);
    Serial.print("mqttSubscribe: "); Serial.println(mqttSubscribe);

    Serial.print("Attempting MQTT connection...");
    if (client.connect(mqttClientId, mqtt_username, mqtt_password)) {
      Serial.println("connected: 连接成功");
      client.subscribe(mqttSubscribe);
      // 连接成功，推送消息
      StaticJsonDocument<200> doc;
      doc["msg"] = "mqtt connect success!";
      String output;
      serializeJson(doc, output);
      client.publish(mqttPush, output.c_str());
    } else {
      int state = client.state();
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.print(" try again in 0.5 seconds: ");
      if (state == -2) {
        Serial.println("网络异常，将自动重试...");
      }
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
      Serial.println("MQTT connecting retry 5 times, it will be retry after 5 seconds!");
    }
  }
}

// 检查 MQTT 消息
void SpMqtt::checkMsg() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillisMsg >= checkIntervalMsg) {
    if (!client.connected()) {
      // 如果 MQTT 连接失败，每 5s 进行尝试
      if(currentMillis - previousMillisConnect >= checkIntervalConnect) {
        previousMillisConnect = currentMillis;
        reconnect();
      }
      return;
    }
    previousMillisMsg = currentMillis;
    client.loop();
  }

}

