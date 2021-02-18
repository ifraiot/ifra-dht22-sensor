# IfraSDK
1. ติดตั้ง SDK
  ดาวน์โหลดไฟล์ https://github.com/ifraiot/ifra-cpp-sdk/archive/master.zip
  และแตกไฟล์วางในโฟลเดอร์ Arduino/libraries

2. ตัวอย่างโค้ดสำหรับ ESP32 เป็นการ Random ค่า 1 - 100 ส่งไปยัง Platform 

*อย่าลืมสร้าง sensor ชื่อ temp ใน measurement
```cpp

#include "iFraSDK.h"
#include "iFraESP32SDK.h"

#define WIFI_SSID      "<ชื่อ WIFI>"
#define WIFI_PASSWORD  "<รหัสผ่าน WIFI>"

#define  USERNAME    "218c2b41-970b-4354-946b-1f6138c218ad"
#define  PASSWORD    "91fd563b-c384-41ea-8101-83699b79ea2b"
#define  CHANNEL       "17f2b49e-a2c7-47d0-9421-a51627f21d14"

iFraESP32SDK esp32(WIFI_SSID, WIFI_PASSWORD);
iFraSDK client(&esp32, CHANNEL, USERNAME, CHANNEL);

void setup() {
  Serial.begin(115200);  
  client.wifiConnection();
}

void loop() {
  client.addSensor("temp","c",random(1,100));
  client.send();
  delay(2000);
}

```