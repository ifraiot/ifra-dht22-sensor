#include "iFraSDK.h"
#include "iFraESP32SDK.h"
#include "DHT.h"
#define WIFI_SSID     "ifrasoft"
#define WIFI_PASSWORD  "@ifrasoft2020"

#define  USERNAME    "9d11c6c4-c711-49b8-87e4-98947072e514"
#define  PASSWORD    "d5d0bfab-4131-4349-9c75-5162117ca8db"
#define  CHANNEL       "d8d74ab3-2689-4343-bf79-78f2b0083fd9"


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
