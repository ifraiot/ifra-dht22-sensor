#ifndef HARDWAREPLATFORM_H
#define HARDWAREPLATFORM_H

#include "HardWarePlatform.h"

#endif // HARDWAREPLATFORM_H
#include <ArduinoJson.h>
#include "Client.h"
#include "Stream.h"
#include <WiFi.h>
#include <PubSubClient.h>
 
 

// for convenience
// using json = nlohmann::json;

#ifndef IFRA_SERVER
#define IFRA_SERVER "mqtt.ifra.io"
#endif

#ifndef NTP_SERVER
#define NTP_SERVER "asia.pool.ntp.org"
#endif

#ifndef MQTT_PORT
#define MQTT_PORT 1883
#endif

#define ON 1
#define OFF 0


const size_t _capacity = JSON_ARRAY_SIZE(500) + JSON_OBJECT_SIZE(10);

class iFraSDK
{
private:
    HardWarePlatform* hardWarePlatform_;
    char* channel_;
    char* username_;
    char* password_;
    char* server_;
    char* _base_name;
    char* _base_unit;
    int _recordCount;
    unsigned long int _base_time;
    Client *client_;
    PubSubClient mqtt_client_;
    

public:
    iFraSDK();
    iFraSDK(HardWarePlatform* hardWarePlatform, char* channel, char* username, char* password);
    iFraSDK(HardWarePlatform* hardWarePlatform  ,char* channel, char* username, char* password, char* server) ;
    void addSensor(char * sensor_name, char * unit, float value);
    void addActuator(void (*callbackFunc)(char * actuator_name, int   * value , char * topic, byte * payload, unsigned int length)); //int
    void addActuator(void (*callbackFunc)(char * actuator_name, float * value , char * topic, byte * payload, unsigned int length)); //float
    void addEventActuator(char * actuator_name, int value , void (*callbackFunc)(char* actuator_name, float* value));
    void send();
    void wifiConnection();
    bool connected();
    void reconnect();
};
