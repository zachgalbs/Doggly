// Pins
const int POT_PIN = A1;
const int FORCE_PIN = A0;
const int MOTOR_PIN = 9;

// Thresholds
const int FORCE_TH = 512;

// Dispense time = 1 second
const unsigned long DISPENSE_TIME = 1000;

// Potentiometer sets cooldown delay: 4–8 hours
const unsigned long MIN_DELAY = 4UL * 1000UL;  // 4 hours (ms)
const unsigned long MAX_DELAY = 8UL * 1000UL;  // 8 hours (ms)

bool dispensing = false;
unsigned long startDispense = 0;
unsigned long lastDispenseEnd = 0;  // tracks cooldown timing

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Feeder Ready (Press force pad to dispense)");
}

void loop() {
  int forceVal = analogRead(FORCE_PIN);
  int potVal = analogRead(POT_PIN);

  // Convert pot to cooldown time (4–8 hours)
  unsigned long cooldown = map(potVal, 0, 1023, MIN_DELAY, MAX_DELAY);
  cooldown = constrain(cooldown, MIN_DELAY, MAX_DELAY);

  bool inCooldown = (millis() - lastDispenseEnd < cooldown);

  // Start dispensing if:
  // - Force pressed
  // - Not already dispensing
  // - Cooldown expired
  if (!dispensing && !inCooldown && forceVal > FORCE_TH) {
    dispensing = true;
    startDispense = millis();
    Serial.println("Dispensing food!");
  }

  // Run motor for fixed 1 second
  if (dispensing) {
    analogWrite(MOTOR_PIN, 100);  // safe fixed speed
    if (millis() - startDispense >= DISPENSE_TIME) {
      dispensing = false;
      analogWrite(MOTOR_PIN, 0);
      lastDispenseEnd = millis();
      Serial.print("Dispense done. Cooldown (ms): ");
      Serial.println(cooldown);
    }
  } else {
    analogWrite(MOTOR_PIN, 0);
  }

  delay(20);
}
