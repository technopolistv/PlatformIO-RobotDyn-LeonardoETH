/*

  https://www.technopolis.tv/blog/2023/05/22/PlatformIO-How-to-use-RobotDyn-Arduino-Leonard-Ethernet-W5500/

*/ 

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#define CS 4    // SD CS
#define SS 10   // W5500 CS
#define RST 11  // W5500 RST

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1];
unsigned int localPort = 8888;

IPAddress ip(192, 168, 23, 23);
EthernetUDP udp;

void setup() {
  // pinMode(SS, OUTPUT);
  pinMode(RST, OUTPUT);

  // digitalWrite(SS, LOW);
  digitalWrite(RST, HIGH);

  Serial.begin(9600);
  // while (!Serial) {
  //   ;  // wait for serial port to connect. Needed for Leonardo only
  // }

  Ethernet.begin(mac, ip);
  // digitalWrite(SS, HIGH);

  udp.begin(localPort);
}

void loop() {
  int packetSize = udp.parsePacket();

  if (packetSize) {
    if(packetSize > UDP_TX_PACKET_MAX_SIZE) {
      memset(packetBuffer, 0, UDP_TX_PACKET_MAX_SIZE); 
      Serial.println("Received packet too large!");
      return;
    }

    Serial.print("Received packet of size ");
    Serial.print(packetSize);
    Serial.print(" From ");
    
    IPAddress remote = udp.remoteIP();
    for (int i = 0; i < 4; i++) {
      Serial.print(remote[i], DEC);
      if (i < 3) {
        Serial.print(".");
      }
    }
    
    Serial.print(", port ");
    Serial.print(udp.remotePort());

    memset(packetBuffer, 0, UDP_TX_PACKET_MAX_SIZE); 
    udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);

    Serial.print(" Contents: ");
    Serial.println(packetBuffer);

    udp.beginPacket(udp.remoteIP(), udp.remotePort());
    udp.print(millis());
    udp.print(" ");
    udp.print(packetBuffer);
    udp.endPacket();
  }
  
  delay(10);
}