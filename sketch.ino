#include <Servo.h>

const int potentiometer_pin = A1;
const int force_sensor_pin = A0;
const int motor_pin = 9;

// Force sensor threshold - adjust this value based on testing
const int force_threshold = 100;

// Servo angles
const int servo_on_angle = 90;   // Angle when force is applied
const int servo_off_angle = 0;   // Angle when no force

Servo myServo;
int force_sensor_value = 0;
int potentiometer_value = 0;

void setup() {
  // Attach the servo to the motor pin
  myServo.attach(motor_pin);

  // Initialize servo to off position
  myServo.write(servo_off_angle);

  // Optional: for debugging
  Serial.begin(9600);
}

void loop() {
  // Read sensor values
  force_sensor_value = analogRead(force_sensor_pin);
  potentiometer_value = analogRead(potentiometer_pin);

  // Check if force exceeds threshold AND potentiometer is turned
  // Potentiometer threshold: > 100 means it's turned (adjust as needed)
  if (force_sensor_value > force_threshold && potentiometer_value > 100) {
    // Turn servo on
    myServo.write(servo_on_angle);
  } else {
    // Turn servo off
    myServo.write(servo_off_angle);
  }

  // Optional: print sensor values for debugging
  Serial.print("Force: ");
  Serial.print(force_sensor_value);
  Serial.print(" | Pot: ");
  Serial.println(potentiometer_value);

  // Small delay for stability
  delay(50);
}
