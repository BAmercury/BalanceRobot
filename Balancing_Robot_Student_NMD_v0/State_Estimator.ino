void State_Estimator()
{
  static long SR = 0;
  // This is a "complementary" filter which blends integrated gyro angles with accelerometer angles
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); // get "raw" values from sensor
  ThetaAccel = atan2(ay, az)*RadToDeg; // compute theta based on the raw accelerometer values
  dTheta = gx / Gyr_Gain; // scale the angular rate measurement into degrees/second
  tnow = micros();
  timeChange = tnow - tpre;
  tpre = tnow;
  dt = timeChange * 0.000001; // time increment since last loop
  ThetaGyro = dTheta*dt + Theta; // integrate gyro measurement and add to previous Theta estimate (Theta) to obtain a gyro-based estimate of Theta
  Theta = filterCoef*ThetaGyro + (1-filterCoef)*ThetaAccel; // blend theta estimate of gyro and theta estimate from accelerometer

  // Distance and speed estimates
  noInterrupts();
  SR = Sum_Right; // make a copy of current value;
  dAlpha = dAlphaVol; // make a copy of current value
  interrupts(); // after getting values of these variables, turn the relevant interrupts back on
  Alpha = (SR)/(PulsesPerRotation)*360; // Wheel angle, in degrees
  AlphaLast = Alpha;
}

void State_Estimator_Wheels_Only()
{
  static long SR = 0;
//  // This is a "complementary" filter which blends integrated gyro angles with accelerometer angles
//  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); // get "raw" values from sensor
//  ThetaAccel = atan2(ay, az)*RadToDeg; // compute theta based on the raw accelerometer values
//  dTheta = gx / Gyr_Gain; // scale the angular rate measurement into degrees/second
//  tnow = micros();
//  timeChange = tnow - tpre;
//  tpre = tnow;
//  dt = timeChange * 0.000001; // time increment since last loop
//  ThetaGyro = dTheta*dt + Theta; // integrate gyro measurement and add to previous Theta estimate (Theta) to obtain a gyro-based estimate of Theta
//  Theta = filterCoef*ThetaGyro + (1-filterCoef)*ThetaAccel; // blend theta estimate of gyro and theta estimate from accelerometer

  // Distance and speed estimates
  noInterrupts();
  SR = Sum_Right; // make a copy of current value;
  dAlpha = dAlphaVol; // make a copy of current value
  interrupts(); // after getting values of these variables, turn the relevant interrupts back on
  Alpha = (SR)/(PulsesPerRotation)*360; // Wheel angle, in degrees
  AlphaLast = Alpha;
}
