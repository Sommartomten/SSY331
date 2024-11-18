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
char action ="";
float aMax = 0.2;  //aproximation utifrån 5 sekunder och mellan min till max v
float vMax = 0.17;
float vCurrentL = 0.0;
float vCurrentR = 0.0;
float vAllowedL;
float vAllowedR;
float vLeftTarget = 0.0;
float vRightTarget = 0.0;
float prevTime = 0.0;
bool signal= true;
int turnsR = 0;
int turnsL =0;
char previous= ' ';
float stop = 0;
int pause=0;
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
  Serial.println(String(inputL) + "   " + String(inputR) + "   " + action + "     "+ previous +"   ");
  if(signal)
  {
    if (inputR == LOW && inputL == LOW){
      action = "reverse";
      aMax = 1;
      vLeftTarget = -0.15;
      vRightTarget = -0.15;
      stop=1+t;
      signal=false;}
    else if (inputL == LOW){
      action = "reverse - left";
      aMax = 1;
      vLeftTarget = -0.15;
      vRightTarget = -0.05;
      stop=1+t;
      signal=false;
      previous='L';
      turnsL += 1;

    }
    else if (inputR == LOW){
      action = "reverse - right";
      aMax = 1;
      vLeftTarget = -0.05;
      vRightTarget = -0.15;
      stop=1+t; //ändrade från 1 till 2
      previous='R';
      signal=false;
      turnsR+=1;

    }
      
    else if(t<stop && t>pause){// drives forward between initial turn and correction turn
      action = "drive";
      aMax = 0.2;
      vLeftTarget = 0.15;
      vRightTarget = 0.15;
    }
    else if(turnsL!=0){ // performes correction turn
        action = "drive - left";
        aMax = 0.2;
        vLeftTarget = 0.15;
        vRightTarget = 0.05;
        pause=t+1;
        turnsL--;}

    else if (turnsR!=0){
        action = "drive - right";
        aMax = 0.2;
        vLeftTarget = 0.05;
        vRightTarget = 0.15;
        pause=t+1;
        turnsR--;
      }
      
    
    
    else{
      vLeftTarget = 0.15;
      vRightTarget = 0.15;
      stop=0;

      previous = ' ';
      //Serial.println("time: " + String(t));
      // default drive function
    }
  }
  else if(t>(stop)){
    signal=true;
    stop=t+1;
  }
  float dt = deltaTimeCalc();
  drive(vLeftTarget, vRightTarget, dt);
}

//funktion för vtarget till vallowed
float vAllowedCalcL(float vTarget, float deltaTime){
  //Serial.println("vAllowedCalc");
  float val = (vTarget - vCurrentL)/deltaTime;
  //Serial.println("val: " + String(val));
  float aAllowed = constrain(val, -aMax, aMax);
  vAllowedL = vCurrentL + (aAllowed * deltaTime);
  //Serial.println("vAllowed: " + String(vAllowed));
  vAllowedL = constrain(vAllowedL, -vMax, vMax);
  vCurrentL = vAllowedL;
  //Serial.println("vAllowed: " + String(vAllowed));
  return vAllowedL;
}

float vAllowedCalcR(float vTarget, float deltaTime){
  //Serial.println("vAllowedCalc");
  float val = (vTarget - vCurrentR)/deltaTime;
  //Serial.println("valR: " + String(val));
  float aAllowed = constrain(val, -aMax, aMax);
  vAllowedR = vCurrentR + (aAllowed * deltaTime);
  vAllowedR = constrain(vAllowedR, -vMax, vMax);
  vCurrentR = vAllowedR;
  //Serial.println("vAllowed: " + String(vAllowed));
  return vAllowedR;
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
  }}

char check(){
  int inputL = digitalRead(pinNrL);
  int inputR = digitalRead(pinNrR);
  if(inputL == 0; inputR == 0){
    return 'F';
  }
  else if (inputL == 0){
    return('L');
  }
  else if(inputR == 0){
    return('R');
  }
  else{
    return('S');
  }
}





