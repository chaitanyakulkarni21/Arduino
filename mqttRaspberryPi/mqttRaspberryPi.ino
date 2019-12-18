

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "IIITN WiFi FAC";
const char* password = "";
const char* mqtt_server = "192.168.22.250";



WiFiClient espClient;
PubSubClient client(espClient);

const int buttonPin = D1;     // the number of the pushbutton pin
const int ledPin = D0;      // the number of the LED pin
int buttonState = 0;  

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
 
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  

  if ((char)payload[0] == '0') {
    digitalWrite(ledPin, LOW);   
    } else {
    digitalWrite(ledPin, HIGH);  
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("SubCntrLED1", "1");
      // ... and resubscribe
      client.subscribe("PubCntrLED1");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  buttonState = digitalRead(buttonPin); 
  if (buttonState == HIGH) {
    // turn LED on:
    client.publish("SubCntrLED1", "1");
  } else {
    // turn LED off:
    client.publish("SubCntrLED1", "0");
  }
  
}
