#include "iFraSDK.h"
#include "iFraESP32SDK.h"
#include "DHT.h"
#define WIFI_SSID     "<ชื่อ WIFI>"
#define WIFI_PASSWORD  "<รหัสผ่าน WIFI>"

#define  USERNAME    "<Username API KEY>"
#define  PASSWORD    "<Password API KEY>"
#define  CHANNEL     "<Channel API KEY>"


#define DHTPIN 2 
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);

iFraESP32SDK esp32(WIFI_SSID, WIFI_PASSWORD);
iFraSDK client(&esp32, CHANNEL, USERNAME, PASSWORD);

void setup() {
  Serial.begin(115200);  
  client.wifiConnection();
 dht.begin();
}

void loop() {
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();

if (isnan(h) || isnan(t))  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }


  client.addSensor("DHT22_1","c",t);
  client.addSensor("DHT22_2","h",h);
  client.send();
  delay(3600);
}
