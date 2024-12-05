#include <Servo.h>

Servo motorLeft;
Servo motorRight;
int servoPinLeft = 11;
int servoPinRight = 10;
int pinNrL = 6;
int pinNrR = 9;
int R = 1463;
int L = 1520;
void setup() {
  Serial.begin(9600);
  motorLeft.attach(servoPinLeft); //Attach motor to pin and outpun initial signal.
  motorRight.attach(servoPinRight); //Attach motor to pin and outpun initial signal.

  pinMode(pinNrL, INPUT);
  pinMode(pinNrR, INPUT);

}

void loop() {
  Serial.println(String(R)+"  "+ String(L));
 motorRight.writeMicroseconds(R);
  motorLeft.writeMicroseconds(L);
  delay(5000);
  R=1490;
  L=1490;

  }






