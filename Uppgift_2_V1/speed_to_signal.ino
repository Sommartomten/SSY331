double speed_to_signalH(double speed){
  return(constrain(1500+27.4273508*speed -83.0335264*power(speed,2)+ 35564.5474(speed,3),1300,1700));

}
double speed_to_signalV(double speed){
  return(constrain(1500-45.7333129*speed+69.7616451*power(speed,2)-34856.56243512(speed,3),1300,1700);
}