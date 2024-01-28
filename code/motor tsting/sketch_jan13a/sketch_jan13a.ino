#include <AFMotor.h>

AF_DCMotor motor1(1);  // Motor 1
AF_DCMotor motor2(2);  // Motor 2

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Move forward
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  Serial.println("cholteesee");

  delay(2000);  // Move forward for 2 seconds

  // Stop motors
  motor1.setSpeed(0);
  motor2.setSpeed(0);

  delay(2000);  // Pause for 2 seconds
}
