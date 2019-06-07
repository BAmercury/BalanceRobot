



void coast_motor_brake(int M1_IN1, int M1_IN2, int M2_IN1, int M2_IN2)
{
  digitalWrite(M1_IN1, LOW);
  digitalWrite(M1_IN2,LOW);
  digitalWrite(M2_IN1, LOW);
  digitalWrite(M2_IN2, LOW);

}

void active_motor_brake(int M1_IN1, int M1_IN2, int M2_IN1, int M2_IN2)
{
  /*
  For active electric brake, we can hook up both sides of motor to +12V
  That is the same as setting IN2/2B and IN1/1B both to HIGH
  By short circuiting the path between the motor terminals
  it is effectivley feeding a very low impedance load that will
  slow motor down and make it hard to turn

  Connecting both sides to ground, IN2/2B and IN1/1B to LOW, wouldn't
  add any load to the motor, so motor will be able to freewheel and coast
  to stop
*/
  digitalWrite(M1_IN1, HIGH);
  digitalWrite(M1_IN2, HIGH);
  digitalWrite(M2_IN1, HIGH);
  digitalWrite(M2_IN2, HIGH);
}

void m1_drive_reg(int dir, int pwm)
{
  if (dir)
  {
    OCR3A = -pwm;
  }
  else
  {
    OCR3A = pwm;
  }
  
}

void m2_drive_reg(int dir, int pwm)
{
  if (dir)
  {
    OCR0B = -pwm;
  }
  else
  {
    OCR0B = pwm;
  }
  
}

void motor_drive_reg(int dir, int pwm)
{
  if (dir)
  {
    OCR3A = -pwm;
    OCR0B = -pwm;
  }
  else
  {
    OCR3A = pwm;
    OCR0B = pwm;
  }

}

void motor_drive_single_dir(boolean dir, int M_IN2)
{
  if (dir)
  {
    digitalWrite(M_IN2, HIGH);
    /*
      According to truth table of datasheet, if IN2/2B is HIGH,
      IN1/1B must be LOW for VS->OUT1, OUT2->GND
    */
    //analogWrite(M_IN1, -pwm);
  }
  else
  {
    /*
      Side note:
      According to truth table of datasheet, if IN2/2B is LOW,
      IN1/1B must be LOW for GND->OUT1, OUT2->GND, COAST BRAKE
    */
    digitalWrite(M_IN2, LOW);
    /*
      According to truth table of datasheet, if IN2/2B is LOW,
      IN1/1B must be HIGH for VS->OUT2, OUT1->GND
    */
    //analogWrite(M_IN1, pwm);
  }

}


void motor_drive(int dir, int pwm, int M1_IN1, int M1_IN2, int M2_IN1, int M2_IN2)
{
  if (dir)
  {
    digitalWrite(M1_IN2, HIGH);
    digitalWrite(M2_IN2, HIGH);
    /*
      According to truth table of datasheet, if IN2/2B is HIGH,
      IN1/1B must be LOW for VS->OUT1, OUT2->GND
    */
    analogWrite(M1_IN1, -pwm);
    analogWrite(M2_IN2, -pwm);
  }
  else
  {
    /*
      Side note:
      According to truth table of datasheet, if IN2/2B is LOW,
      IN1/1B must be LOW for GND->OUT1, OUT2->GND, COAST BRAKE
    */
    digitalWrite(M1_IN2, LOW);
    digitalWrite(M2_IN2, LOW);
    /*
      According to truth table of datasheet, if IN2/2B is LOW,
      IN1/1B must be HIGH for VS->OUT2, OUT1->GND
    */
    analogWrite(M1_IN1, pwm);
    analogWrite(M2_IN2, pwm);
  }


}
