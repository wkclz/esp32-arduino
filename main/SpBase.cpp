#include "Arduino.h"
#include "SpBase.h"

#include <time.h>
#include <sntp.h>

// 初始化 base
SpBase::SpBase() {
  uint64_t mac = ESP.getEfuseMac();
  for(int i=0; i<17; i=i+8) {
    chipId |= ((mac >> (40 - i)) & 0xff) << i;
  }
}

// 打印基础信息
void SpBase::print() {
  Serial.println();
  Serial.print("芯片ID: "); Serial.println(chipId);
  Serial.printf("Mac地址: %012X \n", ESP.getEfuseMac());
  Serial.printf("芯片型号: %s\n", ESP.getChipModel());
  Serial.printf("芯片版本号: %d\n", ESP.getChipRevision());
  Serial.printf("芯片核心数: %d\n", ESP.getChipCores());
  Serial.printf("芯片时钟频率: %u MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("自上电以来时钟走过的周期数: %u\n", ESP.getCycleCount());
  Serial.printf("SDK版本号: %u\n", ESP.getSdkVersion());
  Serial.println();

  //Internal RAM
  Serial.printf("总堆大小: %u Byte\n", ESP.getHeapSize());
  Serial.printf("可用堆大小: %u Byte\n", ESP.getFreeHeap());
  Serial.printf("启动以来最小可用堆大小: %u Byte\n", ESP.getMinFreeHeap());
  Serial.printf("可以一次分配的最大堆大小: %u Byte\n", ESP.getMaxAllocHeap());
  Serial.println();

  //SPI RAM
  Serial.printf("SPI 总堆大小: %u Byte\n", ESP.getPsramSize());
  Serial.printf("SPI 可用堆大小: %u Byte\n", ESP.getFreePsram());
  Serial.printf("SPI 启动以来最小可用堆大小: %u Byte\n", ESP.getMinFreePsram());
  Serial.printf("SPI 可以一次分配的最大堆大小: %u Byte\n", ESP.getMaxAllocPsram());
  Serial.println();

  Serial.printf("Flash大小: %u Byte\n", ESP.getFlashChipSize());
  Serial.printf("Flash运行速度: %u\n", ESP.getFlashChipSpeed());
  Serial.printf("Flash工作模式: %u\n", ESP.getFlashChipMode());
  Serial.printf("Flash大小: %u Byte\n", ESP.getFlashChipSize());
  Serial.println();

  Serial.printf("固件大小: %u Byte\n", ESP.getSketchSize());
  Serial.printf("固件MD5: %u\n", ESP.getSketchMD5());
  Serial.printf("固件区域剩余大小: %u Byte\n", ESP.getFreeSketchSpace());
  Serial.println();
}

// Callback function (get's called when time adjusts via NTP)
void timeavailable(struct timeval *t) {
  Serial.println("Got time adjustment from NTP!");
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)) {
    Serial.println("No time available (yet)");
    return;
  }
  Serial.println(&timeinfo, "%Y-%m-%d %H:%M:%S");
}

void SpBase::syncTime() {
  sntp_set_time_sync_notification_cb(timeavailable);
  sntp_servermode_dhcp(1);
  configTime(gmtOffsetSec, daylightOffsetSec, ntpServer1, ntpServer2);
}
