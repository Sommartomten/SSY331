void setup() {
  Serial.begin(9600);
  
}

void loop() {

  int t = millis();
  delay(1000);

  Serial.println(t/1000);
}
