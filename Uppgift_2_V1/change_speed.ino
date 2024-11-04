double change_speed(char wheel,double initial, double end, double delta){
double acc = 0;
if(wheel=='H'){
    acc=(speed_to_signalH(end)- initial)/delta;
    }

else{
  acc=(speed_to_signalV(end)- initial)/delta;
  }

acc=constrain(acc,-1,1);
return(acc);}