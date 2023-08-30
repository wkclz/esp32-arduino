#include "Arduino.h"
#include "SpServo.h"


// 舵机控制
// degree：角度0-180
// 返回值：输出对应角度PWM占空比
int servo_ctrl(unsigned char degree) {
  // 对应0.5ms(0.5/(20ms/256))
  const float deadZone = 6.4;
  // 对应2.5ms
  const float max = 32;
  if (degree < 0) { degree = 0; }
  if (degree > 180) { degree = 180; }
  return (int)(((max-deadZone)/180)*degree+deadZone);
}

void pwm_set_duty(unsigned char chanel, unsigned int duty) {
  // 改变PWM的占空比
  ledcWrite(chanel,duty);
}

// 初始化 PWM
SpServo::SpServo(unsigned char pin,unsigned char chanel,unsigned char freq,unsigned char resolution) {

  Serial.println("init servo start.....");
  sPin = pin;
  sChanel = chanel;
  sFreq = freq;
  sResolution = resolution;
  previousMillis = 0;
  // PWM初始化
  ledcSetup(chanel, freq, resolution);
  // 绑定PWM通道到GPIO上
  ledcAttachPin(pin, chanel);
  // 初始化位置
  pwm_set_duty(sChanel, servo_ctrl(init_degree));
  Serial.println("init servo end.....");
}

// 更新位置
void SpServo::update(unsigned char degree) {
  unsigned long currentMillis = millis();
  if((currentMillis - previousMillis < checkInterval)) {
    return;
  }
  previousMillis = currentMillis;
  Serial.print("servo update to: ");
  Serial.println(degree);
  pwm_set_duty(sChanel, servo_ctrl(degree));
}