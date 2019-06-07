void printData()
{
  if (firstLoop){ // Print out column headers for easier data import to MATLAB if firstLoop == true
    firstLoop = false;
    Serial.println(" ");
    Serial.print("Time"); Serial.print("\t"); Serial.print("Theta"); Serial.print("\t"); Serial.print("dTheta"); Serial.print("\t"); 
    Serial.print("Alpha"); Serial.print("\t"); Serial.print("dAlpha"); Serial.print("\t"); Serial.println("Throttle");
  }
  else{ // Print data to serial monitor
    Serial.print(millis()*0.001,3); Serial.print("\t"); Serial.print(Theta); Serial.print("\t"); Serial.print(dTheta); Serial.print("\t"); 
    Serial.print(Alpha); Serial.print("\t"); Serial.print(dAlpha); Serial.print("\t"); Serial.println(Throttle); 
    // Serial.print(Sum_Right); Serial.print("\t"); Serial.print(Sum_Left); Serial.print("\t");
  }
  Serial.flush(); // Force data transmission to complete before continuing
}

void printData_Wheel_Only()
{
  if (firstLoop){ // Print out column headers for easier data import to MATLAB if firstLoop == true
    firstLoop = false;
    Serial.println(" ");
    Serial.print("Time"); Serial.print("\t"); 
    Serial.print("Alpha"); Serial.print("\t"); Serial.print("dAlpha"); Serial.print("\t"); Serial.println("Throttle");
  }
  else{ // Print data to serial monitor
    Serial.print(millis()*0.001,3); Serial.print("\t");
    Serial.print(Alpha); Serial.print("\t"); Serial.print(dAlpha); Serial.print("\t"); Serial.println(Throttle); 
    //Serial.println(Throttle);
    // Serial.print(Sum_Right); Serial.print("\t"); Serial.print(Sum_Left); Serial.print("\t");
  }
  Serial.flush(); // Force data transmission to complete before continuing
}
