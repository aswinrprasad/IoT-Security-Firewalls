/*
 * Author : Aswin Raghuprasad
 * NB : Still in testing phase
 */

#include <ESP8266WiFi.h>

const char* ssid = "DopeDevice";

const char* password = "aswin123456";

// Access point Ip Address……
IPAddress local_IP(192,168,4,22);

IPAddress gateway(192,168,4,9);

IPAddress subnet(255,255,255,0);

/////Client Ip Address……

IPAddress staticIP(192,168,1,32);

IPAddress gateway2(192,168,1,9);

IPAddress subnet2(255,255,255,0);

void setup()

{

Serial.begin(115200);

Serial.println();
WiFi.mode(WIFI_AP_STA);

Serial.print("Setting soft-AP configuration … ");

Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

Serial.print("Setting soft-AP … ");

Serial.println(WiFi.softAP("ESPsoftAP_01") ? "Ready" : "Failed!");

Serial.print("Soft-AP IP address = ");

Serial.println(WiFi.softAPIP());

/////////////////////////////////////////

Serial.println();

Serial.printf("Connecting to %s\n", ssid);

WiFi.begin(ssid, password);

WiFi.config(staticIP, gateway2, subnet2);

while (WiFi.status() != WL_CONNECTED)

{

delay(500);

Serial.print(".");

}

Serial.println();

Serial.print("Connected, IP address — Client Ip: ");

Serial.println(WiFi.localIP());
}

void loop() {}
