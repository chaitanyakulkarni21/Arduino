//#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "H7tZZ-OdBCBqPFI3JiG1DuZNBJ8ULO6-"; // the auth code that you got on your gmail
char ssid[] = "Zayn Malik"; // username or ssid of your WI-FI
char pass[] = "Saurav07@_ZaynMalik1D"; // password of your Wi-Fi

// In Blynk App
// Connect IN1 to D3
// In Blynk App - Pin: D3
// Logic: 1 to 0
// Push to Switch

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(D3,OUTPUT);
  digitalWrite(D3,HIGH);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
