
void setup() {
  // put your setup code here, to run once:
  pinMode(10,OUTPUT);
}

bool state = 0;
void loop() {
  // put your main code here, to run repeatedly:
  state = !state;
  digitalWrite(10,state);
  delay(1500);
  
}
