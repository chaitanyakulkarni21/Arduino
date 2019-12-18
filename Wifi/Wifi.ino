#include <ESP8266WiFi.h>
void setup()
{
  // Begin Serial Monitor
  // Begin Wifi using SSID and Pass E.g.  WiFi.begin("SSID", "Password");
  // Print Connecting Status E.g. Serial.println("Connecting");
  // Wait Until WiFi gets connected 

  Serial.begin(9600);
  WiFi.begin("Samsung Galaxy Note 9", "qdaz1607");
  Serial.print("Connecting...");

  while (WiFi.status() != WL_CONNECTED)
  {
  delay(1000);
  Serial.print(".");
  }

  Serial.println("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  
  // Print connected status.   E.g. Serial.println("Connected, IP address: ");
  // Print IP address, once connected  E.g. Serial.println(WiFi.localIP());
}
void loop() {}
