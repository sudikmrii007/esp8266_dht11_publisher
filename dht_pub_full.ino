#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "iot-bhupendra";
const char* password =  "iot12345";
const char* mqttServer = "192.168.43.239";
const int mqttPort = 1883;
const char* mqttUser = "mqtt1";
const char* mqttPassword = "mqtt1";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  
 dht.begin();
 delay(2000);
}

void loop() {
    float h = dht.readHumidity();
    float t = dht.readTemperature(); 
    char tempString[8];
    dtostrf(t, 1, 2, tempString);   

    char humidString[8];
    dtostrf(t, 1, 2, humidString); 

    Serial.print("humidity string");
    Serial.print(humidString);
    Serial.println("");
    Serial.print("tempstring string");
    Serial.print(tempString); 
    Serial.println("");
//  if(!client.publish())
//  {
//    Serial.print("cannot publish");
//  }
   client.publish("iot",tempString);
   
   client.publish("iot2",humidString);
//    Serial.print("Current humidity = ");
//    Serial.print(h);
//    Serial.print("%  ");
//    Serial.print("temperature = ");
//    Serial.print(t); 
//    Serial.println("C  ");
    delay(800);
}



 
