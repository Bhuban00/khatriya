#include <Servo.h>

#define SENS  2

#define RELE  10

#define SERVO 11

#define RON   HIGH
#define ROF   LOW

Servo servo;

bool flSt = false;
int16_t i = 0;
bool up = false;

void Sens()
{
  if (!digitalRead(SENS))
  {
    Serial.println("jole na");
    flSt = false;
  }
  else
  {
    Serial.println("jole");
    flSt = true;
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("setup intiallizing...");
  pinMode(SENS, INPUT_PULLUP);
  pinMode(RELE, OUTPUT);
  digitalWrite(RELE, ROF);
  servo.attach(SERVO);
  servo.write(10);

}

void loop() {
  Sens();
  if (flSt) {
    // Flame detected
    if (servo.attached()) {
      // If the servo is attached, detach it
      //servo.detach();
      digitalWrite(RELE, RON);
      servo.write(((millis() / 15) % 180)+20);
      delay(1000);
      servo.write(((millis() / 15) % 180)-40);
      delay(1000);
    }
    // Turn on the water pump through the relay
    //digitalWrite(RELE, RON);  // Assuming RON is the state for turning on the relay
  } else {
    // No flame detected
    if (!servo.attached()) {
      // If the servo is not attached, attach it
      servo.attach(SERVO);
    }
    // Move the servo motor continuously
    servo.write((millis() / 15) % 180);  // Adjust the divisor for speed
    // Stop the water pump through the relay
    digitalWrite(RELE, ROF);  // Assuming ROF is the state for turning off the relay
  }
}
