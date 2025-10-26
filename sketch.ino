const int potentiometer_pin = A1
const int force_sensor_pin = A0
const int motor_pin = 9

void start() {
  // we need to set the motor pin to output:
  pinMode(motorPin, OUTPUT);

}

void loop() {
  // Read sensor values:
  force_sensor_value = analogRead(force_sensor_pin);
  potentiometer_value = analogRead(potentiometer_pin);

  digitalWrite(
}
