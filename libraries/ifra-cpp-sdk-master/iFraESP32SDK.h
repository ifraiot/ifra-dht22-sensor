 
#ifndef HARDWAREPLATFORM_H
#define HARDWAREPLATFORM_H

#include "HardWarePlatform.h"

#endif // HARDWAREPLATFORM_H
#include <PubSubClient.h>
#include <WiFi.h>

class iFraESP32SDK : public HardWarePlatform
{
   public:
        char* ssid_;
        char* password_;
        WiFiClient client_;
        iFraESP32SDK(char* ssid, char* password);
        void Connect() override;
        Client* GetClient() override;
  
};


 