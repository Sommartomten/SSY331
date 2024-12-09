#include <Servo.h>

Servo motorLeft;
Servo motorRight;
int servoPinLeft = 11;
int servoPinRight = 10;
int pinNrL = 6;
int pinNrR = 9;

float kLeft1 =  -171.94271097;
float kLeft2 = -113.74748136 ;
float kLeft3 =  -30126.71226967;

float kRight1 = 256.84342658;
float kRight2 = 421.86117271;
float kRight3 =  26889.99006828;
float mLeft = 1494.0;   // värdena från linjerna i exceldokumentet.
float mRight = 1500.0;
String action ="";
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
int turns=0;
char previous= ' ';
float stop = 0;
float pause =0;
float d = 0;
float dWished= 0.1;//wanted distance in M
int melody[] = { 
466, 466, 466, 466, 233, 233, 233, 233, 466, 466, 466, 466, 233, 233, 233, 233, 392, 466, 622, 392, 466, 622, 392, 466, 622, 392, 466, 622, 392, 466, 622, 233, 233, 233, 233, 349, 466, 587, 466, 466, 466, 233, 233, 233, 233, 370, 466, 740, 370, 466, 740, 370, 466, 740, 370, 466, 740, 77, 156, 77, 156, 77, 156, 77, 156, 349, 466, 698, 349, 466, 698, 349, 466, 698, 349, 466, 698, 73, 147, 73, 147, 73, 147, 73, 147, 262, 294, 330, 349, 392, 440, 65, 131, 73, 147, 82, 165, 87, 175, 98, 196, 110, 220, 349, 1047, 1175, 1319, 1397, 0, 87, 175, 0, 175, 220, 262, 349, 0, 466, 466, 466, 466, 233, 233, 233, 233, 466, 466, 466, 466, 233, 233, 233, 233, 392, 466, 622, 392, 466, 622, 392, 466, 622, 392, 466, 622, 392, 466, 622, 233, 233, 233, 233, 349, 466, 587, 466, 466, 466, 233, 233, 233, 233, 392, 466, 784, 392, 466, 784, 392, 466, 784, 392, 466, 784, 77, 156, 77, 156, 77, 156, 77, 156, 349, 466, 698, 392, 466, 784, 440, 587, 880, 466, 587, 933, 73, 147, 77, 156, 92, 185, 98, 196, 392, 466, 523, 0, 440, 523, 698, 0, 77, 156, 0, 87, 175, 0, 294, 349, 466, 0, 523, 622, 0, 523, 622, 116, 233, 0, 0, 466, 587, 440, 554, 466, 587, 440, 554, 175, 208, 233, 116, 208, 233, 466, 587, 440, 554, 466, 587, 415, 523, 175, 208, 233, 116, 208, 233, 392, 466, 370, 440, 392, 466, 156, 196, 233, 116, 196, 233, 392, 466, 0, 466, 523, 392, 156, 196, 233, 116, 196, 233, 415, 466, 587, 933, 175, 208, 233, 116, 208, 233, 933, 466, 831, 784, 466, 698, 175, 208, 233, 116, 208, 233, 622, 392, 523, 466, 156, 196, 233, 116, 196, 233, 466, 0, 523, 622, 0, 523, 622, 156, 196, 233, 0, 466, 587, 440, 554, 466, 587, 440, 554, 175, 208, 233, 116, 208, 233, 466, 587, 440, 554, 466, 587, 415, 523, 175, 208, 233, 116, 208, 233, 392, 466, 370, 440, 392, 466, 156, 196, 233, 116, 196, 233, 392, 466, 0, 466, 523, 392, 156, 196, 233, 116, 196, 262, 349, 466, 587, 698, 175, 233, 294, 233, 294, 349, 440, 523, 698, 175, 220, 262, 311, 220, 262, 311, 466, 587, 698, 933, 466, 466, 466, 466, 233, 294, 233, 233, 233, 233, 466, 0, 523, 622, 0, 
};
int noteDurations[] = { 
252, 126, 126, 504, 252, 126, 126, 504, 252, 126, 126, 504, 252, 126, 126, 504, 252, 252, 252, 126, 126, 126, 126, 126, 126, 252, 252, 252, 252, 252, 252, 252, 126, 126, 504, 252, 252, 252, 126, 126, 504, 252, 126, 126, 504, 252, 252, 252, 126, 126, 126, 126, 126, 126, 504, 504, 504, 252, 252, 126, 126, 126, 126, 504, 504, 252, 252, 252, 126, 126, 126, 126, 126, 126, 504, 504, 504, 252, 252, 126, 126, 126, 126, 504, 504, 126, 126, 126, 126, 252, 252, 126, 126, 126, 126, 126, 126, 126, 126, 252, 252, 252, 252, 252, 84, 84, 84, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 126, 126, 504, 252, 126, 126, 504, 252, 126, 126, 504, 252, 126, 126, 504, 252, 252, 252, 126, 126, 126, 126, 126, 126, 252, 252, 252, 252, 252, 252, 252, 126, 126, 504, 252, 252, 252, 126, 126, 504, 252, 126, 126, 504, 252, 252, 252, 126, 126, 126, 126, 126, 126, 504, 504, 504, 252, 252, 126, 126, 126, 126, 504, 504, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 126, 126, 126, 252, 252, 252, 504, 378, 378, 126, 126, 378, 378, 126, 126, 252, 252, 252, 252, 252, 252, 378, 378, 126, 126, 378, 378, 126, 126, 252, 252, 252, 252, 252, 252, 378, 378, 126, 126, 504, 504, 252, 252, 252, 252, 252, 252, 252, 252, 252, 168, 168, 168, 252, 252, 252, 252, 252, 252, 168, 168, 168, 504, 252, 252, 252, 252, 252, 252, 168, 168, 168, 168, 168, 168, 252, 252, 252, 252, 252, 252, 168, 168, 168, 504, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 126, 126, 126, 252, 252, 252, 504, 378, 378, 126, 126, 378, 378, 126, 126, 252, 252, 252, 252, 252, 252, 378, 378, 126, 126, 378, 378, 126, 126, 252, 252, 252, 252, 252, 252, 378, 378, 126, 126, 504, 504, 252, 252, 252, 252, 252, 252, 252, 252, 252, 168, 168, 168, 252, 252, 252, 252, 252, 252, 168, 168, 168, 504, 252, 252, 252, 504, 504, 168, 168, 168, 504, 252, 252, 252, 252, 504, 504, 504, 252, 252, 252, 252, 126, 126, 252, 252, 252, 252, 126, 126, 252, 252, 252, 252, 252, 252, 126, 126, 126, 252, 252, 504, 252, 252,

};
void setup() {
  Serial.begin(9600);
  motorLeft.attach(servoPinLeft); //Attach motor to pin and outpun initial signal.
  motorRight.attach(servoPinRight); //Attach motor to pin and outpun initial signal.

  pinMode(pinNrL, INPUT);
  pinMode(pinNrR, INPUT);
}

void loop() {
float t = micros()/(1000000.0);
float raw = pingdist(12);
d=filter(d,raw);
Serial.println(String(d) +" "+ String(raw));
float dDiff=dWished-d;
float dt = deltaTimeCalc();
drive(regulator(dDiff),regulator(dDiff),dt);
// if (dDiff==0){
//   for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(int); thisNote++)
//   {    
//     tone(6, melody[thisNote], noteDurations[thisNote] * .7);    
//     delay(noteDurations[thisNote]);    
//     noTone(6);
//   }}
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
float regulator(float diff){
  return diff*(-1); //k uppskattas till 2
}

unsigned long pingTime(int pingPin){
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  unsigned long duration = pulseIn(pingPin, HIGH);
  return duration;
  }





float pingdist(int pingPin){
  unsigned long  t = pingTime(pingPin)/2;
  float  s= 343*t*pow(10,-6);
  return s;}

 float filter(float value, float new_value){
  float x = 0.4;//x uppskattas av oss
  return (1.0-x)*value + x*new_value; // returnar filtrert avstånd
  }






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








