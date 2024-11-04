int t_prev = 0;
void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT);//
pinMode(12,OUTPUT);//
}

void loop() {
while(millis()<5000){
  int t = millis()%200;
  if (t<100){
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
  }
  else{
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
  }}
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
}
