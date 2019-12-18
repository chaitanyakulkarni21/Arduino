const int led[3] = {2,3,4};
int a;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led[0],OUTPUT);
  pinMode(led[1],OUTPUT);
  pinMode(led[2],OUTPUT);
}

void binary(int n)  // function to convert int to binary 
{
  for(int i = 0 ; i <3 ; i++){
    a = n%2;
    n = n/2;

    if(a == 0){
      digitalWrite(led[i],LOW);
    }
    
    if(a == 1){
      digitalWrite(led[i],HIGH);
    }
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 8 ; i++){
    binary(i);
    delay(1000);
  }
}
