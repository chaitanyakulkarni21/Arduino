
// DHT11
#include<DHT.h>
#include<DHT_U.h>
#define DHTPIN 3  // DHt11 connected to the D1 pin of the NodeMCU
#define DHTTYPE DHT11 //Type of Sensor used

DHT dht(DHTPIN,DHTTYPE);

float humidity_value = 0; //initial humidity value 
float temperature_value = 0;  // initial temperature value 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Begin serial communication with Ardiuno Uno
  dht.begin();  // initialising the dht11 sensor  
}

void loop() {
  // put your main code here, to run repeatedly:
  temperature_value = dht.readTemperature();  //reads the current temperature
  humidity_value = dht.readHumidity();  //reads the current humidity

  //Check if any reads failed and exit early (to try again)

  if(isnan(humidity_value) || isnan(temperature_value)){
    Serial.println(("failed to read from dht sensor"));
    return;
  }

  Serial.println(temperature_value);
  delay(2000);
  Serial.println(humidity_value);
  delay(2000);
}
