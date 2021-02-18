#include "iFraESP32SDK.h"
 
iFraESP32SDK::iFraESP32SDK(char* ssid, char* password){
    this->ssid_=ssid;
    this->password_=password;
}


void iFraESP32SDK::Connect() {
    
        WiFi.begin(this->ssid_, this->password_);
        Serial.print("Start connect wifi");
        while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                Serial.print(".");
        }
        WiFi.setAutoReconnect(true);
        Serial.println(F("WiFi connected"));
        Serial.println(F("IP address: "));
        Serial.println(WiFi.localIP());
 
       
}

Client* iFraESP32SDK::GetClient(){
    return &this->client_;
}
 