/*
 * Author : Aswin Raghuprasad
 * Reference : Roboindia.com
 */

#include <DHT.h>  // Including library for dht

#include <ESP8266WiFi.h>
#include "ChangeMac.hpp"
 
String apiKey = "4VMADMVD8WTB0SLB";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "ROGUE";     // replace with your wifi ssid and wpa2 key
const char *pass =  "12345678";
const char* server = "api.thingspeak.com";

IPAddress local_IP(192,168,4,22);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

#define DHTPIN 5          //pin where the dht11 is connected
 
DHT dht(DHTPIN, DHT11);
int cnt=0;
int mx = 5;
int f=0;
WiFiClient client;
 
void setup() 
{
  Serial.begin(115200);
  delay(10);
  dht.begin();
  Serial.println();
  Serial.println();
  
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}


void loop() 
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (isnan(h) || isnan(t)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
        
  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
  {  
                            
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(t);
    postStr +="&field2=";
    postStr += String(h);
    postStr += "\r\n\r\n";
 
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
 
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" degrees Celcius, Humidity: ");
    Serial.print(h);
    Serial.println("%. Send to Thingspeak.");
  }
  client.stop();
 
  Serial.println("Waiting...");
  cnt++;
  if(cnt==mx){
    uint8_t mac[6];
    makeRandomMac(mac);
    bool res = changeMac(mac);
    Serial.print("MAC address is ");
    //Serial.println(res);
    Serial.println(WiFi.macAddress());
    WiFi.begin(ssid, pass);
    cnt=0;
  }
  delay(10000);
}
