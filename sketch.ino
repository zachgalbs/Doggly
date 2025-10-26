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
  // Optional: for debugging
  Serial.begin(9600);
  Serial.println("Starting Doggly Arduino Sketch...");

  // Attach the servo to the motor pin
  myServo.attach(motor_pin);
  Serial.println("Servo attached to pin 9");

  // Test servo movement on startup
  Serial.println("Testing servo - moving to 90 degrees");
  myServo.write(90);
  delay(1000);
  Serial.println("Testing servo - moving to 0 degrees");
  myServo.write(0);
  delay(1000);
  Serial.println("Servo test complete - starting main loop");
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
    Serial.print("✓ MOTOR ON  | ");
  } else {
    // Turn servo off
    myServo.write(servo_off_angle);
    Serial.print("✗ MOTOR OFF | ");
  }

  // Print sensor values for debugging
  Serial.print("Force: ");
  Serial.print(force_sensor_value);
  Serial.print(" (threshold: ");
  Serial.print(force_threshold);
  Serial.print(") | Pot: ");
  Serial.print(potentiometer_value);
  Serial.print(" (threshold: 100)");

  // Show which conditions are met
  Serial.print(" | Conditions: ");
  if (force_sensor_value > force_threshold) {
    Serial.print("Force✓ ");
  } else {
    Serial.print("Force✗ ");
  }
  if (potentiometer_value > 100) {
    Serial.print("Pot✓");
  } else {
    Serial.print("Pot✗");
  }
  Serial.println();

  // Small delay for stability
  delay(50);
}
