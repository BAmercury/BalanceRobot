/*
 Generate commands for testing motor performance
*/

void stepCmd(double stepTime, double stepDuration, double startThrottle, double stepThrottle, double endThrottle){
  static double t; 
  static double tStart;
  static bool firstCallFlag = true;
//  static double Throttle = 0;
  
  if (firstCallFlag){
    // get start time on first call to stepCmd()
    tStart = millis()*0.001;
    firstCallFlag = false;
  }
  
  t = millis()*0.001; // t = time in seconds since first loop
  if (t <= (stepTime+tStart))
  {
    Throttle = startThrottle;
  }
  else if (t <= (stepDuration+stepTime+tStart))
  {
    Throttle = stepThrottle;
  }
  else
  {;
    Throttle = endThrottle;
  }
  //Serial.println("Throttle: " + String(Throttle));
  LThrottle = Throttle;
  RThrottle = Throttle;
}
