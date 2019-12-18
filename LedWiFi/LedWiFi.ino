// Turn on the LED using mobile WiFi

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

//ESP Web Server Library to host a web page
#include <ESP8266WebServer.h>

#define LED 2  

//SSID and Password of your WiFi router
const char* ssid = "Samsung Galaxy Note 9";
const char* password = "qdaz1607";

//Declare a global object variable from the ESP8266WebServer class.
ESP8266WebServer server(80); //Server on port 80

void Root() {
 Serial.println("You called root page");
 server.send(200, "text/html", sendHTML()); //Send web page
}

void LEDon() {
 Serial.println("LED on page");
 digitalWrite(LED,LOW); //LED is connected in reverse
 server.send(200, "text/html", sendHTML());
}

void LEDoff() {
 Serial.println("LED off page");
 digitalWrite(LED,HIGH); //LED off
 server.send(200, "text/html", sendHTML());
}


void setup(void){
  Serial.begin(9600);
 
  WiFi.begin(ssid, password);   //Connect to your WiFi router
  Serial.println("");

  pinMode(LED,OUTPUT);
  //Power on LED state off
  digitalWrite(LED,HIGH);
 
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", Root);   //Which routine to handle at root location. This is display page
  server.on("/ledon", LEDon); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/ledoff", LEDoff);

  server.begin();               //Start server
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();        //Handle client requests
}

String sendHTML(){
  String ptr = "<!DOCTYPE html>\n"
"<html>\n"
"<body>\n"
"<center>\n"
"<h1>WiFi LED at GCOEC </h1><br>\n"
"<a href=\"ledon\">LED ON</a><br>\n"
"<a href=\"ledoff\">LED OFF</a><br>\n"
"<hr>\n"
"</center>\n"
"\n"
"</body>\n"
"</html>";
return ptr;
}
