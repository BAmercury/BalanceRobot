#define IN1 9
#define POT 0
#define IN2 7
#define DIR_PIN 2
#define IN1B 10
#define IN2B 5


int dir = 0;

void setup()
{

    pinMode(IN2, OUTPUT);
    pinMode(IN2B, OUTPUT);
    pinMode(POT, INPUT);
    pinMode(DIR_PIN, INPUT);
    Serial.begin(115200);

    // Set initial rotation direction
    digitalWrite(IN2, LOW);
    digitalWrite(IN2B, LOW);
}

void loop() {
  int potValue = analogRead(POT);
   int pwm = map(potValue, 0, 1023, 0 , 255);
  
  dir = digitalRead(DIR_PIN);
  if (dir)
  {
    digitalWrite(IN2, HIGH);
    digitalWrite(IN2B, HIGH);
    Serial.println(pwm);
    analogWrite(IN1, -pwm);
    analogWrite(IN1B, -pwm);
  }
  else
  {
    digitalWrite(IN2, LOW);
    digitalWrite(IN2B, LOW);
    Serial.println(pwm);
    analogWrite(IN1, pwm);
    analogWrite(IN1B, pwm);
  }

 




}