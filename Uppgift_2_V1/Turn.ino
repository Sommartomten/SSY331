double Turn(char dir, double diff,double speed){
  if (dir == 'V'){
    diff=diff*(-1);
  }
    Serial.println("entering Turn");
      int SignalV = change_speed('V',speed_to_signalV(speed),speed+diff,1);
      int SignalH = change_speed('H',speed_to_signalV(speed),speed-diff,1);
      return(SignalV,SignalH);
}