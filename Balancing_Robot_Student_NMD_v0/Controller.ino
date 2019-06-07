// Primary task: program a control function that computes Throttle and assigns the value to RThrottle and LThrottle
// Secondary task: program a control function that adds a deadzone compensation logic to improve performance
void Controller()
{
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Calculate the "Throttle" value using the state estimates and the gains.
  // Your code here...
  Throttle = -(kTheta*Theta + kAlpha*Alpha + kdTheta*dTheta + kdAlpha*dAlpha);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
  // Deadzone compensation
  if (Throttle > 0){
    Throttle = Throttle + deadZone;
  }
  else if (Throttle < 0){
    Throttle = Throttle - deadZone;
  }

  // Enforce throttle saturation limits
  if (Throttle > 100){
    Throttle = 100.0;
  }
  else if (Throttle < -100) {
    Throttle = - 100.0;
  }

  // Send identical throttle setting to both motors
  RThrottle = Throttle;
  LThrottle = Throttle;
}
