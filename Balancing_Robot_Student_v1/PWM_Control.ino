void PWMControl()
{
  if (LThrottle > 0)
  {
    digitalWrite(TN1, HIGH);
    digitalWrite(TN2, LOW);
  }
  else if (LThrottle < 0)
  {
    digitalWrite(TN1, LOW);
    digitalWrite(TN2, HIGH);
  }
  else
  {
    OCR3A = 0;
  }
  if (RThrottle > 0)
  {
    digitalWrite(TN3, HIGH);
    digitalWrite(TN4, LOW);
  }
  else if (RThrottle < 0)
  {
    digitalWrite(TN3, LOW);
    digitalWrite(TN4, HIGH);
  }
  else
  {
    OCR0B = 0;
  }
  OCR3A = min(1023, (abs(10.23*LThrottle))); // Timer/Counter3 is a general purpose 16-bit Timer/Counter module
  OCR0B = min(255, (abs(2.55*RThrottle) )); // Timer/Counter0 is a general purpose 8-bit Timer/Counter module
}
