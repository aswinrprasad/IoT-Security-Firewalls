/*
 * Author : Aswin Raghuprasad
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "sdk_structs.h"
#include "ieee80211_structs.h"
#include "string_utils.h"

#define channel 1
#define scanTime 500 //scan time per channel in ms
unsigned long deauth = 0;
#define channelHopping true //scan on all channels
#define maxChannel 13
unsigned long prevTime = 0;
unsigned long curTime = 0;
int curChannel = channel;
#define inverted false

extern "C"
{
  #include "user_interface.h"
}

// According to the SDK documentation, the packet type can be inferred from the
// size of the buffer. We are ignoring this information and parsing the type-subtype
// from the packet header itself. Still, this is here for reference.
wifi_promiscuous_pkt_type_t packet_type_parser(uint16_t len)
{
  	switch(len)
    {
      // If only rx_ctrl is returned, this is an unsupported packet
      case sizeof(wifi_pkt_rx_ctrl_t):
      return WIFI_PKT_MISC;

      // Management packet
      case sizeof(wifi_pkt_mgmt_t):
      return WIFI_PKT_MGMT;

      // Data packet
      default:
      return WIFI_PKT_DATA;
    }
}


  
// In this example, the packet handler function does all the parsing and output work.
// This is NOT ideal.
void wifi_sniffer_packet_handler(uint8_t *buff, uint16_t len)
{
  // First layer: type cast the received buffer into our generic SDK structure
  const wifi_promiscuous_pkt_t *ppkt = (wifi_promiscuous_pkt_t *)buff;
  // Second layer: define pointer to where the actual 802.11 packet is within the structure
  const wifi_ieee80211_packet_t *ipkt = (wifi_ieee80211_packet_t *)ppkt->payload;
  // Third layer: define pointers to the 802.11 packet header and payload
  const wifi_ieee80211_mac_hdr_t *hdr = &ipkt->hdr;
  const uint8_t *data = ipkt->payload;

  // Pointer to the frame control section within the packet header
  const wifi_header_frame_control_t *frame_ctrl = (wifi_header_frame_control_t *)&hdr->frame_ctrl;

  // Parse MAC addresses contained in packet header into human-readable strings
  char addr1[] = "00:00:00:00:00:00\0";
  char addr2[] = "00:00:00:00:00:00\0";
  char addr3[] = "00:00:00:00:00:00\0";

  mac2str(hdr->addr1, addr1);
  mac2str(hdr->addr2, addr2);
  mac2str(hdr->addr3, addr3);
  
  // Output info to serial
  

  // Print ESSID if beacon
  if (frame_ctrl->type == WIFI_PKT_MGMT && frame_ctrl->subtype == DEAUTHENTICATION)
  {
    //deauth = 200;
    char ssid[32] = {0};
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(2, LOW);
    Serial.printf("\n%s | %s | %u | %-28s |",
    addr1,
    addr2,
    wifi_get_channel(),
    //frame_ctrl->type,
    //frame_ctrl->subtype,
    wifi_pkt_type2str((wifi_promiscuous_pkt_type_t)frame_ctrl->type, (wifi_mgmt_subtypes_t)frame_ctrl->subtype));
    
  }
  else{
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(2, HIGH);
  }
}


void setup()
{
  // Serial setup
  Serial.begin(115200);
  delay(10);
  wifi_set_channel(2);

  //Detector LED
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
  
  // Wifi setup
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1);
  WiFi.disconnect();

  // Set sniffer callback
  wifi_set_promiscuous_rx_cb(wifi_sniffer_packet_handler);
  wifi_promiscuous_enable(1);

  // Print header
  Serial.printf("\n\n    MAC RECIEVER 1|       MAC SENDER 2| Ch|           Frame type         |");
  Serial.printf("\n------------------------------------------------------------------------------");
  

}

void loop()
{
 if(channelHopping){
      curChannel++;
      if(curChannel > maxChannel) curChannel = 1;
      wifi_set_channel(curChannel);
   } 
 delay(10);
}
