#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "******"; // Enter your WiFi name
const char* password =  "******"; // Enter WiFi password
#define ORG "z7oat3"
#define DEVICE_TYPE "nodemcu"
#define DEVICE_ID "dev01"
#define TOKEN "WuUwWl)clq74*VS-+8"
const char* mqttServer =ORG".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/evt/status/fmt/json";
const int mqttPort = 1883;
const char* mqttUser = "otfxknod";
const char* mqttPassword = "nSuUc1dDLygF";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;
WiFiClient wifiClient;
void callback(char* topic, byte* payload, unsigned int length) {
 Serial.println("callback invoked");
}
PubSubClient client(mqttServer, 1883, callback, wifiClient);
void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
 Serial.println();
 
 Serial.print("Connecting to ");
 Serial.print(ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 } 
 Serial.println("");
 
 Serial.print("WiFi connected, IP address: ");
 Serial.println(WiFi.localIP());

}
void loop() {
  // put your main code here, to run repeatedly:
   if (!client.connected()) {
 Serial.print("Reconnecting client to ");
 Serial.println(mqttServer);
 while (!client.connect(clientId, authMethod, token)) {
 Serial.print(".");
 delay(500);
 }
 Serial.println();
 }
 int sensorValue = analogRead(A0);
 String payload = "{d:{s:"+String(sensorValue)+"}}";  
 Serial.print("Sending payload: ");
 Serial.println(payload);
 if (client.publish(topic, (char*) payload.c_str())) {
 Serial.println("Publish ok");
 } else {
 Serial.println("Publish failed");
 }
 delay(10000);
 }
 
