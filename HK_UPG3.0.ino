#include <Servo.h>

Servo motorLeft;
Servo motorRight;
int servoPinLeft = 11;
int servoPinRight = 10;
int pinNrL = 6;
int pinNrR = 9;

float kLeft1 = -45.7333129;
float kLeft2 = 69.7616451;
float kLeft3 = -34856.56243512;

float kRight1 = 27.4273508;
float kRight2 = -83.0335264;
float kRight3 = 35564.5474;
float mLeft = 1494.0;   // värdena från linjerna i exceldokumentet.
float mRight = 1504.6;

float aMax = 0.2;  //aproximation utifrån 5 sekunder och mellan min till max v
float vMax = 0.17;
float vCurrent = 0.0;
float vAllowed;
float vLeftTarget = 0.0;
float vRightTarget = 0.0;
float prevTime = 0.0;

void setup() {
  Serial.begin(9600);
  motorLeft.attach(servoPinLeft); //Attach motor to pin and outpun initial signal.
  motorRight.attach(servoPinRight); //Attach motor to pin and outpun initial signal.

  pinMode(pinNrL, INPUT);
  pinMode(pinNrR, INPUT);

}

void loop() {
  float t = micros()/(1000000.0);
  int inputL = digitalRead(pinNrL);
  int inputR = digitalRead(pinNrR);
  Serial.println(String(inputL) + "   " + String(inputR));
  if (inputL == LOW){
    //Serial.println("Left ");
    aMax = 1;
    vLeftTarget = -0.15;
    vRightTarget = -0.15;
  }
  else if (inputR == LOW){
    //Serial.println("Right ");
    aMax = 1;
    vLeftTarget = -0.15;
    vRightTarget = -0.15;
  }
  else{
    //Serial.println("clear ");
    aMax = 0.2;
    vLeftTarget = 0.15;
    vRightTarget = 0.15;
    //Serial.println("time: " + String(t));
  }

  float dt = deltaTimeCalc();
  drive(vLeftTarget, vRightTarget, dt);
}

//funktion för vtarget till vallowed
float vAllowedCalcL(float vTarget, float deltaTime){
  //Serial.println("vAllowedCalc");
  float val = (vTarget - vCurrent)/deltaTime;
  //Serial.println("val: " + String(val));
  float aAllowed = constrain(val, -aMax, aMax);
  vAllowed = vCurrent + (aAllowed * deltaTime);
  //Serial.println("vAllowed: " + String(vAllowed));
  vAllowed = constrain(vAllowed, -vMax, vMax);
  vCurrent = vAllowed;
  //Serial.println("vAllowed: " + String(vAllowed));
  return vAllowed;
}

float vAllowedCalcR(float vTarget, float deltaTime){
  //Serial.println("vAllowedCalc");
  float val = (vTarget - vCurrent)/deltaTime;
  //Serial.println("valR: " + String(val));
  float aAllowed = constrain(val, -aMax, aMax);
  vAllowed = vCurrent + (aAllowed * deltaTime);
  vAllowed = constrain(vAllowed, -vMax, vMax);
  vCurrent = vAllowed;
  //Serial.println("vAllowed: " + String(vAllowed));
  return vAllowed;
}

//funktion för hastighet till pulser
float pulseLeft(float vAllowed){  
  float left = (kLeft1 * vAllowed + kLeft2 * pow(vAllowed,2) +  kLeft3 * pow(vAllowed,3)+ mLeft);
  //Serial.println("left: " + String(left));                                   
  float signalLeft = constrain(left, 1300, 1700); // kommer returnera värdet till den vänstra motorn.
  //Serial.println("leftsignal: " + String(signalLeft));
  return signalLeft;
}


float pulseRight(float vAllowed){
  float right = (kRight1 * vAllowed + kRight2 * pow(vAllowed,2) +  kRight3 * pow(vAllowed,3)+ mRight);
  float signalRight = constrain(right, 1300, 1700);
  //Serial.println("Right: " + String(signalRight));
  return signalRight;
}

//funktion för att få deltatime
float deltaTimeCalc(){
  float time = (micros())/(1000000.0);
  //Serial.println("timez: " + String(time));
  float deltaTime = time - prevTime;
  prevTime = time;
  return deltaTime;
}

//funktion för driving, tar in värderna för höger och vänster och deltaTime.
void drive (float vLeft, float vRight, float deltaTime){

  //Serial.println("drive");
  float vLeftAllowed = vAllowedCalcL(vLeft, deltaTime);
  float vRightAllowed = vAllowedCalcR(vRight,deltaTime);

  float vLeftNew = pulseLeft(vLeftAllowed);
  float vRightNew = pulseRight(vRightAllowed);
  //Serial.println(vLeftNew, vRightNew);
  motorRight.writeMicroseconds(vRightNew);
  motorLeft.writeMicroseconds(vLeftNew);
}


void paus(double pause){
  double end = pause*1000000;
  for (int i=0; i<=pause*1000000;){
    if (micros() > end){
      break;
    }
    else {}
  }





