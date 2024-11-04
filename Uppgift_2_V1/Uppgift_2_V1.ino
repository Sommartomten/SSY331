#include <Servo.h>


Servo motor_hoger;
Servo motor_vanster;
int servoPinV = 10;
int servoPinH = 11;
int SignalV=1500;
int SignalH=1500;
bool first = true;
int t=0;
void setup() {
  motor_vanster.attach(servoPinV); //67.5
  motor_hoger.attach(servoPinH);
  Serial.begin(9600);
  Serial.print("leaving setup");
}
int Delta=100;
double speed = 10;
void loop(){
 int deltaT = abs(millis()-t);
  t=millis();
  if (not first){
       speed=0;
      SignalV += change_speed('V',SignalV,speed,deltaT);
      SignalH += change_speed('H',SignalH,speed,deltaT);
  }
  else if(millis()<=3000){
      if(Delta>10){
      SignalV += change_speed('V',SignalV,speed,deltaT);
      SignalH += change_speed('H',SignalH,speed,deltaT);
      Delta =0;}
    }
    else if(millis()<7000){
      Serial.println("entering Turn");
      SignalV += change_speed('V',SignalV,speed+5,deltaT);
      SignalH += change_speed('H',SignalH,speed-10,deltaT);
      Serial.println(SignalV);
      Serial.println(SignalH); }
    else if (millis()<14000){
      SignalV += change_speed('V',SignalV,speed-10,deltaT);
      SignalH += change_speed('H',SignalH,speed+5,deltaT);
      Serial.println(SignalV);
      Serial.println(SignalH);
    }
    else if(millis<1500){
           if(Delta>10){
      SignalV += change_speed('V',SignalV,speed,deltaT);
      SignalH += change_speed('H',SignalH,speed,deltaT);
      Delta =0;}
    }
  else{
    first = false;
    speed=0;
    }
   Delta+=deltaT;
   
Serial.println();
  motor_vanster.writeMicroseconds(SignalV); //<1500
  motor_hoger.writeMicroseconds(SignalH);  //>1500
}
