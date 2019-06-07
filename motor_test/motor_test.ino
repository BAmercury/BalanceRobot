#include <Encoder.h>
#include <TimerOne.h>
#define IN1 4
#define IN2 12
#define POT 0

#define DIR_PIN 2
#define IN1B 5
#define IN2B 7

volatile bool dir_lock = false;

Encoder enc1(2,3);
Encoder enc2(18,19);


void lock_direction()
{
  dir_lock = !dir_lock;
}

void coast_motor_brake()
{
  digitalWrite(IN2, LOW);
  digitalWrite(IN2B,LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN1B, LOW);

}


void active_motor_brake()
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
  digitalWrite(IN2, HIGH);
  digitalWrite(IN2B,HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN1B, HIGH);
}

void motor_drive(int dir, int pwm)
{
  if (dir)
  {
    digitalWrite(IN2, HIGH);
    digitalWrite(IN2B, HIGH);
    /*
      According to truth table of datasheet, if IN2/2B is HIGH,
      IN1/1B must be LOW for VS->OUT1, OUT2->GND
    */
    analogWrite(IN1, -pwm);
    analogWrite(IN1B, -pwm);
  }
  else
  {
    /*
      Side note:
      According to truth table of datasheet, if IN2/2B is LOW,
      IN1/1B must be LOW for GND->OUT1, OUT2->GND, COAST BRAKE
    */
    digitalWrite(IN2, LOW);
    digitalWrite(IN2B, LOW);
    /*
      According to truth table of datasheet, if IN2/2B is LOW,
      IN1/1B must be HIGH for VS->OUT2, OUT1->GND
    */
    analogWrite(IN1, pwm);
    analogWrite(IN1B, pwm);
  }


}



void setup()
{

    pinMode(IN2, OUTPUT);
    pinMode(IN2B, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN1B, OUTPUT);
    pinMode(POT, INPUT);
    Serial.begin(115200);
    //Timer1.initialize(2500);
    //Timer1.attachInterrupt(VelocityEstimate);
    //attachInterrupt(digitalPinToInterrupt(DIR_PIN), lock_direction, HIGH);
}

void loop() {
  int potValue = analogRead(POT);
  //int pwm = map(potValue, 0, 1023, 0 , 255);
  int pwm = 255;
  motor_drive(dir_lock, pwm);

  delay(100);

  coast_motor_brake();

  delay(1000);

  motor_drive(!dir_lock, pwm);

  delay(100);

  coast_motor_brake();

  delay(1000);
  
 




}
