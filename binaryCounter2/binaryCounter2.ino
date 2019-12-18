// Design a 3 bit counter using led to count from 0 to 7

void setup() {
  // put your setup code here, to run once:
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0 ; i <= 7 ; i++)
    // for pin 4 as MSB
    if(i < 4){
      digitalWrite(4,LOW);
    }
    else{
      digitalWrite(4,HIGH);
    }
    
    // for pin 3
    if(i == 0 || i == 1 || i == 4 || i == 5){
      digitalWrite(3,LOW);
    }
    else{
      digitalWrite(3,HIGH);
    }
    
    // for pin 2
    if(i == 0 || i == 2 || i == 4 || i == 6){
      digitalWrite(2,LOW);
  }
  else{
    digitalWrite(2,HIGH);
  }

  delay(2000);
}
