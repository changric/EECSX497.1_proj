#include "Energia.h"

#line 1 "C:/Users/Megumi Kato/workspace_v10/WiFiChatServer/WiFiChatServer.ino"






















#ifndef __CC3200R1M1RGC__

#include <SPI.h>
#endif
#include <WiFi.h>


void setup();
void loop();
void printWifiStatus();

#line 30
char ssid[] = "Chang";

char password[] = "7783166783";

WiFiServer server(23);

boolean alreadyConnected = false; 

void setup() {
  
  Serial.begin(9600);

  
  Serial.print("Attempting to connect to Network named: ");
  
  Serial.println(ssid); 
  
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    
    Serial.print(".");
    delay(300);
  }
  
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");
  
  while (WiFi.localIP() == INADDR_NONE) {
    
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nIP Address obtained");

  
  printWifiStatus();

  
  server.begin();
}


void loop() {
  
  WiFiClient client = server.available();


  
  if (client) {
    if (!alreadyConnected) {
      
      client.flush();
      Serial.println("We have a new client");
      client.println("Hello, client!");
      alreadyConnected = true;
    }

    if (client.available() > 0) {
      
      char thisChar = client.read();
      
      server.write(thisChar);
      
      Serial.write(thisChar);
    }
  }
}


void printWifiStatus() {
  
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}





