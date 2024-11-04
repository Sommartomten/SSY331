void setup() {
  Serial.begin(9600);
  #hello
}

void loop() {

  int t = millis();
  delay(1000);

  Serial.println(t/1000);
}
