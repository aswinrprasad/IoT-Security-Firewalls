/*
 * Author : Aswin Raghuprasad
 * References : Nullbyte
 */

#include <ESP8266WiFi.h>
#include "Mac.h"

IPAddress local_IP(192,168,4,22);

IPAddress gateway(192,168,4,9);

IPAddress subnet(255,255,255,0);

extern "C" {
  #include "user_interface.h"
}

//===== SETTINGS =====//
#define channel 1 //the channel it should scan on (1-14)
#define channelHopping true //scan on all channels
#define maxChannel 13 //US = 11, EU = 13, Japan = 14
#define ledPin 2 //led pin ( 2 = built-in LED)
#define inverted false // invert HIGH/LOW for the LED
#define packetRate 3 //min. packets before it gets recognized as an attack

#define scanTime 500 //scan time per channel in ms

unsigned long deauth = 0;
unsigned long dissoc = 0;
unsigned long prevTime = 0;
unsigned long curTime = 0;
int curChannel = channel;
const char* ssid     = "NodeMCU";
const char* password = "123456789";


void sniffer(uint8_t *buf, uint16_t len) {

Mac m;
if(buf[12] == 0xA0){

      dissoc = 200;
    }
if(buf[12] == 0xC0){
      deauth = 200;
      m.Mac::_println();
    }
else{
      if (deauth >= 1){
      deauth--;}
      if (dissoc >= 1){
      dissoc--;}
    }

  //}
}

void setup() {
  
  Serial.begin(115200);
  //WiFi.mode(WIFI_AP_STA);
  //WiFi.softAPConfig(local_IP, gateway, subnet);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(0);
  WiFi.disconnect();
  wifi_set_promiscuous_rx_cb(sniffer);
  wifi_set_channel(1);
  wifi_promiscuous_enable(1);
  WiFi.softAP(ssid, password);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
  
  Serial.println("starting!");

}

void loop() {
  curTime = millis();

  if(curTime - prevTime >= scanTime){
    prevTime = curTime;
    //Serial.println((String)c);

    if(deauth >= 1){
      //Serial.println("Deauth attack!");
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(2, LOW);
    }
    else{
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(2, HIGH);
    }
    if(dissoc >= 1){
      Serial.println("Dissoc attack!");
    }
    if(channelHopping){
      curChannel++;
      if(curChannel > maxChannel) curChannel = 1;
      wifi_set_channel(curChannel);
    }
  }

}
