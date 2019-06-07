void PWMControl()
{
  // Saturation
  int m1_pwm = min(255, (abs(2.55*LThrottle))); // Timer 0 Pin 4 OCR3A
  int m2_pwm = min(1023, (abs(10.23*RThrottle))); // Timer 3 Pin 5
  static boolean m1_dir = false;
  static boolean m2_dir = false;
  if (LThrottle > 0)
  {
    m1_dir = true;
    motor_drive_single_dir(m1_dir,PIN_M1_IN2);
    //digitalWrite(TN1, HIGH);
    //digitalWrite(TN2, LOW);
  }
  else if (LThrottle < 0)
  {
    m1_dir = false;
    motor_drive_single_dir(m1_dir,PIN_M1_IN2);
    //digitalWrite(TN1, LOW);
    //digitalWrite(TN2, HIGH);
  }
  else
  {
    m1_pwm = 0;
    m1_dir = true;
    motor_drive_single_dir(m1_dir,PIN_M1_IN2);
    //OCR3A = 0;
  }

  
  if (RThrottle > 0)
  {
    m2_dir = true;
    motor_drive_single_dir(m2_dir, PIN_M2_IN2B);
    //digitalWrite(TN3, HIGH);
    //digitalWrite(TN4, LOW);
  }
  else if (RThrottle < 0)
  {
    m2_dir = true;
    motor_drive_single_dir(m2_dir, PIN_M2_IN2B);
    //digitalWrite(TN3, LOW);
    //digitalWrite(TN4, HIGH);
  }
  else
  {
    m2_pwm = 0;
    m2_dir = true;
    motor_drive_single_dir(m2_dir, PIN_M2_IN2B);
    //OCR0B = 0;
  }
  m1_drive_reg(m1_dir, m1_pwm);
  m2_drive_reg(m2_dir, m2_pwm);
  //OCR3A = min(1023, (abs(10.23*LThrottle))); // Timer/Counter3 is a general purpose 16-bit Timer/Counter module
  //OCR0B = min(255, (abs(2.55*RThrottle) )); // Timer/Counter0 is a general purpose 8-bit Timer/Counter module
}
