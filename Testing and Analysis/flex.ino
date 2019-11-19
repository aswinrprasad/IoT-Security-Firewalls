
#include <ESP8266WiFi.h>
 
String apiKey = "401RDNI2N6QT1YNR";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "DopeDevice";     // replace with your wifi ssid and wpa2 key
const char *pass =  "aswin123456";
const char* server = "api.thingspeak.com";

IPAddress local_IP(192,168,4,22);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

//Constants:
static const uint8_t ledPin   = 0;  //pin D3 has PWM funtion
const int flexPin = A0; //pin A0 to read analog input

//Variables:
int value; //save analog value

WiFiClient client;
 
void setup() 
{
  pinMode(ledPin, OUTPUT);  //Set pin 3 as 'output'
  Serial.begin(115200);
  delay(10);
  Serial.println("\n\nConnecting to ");
  Serial.println(ssid);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP("NODEMCU");
  WiFi.begin(ssid, pass);
 
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}
 
void loop() 
{
  value = analogRead(flexPin);
  value = map(value, 0, 1023, 0, 255);//Map value 0-1023 to 0-255 (PWM)
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
}
