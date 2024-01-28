#include <Servo.h>

#define SENS  2

#define RELE  10

#define SERVO 11

#define RON   LOW
#define ROF   HIGH

Servo servo;

bool flSt = false;
int16_t i = 0;
bool up = false;

void Sens()
{
  if (!digitalRead(SENS))
  {
    flSt = true;
  }
  else
  {
    flSt = false;
  }
}

void setup()
{
  pinMode(SENS, INPUT_PULLUP);
  pinMode(RELE, OUTPUT);
  digitalWrite(RELE, ROF);
  servo.attach(SERVO);
  servo.write(0);
}

void loop() {
  Sens();
  if (flSt) {
    // Flame detected
    if (servo.attached()) {
      // If the servo is attached, detach it
      servo.detach();
    }
    // Turn on the water pump through the relay
    digitalWrite(RELE, RON);  // Assuming RON is the state for turning on the relay
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
