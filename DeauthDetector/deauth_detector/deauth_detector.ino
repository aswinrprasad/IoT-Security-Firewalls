#include <ESP8266WiFi.h>
#include "Mac.h"

extern "C" {
  #include "user_interface.h"
}


//===== FELX SENSOR SETTINGS =====//

String apiKey = "401RDNI2N6QT1YNR";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "KitKat";     // replace with your wifi ssid and wpa2 key
const char *pass =  "kittykat";
const char* server = "api.thingspeak.com";


//Constants:
static const uint8_t ledPin   = 0;  //pin D3 has PWM funtion
const int flexPin = A0; //pin A0 to read analog input

//Variables:
int value; //save analog value
WiFiClient client;

//===== SETTINGS =====//
#define channel 1 //the channel it should scan on (1-14)
#define channelHopping true //scan on all channels
#define maxChannel 13 //US = 11, EU = 13, Japan = 14
#define packetRate 3 //min. packets before it gets recognized as an attack

#define scanTime 500 //scan time per channel in ms

unsigned long deauth = 0;
unsigned long dissoc = 0;
unsigned long prevTime = 0;
unsigned long curTime = 0;
int curChannel = channel;

void sniffer(uint8_t *buf, uint16_t len) {

if(buf[12] == 0xA0){

      dissoc = 500;
    }
        if(buf[12] == 0xC0){

      deauth = 500;
    }
    else{
      if (deauth >= 1){
      deauth--;}
      if (dissoc >= 1){
      dissoc--;}
    }

  //}
}
void  art(){
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(0);
  WiFi.disconnect();
  wifi_set_promiscuous_rx_cb(sniffer);
  wifi_set_channel(curChannel);
  wifi_promiscuous_enable(1);
  Serial.println("starting!");
}

void check(){
  curTime = millis();
  
  if(curTime - prevTime >= scanTime){
    prevTime = curTime;
    //Serial.println((String)c);

    if(deauth >= 1){
      Serial.println("Deauth ATTACK !!");
    }
    if(dissoc >= 1){
      Serial.println("Dissoc ATTACK!!");
    }
  }
}
void setup() {
  Serial.begin(115200);

  
  pinMode(ledPin, OUTPUT);  //Set pin 3 as 'output'
  delay(10);
  Serial.println("\n\nConnecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
 
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}


void loop() {
  value = analogRead(flexPin);
  value = map(value, 0, 1023, 0, 255);//Map value 0-1023 to 0-255 (PWM)
  Serial.print(value);
  if (isnan(value)) {
    Serial.println("Failed to read from sensor!");
    return;
  }
  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
  {                           
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(value);
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
    Serial.print("Flex Value: ");
    Serial.print(value);
    Serial.println("%. Send to Thingspeak.");    
  }
  client.stop();
  analogWrite(ledPin, value);          //Send PWM value to led
  delay(100); 
  Serial.println("Waiting...");
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(10000);
  art();
  check();
}
