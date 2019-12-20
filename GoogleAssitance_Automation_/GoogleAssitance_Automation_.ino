#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define Relay1 D6
#define Relay2 D5
#define LED_01 D0
#define LED_02 D1

#define WLAN_SSID "Samsung Galaxy Note 9"             
#define WLAN_PASS "qdaz1607"        

#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883                  
#define AIO_USERNAME "chaitanya2110"            
#define AIO_KEY "aio_CkgR16iBdlmOsulfYGNg8d7w8wI4"   

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe Light1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/Relay1"); 
Adafruit_MQTT_Subscribe Light2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Relay2");

void MQTT_connect();

void setup() {
  Serial.begin(9600);

  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);

  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);

  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
 

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&Light1);
  mqtt.subscribe(&Light2);
}

void loop() {
 
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(20000))) {
    if (subscription == &Light1) 
    {
      Serial.print(F("Got: "));
      Serial.println((char *)Light1.lastread);
      int Light1_State = atoi((char *)Light1.lastread);
      if (Light1_State == 1)
      {
        digitalWrite(Relay1, LOW);
       digitalWrite(LED_01, HIGH); 
      }
      else if (Light1_State == 0)
      {
       digitalWrite(Relay1, HIGH);
       digitalWrite(LED_01, LOW); 
      }
    }
    if (subscription == &Light2) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light2.lastread);
      int Light2_State = atoi((char *)Light2.lastread);
     if (Light2_State == 1)
      {
        digitalWrite(Relay2, LOW);
        digitalWrite(LED_02, HIGH); 
      }
      else if (Light2_State == 0)
      {
       digitalWrite(Relay2, HIGH);
       digitalWrite(LED_02, LOW); 
      }
    }
  } 
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
  
}
