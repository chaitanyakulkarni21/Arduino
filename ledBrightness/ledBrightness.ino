// Increasing and decreasing the brightness of led

#define PIN_NO 11;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIN_NO,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0 ; i <= 255 ; i++){
    analogWrite(PIN_NO, i);
    delay(30);
  }
}
