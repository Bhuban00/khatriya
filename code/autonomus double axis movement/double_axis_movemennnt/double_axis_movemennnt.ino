#include <Servo.h>

#define SENS_PIN  2
#define RELE_PIN  10
#define OLD_SERVO_PIN 11
#define NEW_SERVO_PIN 9

#define RON   LOW
#define ROF   HIGH

Servo oldServo;
Servo newServo;

bool flameDetected = false;

void setup() {
  pinMode(SENS_PIN, INPUT_PULLUP);
  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, ROF);

  oldServo.attach(OLD_SERVO_PIN);
  oldServo.write(90); // Set initial position to 90 degrees

  newServo.attach(NEW_SERVO_PIN);
  newServo.write(0); // Set initial position to 0 degrees
}

void loop() {
  detectFlame();
  
  if (flameDetected) {
    // Flame detected, wiggle old servo and move new servo
    for (int i = 0; i < 30; i++) {
      oldServo.write(90 + i); // Wiggle old servo to one side
      newServo.write(90 + i); // Move new servo up
      delay(20);
    }
    for (int i = 30; i > 0; i--) {
      oldServo.write(90 - i); // Wiggle old servo to the other side
      newServo.write(90 - i); // Move new servo down
      delay(20);
    }
  } else {
    // No flame detected, reset old servo and new servo
    oldServo.write(90); // Reset old servo to initial position
    newServo.write(0); // Reset new servo to initial position
  }

  // Control water pump based on flame detection
  digitalWrite(RELE_PIN, flameDetected ? RON : ROF); // Turn on water pump if flame is detected, otherwise turn it off
}

void detectFlame() {
  if (!digitalRead(SENS_PIN)) {
    flameDetected = true;
  } else {
    flameDetected = false;
  }
}
