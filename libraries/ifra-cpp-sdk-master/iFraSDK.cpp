#include "iFraSDK.h"
 
DynamicJsonDocument _doc(_capacity);
 
iFraSDK::iFraSDK(){
        
}
iFraSDK::iFraSDK(HardWarePlatform* hardWarePlatform, char* channel, char* username, char* password)  {

    //Assign to global valuable.
    this->hardWarePlatform_ = hardWarePlatform;
    this->channel_ = channel;
    this->username_ = username;
    this->password_ = password;
    
    //Get client from strategy sdk
    this->client_ = this->hardWarePlatform_->GetClient(); 

    //Set Client to MQTT client 
    this->mqtt_client_.setClient(*this->client_);

    //Setup server and port number.
    this->mqtt_client_.setServer(IFRA_SERVER, MQTT_PORT);

}

iFraSDK::iFraSDK(HardWarePlatform* hardWarePlatform  ,char* channel, char* username, char* password, char* server){
    this->channel_ = channel;
    this->username_ = username;
    this->password_ = password;
    this->hardWarePlatform_ = hardWarePlatform;
    this->server_ = server;
        //Get client from strategy sdk
    this->client_ = this->hardWarePlatform_->GetClient(); 

    //Set Client to MQTT client 
    this->mqtt_client_.setClient(*this->client_);

    //Setup server and port number.
    this->mqtt_client_.setServer(this->server_, MQTT_PORT);
}

void iFraSDK::addSensor(char * sensor_name, char * unit, float value){
       JsonObject doc = _doc.createNestedObject();
       doc["n"] = sensor_name;
       doc["u"] = unit;
       doc["v"] = value;
      _recordCount++;
}

void iFraSDK::addActuator(void (*callbackFunc)(char * actuator_name, int * value , char * topic, byte * payload, unsigned int length)){
        this->mqtt_client_.setCallback([this,callbackFunc](char * topic, byte * payload, unsigned int length) {
                
                const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(3) + 30;
                DynamicJsonDocument doc(capacity);
                deserializeJson(doc, payload);
                JsonObject root_0 = doc[0];
                const char* actuator_name_ = root_0["n"]; // "Name"
                const char* root_0_u = root_0["u"]; // "Unit"
                int  value_ = root_0["v"]; // Value
                callbackFunc(( char*)actuator_name_,&value_, topic, payload, length);
       });

}

void iFraSDK::addActuator(void (*callbackFunc)(char * actuator_name, float * value , char * topic, byte * payload, unsigned int length)){
       this->mqtt_client_.setCallback([this,callbackFunc](char * topic, byte * payload, unsigned int length) {
                
                const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(3) + 30;
                DynamicJsonDocument doc(capacity);
                deserializeJson(doc, payload);
                JsonObject root_0 = doc[0];
                const char* actuator_name_ = root_0["n"]; // "Name"
                const char* root_0_u = root_0["u"]; // "Unit"
                float  value_ = root_0["v"]; // Value
                callbackFunc(( char*)actuator_name_,&value_, topic, payload, length);
       });
 
}

void iFraSDK::addEventActuator(char * actuator_name, int actuator_value , void (*callbackFunc)(char * actuator_name, float * value)){
        this->mqtt_client_.setCallback([this,actuator_name,actuator_value,callbackFunc](char * topic, byte * payload, unsigned int length) {
                
                const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(3) + 30;
                DynamicJsonDocument doc(capacity);
                deserializeJson(doc, payload);

                JsonObject root_0 = doc[0];
                const char* actuator_name_ = root_0["n"]; // "Name"
                const char* root_0_u = root_0["u"]; // "Unit"
                long  value_ = root_0["v"]; // Value
                if (*actuator_name_ == *actuator_name && value_ == (long) actuator_value) {
                        Serial.print("callback:");
                        Serial.println(actuator_name_);
                        callbackFunc(( char*)actuator_name_, (float*)value_);
                }
               
       });
}

void iFraSDK::send() {
      if (this->mqtt_client_.connected()) {
                String channel(this->channel_);
                String topic = "organization/"+channel+"/messages";
                
                char message[4096];
                serializeJson(_doc, message);
                this->mqtt_client_.publish(topic.c_str(), message);
                this->mqtt_client_.loop();
                Serial.println(message);
        }else{
          this->reconnect();
        }
        

        _doc.clear();
        _recordCount = 0;
}

void iFraSDK::wifiConnection(){

      this->hardWarePlatform_->Connect();

      while (!this->mqtt_client_.connected()) {
            reconnect();  
      }

    
}
 bool iFraSDK::connected(){
         this->mqtt_client_.loop();
         return this->mqtt_client_.connected();
 }

 void iFraSDK::reconnect(){

   Serial.println("Trying connect IFRA MQTT...");     

   if (this->mqtt_client_.connect(this->username_, this->username_, this->password_)) {
            Serial.println("connected ^_^");
            String channel(this->channel_);
            String topic = "organization/"+ channel +"/messages/actuator";
            this->mqtt_client_.subscribe(topic.c_str());
   } else {
            Serial.print("failed, rc=");
            Serial.print(this->mqtt_client_.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
       }

 }




