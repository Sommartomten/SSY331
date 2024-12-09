
int melody[] = { 
466, 466, 466, 466, 233, 233, 233, 233, 466, 466, 466, 466, 233, 233, 233, 233, 392, 466, 622, 392, 466, 622, 392, 466, 622, 392, 466, 622, 392, 466, 622, 233, 233, 233, 233, 349, 466, 587, 466, 466, 466, 233, 233, 233, 233, 370, 466, 740, 370, 466, 740, 370, 466, 740, 370, 466, 740, 77, 156, 77, 156, 77, 156, 77, 156, 349, 466, 698, 349, 466, 698, 349, 466, 698, 349, 466, 698, 73, 147, 73, 147, 73, 147, 73, 147, 262, 294, 330, 349, 392, 440, 65, 131, 73, 147, 82, 165, 87, 175, 98, 196, 110, 220, 349, 1047, 1175, 1319, 1397, 0, 87, 175, 0, 175, 220, 262, 349, 0, 466, 466, 466, 466, 233, 233, 233, 233, 466, 466, 466, 466, 233, 233, 233, 233, 392, 466, 622, 392, 466, 622, 392, 466, 622, 392, 466, 622, 392, 466, 622, 233, 233, 233, 233, 349, 466, 587, 466, 466, 466, 233, 233, 233, 233, 392, 466, 784, 392, 466, 784, 392, 466, 784, 392, 466, 784, 77, 156, 77, 156, 77, 156, 77, 156, 349, 466, 698, 392, 466, 784, 440, 587, 880, 466, 587, 933, 73, 147, 77, 156, 92, 185, 98, 196, 392, 466, 523, 0, 440, 523, 698, 0, 77, 156, 0, 87, 175, 0, 294, 349, 466, 0, 523, 622, 0, 523, 622, 116, 233, 0, 0, 466, 587, 440, 554, 466, 587, 440, 554, 175, 208, 233, 116, 208, 233, 466, 587, 440, 554, 466, 587, 415, 523, 175, 208, 233, 116, 208, 233, 392, 466, 370, 440, 392, 466, 156, 196, 233, 116, 196, 233, 392, 466, 0, 466, 523, 392, 156, 196, 233, 116, 196, 233, 415, 466, 587, 933, 175, 208, 233, 116, 208, 233, 933, 466, 831, 784, 466, 698, 175, 208, 233, 116, 208, 233, 622, 392, 523, 466, 156, 196, 233, 116, 196, 233, 466, 0, 523, 622, 0, 523, 622, 156, 196, 233, 0, 466, 587, 440, 554, 466, 587, 440, 554, 175, 208, 233, 116, 208, 233, 466, 587, 440, 554, 466, 587, 415, 523, 175, 208, 233, 116, 208, 233, 392, 466, 370, 440, 392, 466, 156, 196, 233, 116, 196, 233, 392, 466, 0, 466, 523, 392, 156, 196, 233, 116, 196, 262, 349, 466, 587, 698, 175, 233, 294, 233, 294, 349, 440, 523, 698, 175, 220, 262, 311, 220, 262, 311, 466, 587, 698, 933, 466, 466, 466, 466, 233, 294, 233, 233, 233, 233, 466, 0, 523, 622, 0, 
};
int noteDurations[] = { 
252, 126, 126, 504, 252, 126, 126, 504, 252, 126, 126, 504, 252, 126, 126, 504, 252, 252, 252, 126, 126, 126, 126, 126, 126, 252, 252, 252, 252, 252, 252, 252, 126, 126, 504, 252, 252, 252, 126, 126, 504, 252, 126, 126, 504, 252, 252, 252, 126, 126, 126, 126, 126, 126, 504, 504, 504, 252, 252, 126, 126, 126, 126, 504, 504, 252, 252, 252, 126, 126, 126, 126, 126, 126, 504, 504, 504, 252, 252, 126, 126, 126, 126, 504, 504, 126, 126, 126, 126, 252, 252, 126, 126, 126, 126, 126, 126, 126, 126, 252, 252, 252, 252, 252, 84, 84, 84, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 126, 126, 504, 252, 126, 126, 504, 252, 126, 126, 504, 252, 126, 126, 504, 252, 252, 252, 126, 126, 126, 126, 126, 126, 252, 252, 252, 252, 252, 252, 252, 126, 126, 504, 252, 252, 252, 126, 126, 504, 252, 126, 126, 504, 252, 252, 252, 126, 126, 126, 126, 126, 126, 504, 504, 504, 252, 252, 126, 126, 126, 126, 504, 504, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 126, 126, 126, 252, 252, 252, 504, 378, 378, 126, 126, 378, 378, 126, 126, 252, 252, 252, 252, 252, 252, 378, 378, 126, 126, 378, 378, 126, 126, 252, 252, 252, 252, 252, 252, 378, 378, 126, 126, 504, 504, 252, 252, 252, 252, 252, 252, 252, 252, 252, 168, 168, 168, 252, 252, 252, 252, 252, 252, 168, 168, 168, 504, 252, 252, 252, 252, 252, 252, 168, 168, 168, 168, 168, 168, 252, 252, 252, 252, 252, 252, 168, 168, 168, 504, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 126, 126, 126, 252, 252, 252, 504, 378, 378, 126, 126, 378, 378, 126, 126, 252, 252, 252, 252, 252, 252, 378, 378, 126, 126, 378, 378, 126, 126, 252, 252, 252, 252, 252, 252, 378, 378, 126, 126, 504, 504, 252, 252, 252, 252, 252, 252, 252, 252, 252, 168, 168, 168, 252, 252, 252, 252, 252, 252, 168, 168, 168, 504, 252, 252, 252, 504, 504, 168, 168, 168, 504, 252, 252, 252, 252, 504, 504, 504, 252, 252, 252, 252, 126, 126, 252, 252, 252, 252, 126, 126, 252, 252, 252, 252, 252, 252, 126, 126, 126, 252, 252, 504, 252, 252,

};

void setup() {
  pinMode(3,OUTPUT);
  digitalWrite(3,HIGH);
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(int); thisNote++)
  {    
    tone(6, melody[thisNote], noteDurations[thisNote] * .7);    
    delay(noteDurations[thisNote]);    
    noTone(6);
  }
}

void loop() {
  // no need to repeat the melody.
}
