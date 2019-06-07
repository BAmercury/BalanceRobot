/*
  MEM351 Balancing Robot Lab
  STUDENT v1.0
  (c) David Hartman, Feb. 2019
  Drexel University
  
  License: The MIT License
  Permission is hereby granted, free of charge, to any person obtaining a copy of this 
  software and associated documentation files (the "Software"), to deal in the Software 
  without restriction, including without limitation the rights to use, copy, modify, 
  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
  permit persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or 
  substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// Include statements
#include <I2Cdev.h>
#include <MPU6050.h>
#include <TimerOne.h>

MPU6050 accelgyro;
MPU6050 initialize;
int16_t ax, ay, az;
int16_t gx, gy, gz;

double ThetaAccel, ThetaGyro, Theta, dTheta, dt;
float LThrottle, RThrottle, Throttle;
unsigned long tnow, tpre;
double Alpha, AlphaLast, dAlpha;
volatile double dAlphaVol;
int timeChange;
volatile long Sum_Right, Sum_Left, Sum_Right_Last, dSum_Right;
const byte gyroRangeByte = 1; // 0 =  +/-250 deg/s, 1 =  +/-500 deg/s, 2 =  +/-1000 deg/s, 3 = +/-2000 deg/s;
const double range = 500*2; // Be sure to change this correctly if you change the gyro range!
const double Gyr_Gain = 1.0*(65535-1)/range, PulsesPerRotation = 256.0, RadToDeg = 180 / PI, dAlphaConversion = 360 / PulsesPerRotation * 1000000;
//_____________________________________________________________________________________________________
//_____________________________________________________________________________________________________

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Control gains
// Define your control gains here...
const double kTheta = -10.1530, kAlpha = -0.0679, kdTheta = -0.8690, kdAlpha = -0.2687;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Control enabled limitation
const double ThetaLimit = 30; // limit on angle for which controller is engaged, degrees

// Complimentary filter coefficient
const double filterCoef = 0.99; // A higher coefficient results in a higher weighting of integrated gyro for estimated theta angle

// Motor deadzone compensation
const unsigned int deadZone = 16; // Motor deadzone compensation, in percent throttle

// Motor velocity estimation period
const double velEstT_us = 25000; // how long a period to use for computing the average wheel velocity, in microseconds
//_____________________________________________________________________________________________________
//_____________________________________________________________________________________________________


// Motor H-Bridge Control Pins
int PIN_M1_IN1 = 4; // Timer 1 PWM Pins
int PIN_M1_IN2 = 12; // Timer 1 PWM Pins
int PIN_M2_IN1B = 5; // Timer 3 PWM Pins
int PIN_M2_IN2B = 7; // Timer 3 PWM Pins

// Motor Encoder Pins
// Arduino MEGA External Interruptable Pins
int PIN_M1_ENCA = 2;
int PIN_M1_ENCB = 3;
int PIN_M2_ENCA = 18;
int PIN_M2_ENCB = 19;

// Flags
boolean ratePinState = HIGH, firstLoop = true;

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  // Setup timers used for PWM
  TCCR3A = _BV(COM3A1) | _BV(WGM31) | _BV(WGM30); // TIMER_3 @1K Hz, fast pwm
  TCCR3B = _BV(CS31);
  TCCR0A = _BV(COM0B1) | _BV(WGM01) | _BV(WGM00); // TIMER_0 @1K Hz, fast pwm
  TCCR0B = _BV(CS01) | _BV(CS00);

  accelgyro.initialize(); // Initialize mpu6050
  accelgyro.setFullScaleGyroRange(gyroRangeByte);

  for (int i = 0; i < 300; i++) // Looping 300 times to initialize angle
  {
    State_Estimator(); // Run the state estimation function
  }

  // Setup pins used for PWM output and H-bridge control
  pinMode(PIN_M1_ENCA, INPUT);
  pinMode(PIN_M1_ENCB, INPUT);
  pinMode(PIN_M1_IN1, OUTPUT);
  pinMode(PIN_M1_IN2, OUTPUT);
  pinMode(PIN_M2_ENCA, INPUT);
  pinMode(PIN_M2_ENCB, INPUT);
  pinMode(PIN_M2_IN1B, OUTPUT);
  pinMode(PIN_M2_IN2B, OUTPUT);
  // Setup interrupts used to capture encoder signals
  attachInterrupt(PIN_M1_ENCA, State_A, FALLING);
  attachInterrupt(PIN_M2_ENCA, State_B, FALLING);

  Timer1.initialize(velEstT_us); // initialize ISR timer based on this period
  Timer1.attachInterrupt(VelocityEstimate); // attach named ISR to timer

  Serial.println("Setup Complete");
}

void loop() {
  State_Estimator();
  if (abs(Theta) < ThetaLimit) { // Check if the tilt of the robot is within the limit chosen for feedback control
    Controller(); // Compute motor command based on state estimate
    PWMControl(); // Apply motor command to motor via PWM outputs
  }
  else // If tilt is not within limits, shutoff the motors and zero the motor position
  {
    // Stops left and right motor
    active_motor_brake(PIN_M1_IN1, PIN_M1_IN2, PIN_M2_IN1B, PIN_M2_IN2B);
    // Reset motor position to zero (Alpha)
    Sum_Right = 0; Sum_Left = 0;
    Alpha = 0; AlphaLast = 0;
  }
  printData(); // execute the print command
}

// _________________________________________________________________________________________________________________
// THE END
