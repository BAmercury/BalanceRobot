void State_A()
{
  if (digitalRead(PIN_M1_ENCB))
  {
    Sum_Right ++;
  }
  else
  { 
    Sum_Right --;
  }
}

void State_B()
{
  if (!digitalRead(PIN_M2_ENCB))
  {
    Sum_Left ++;
  }
  else
  {
    Sum_Left --;
  }
}

void VelocityEstimate()
{
  noInterrupts(); // Is this needed?
  dSum_Right = Sum_Right - Sum_Right_Last;
  Sum_Right_Last = Sum_Right;
  interrupts();
  dAlphaVol = (dAlphaConversion*dSum_Right)/(1.0*velEstT_us);
}

