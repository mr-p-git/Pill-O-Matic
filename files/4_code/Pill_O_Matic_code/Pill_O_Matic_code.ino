#include <Wire.h>          // Enables I2C communication for the RTC module
#include <RTClib.h>        // DS3231 RTC library
#include <Stepper.h>       // Stepper motor library

// ======================================================
// RTC SETUP
// ======================================================
RTC_DS3231 rtc;            // Create RTC object

// ======================================================
// PIN DEFINITIONS
// ======================================================
const int hallPin = A0;    // SS49E Hall sensor output pin

const int redLedPin = 6;   // RED LED: tray status
const int greenLedPin = 5; // GREEN LED: pill waiting in tray

// Stepper motor physical wiring to ULN2003:
// D8  -> IN1
// D9  -> IN2
// D10 -> IN3
// D11 -> IN4
//
// Stepper library pin order is intentionally set to
// 8, 10, 9, 11 for correct coil activation sequence.
const int motorPin1 = 8;   // First pin in software stepping sequence
const int motorPin2 = 10;  // Second pin in software stepping sequence
const int motorPin3 = 9;   // Third pin in software stepping sequence
const int motorPin4 = 11;  // Fourth pin in software stepping sequence

// ======================================================
// STEPPER SETUP
// ======================================================
const int stepsPerRevolution = 2048;   // 28BYJ-48 output shaft steps per full revolution
const int stepsPerDose = 256;          // 2048 / 8 = 256 steps = 45 degrees = one compartment move

Stepper stepperMotor(stepsPerRevolution, motorPin1, motorPin2, motorPin3, motorPin4);

// ======================================================
// HALL SENSOR THRESHOLDS
// Based on measured values:
// tray inserted ~533
// tray removed  ~518
// ======================================================
const int trayInThreshold  = 528;      // If reading rises to this or above, tray is considered inserted
const int trayOutThreshold = 523;      // If reading drops to this or below, tray is considered removed

// ======================================================
// DAILY DOSE SCHEDULE
// Add or remove entries as needed
// Example schedule below
// ======================================================
const int numDoseTimes = 7;            // Total number of scheduled daily dose times

int doseHours[numDoseTimes]   = {10, 10, 10, 10, 10, 10, 10};   // Scheduled hours (set hours here)
int doseMinutes[numDoseTimes] = {46, 46, 46, 46, 46, 47, 47};          // Scheduled minutes (set minutes here)
//int doseSeconds[numDoseTimes] = {10, 20, 30, 40, 50, 00, 55};   // Uncomment to include seconds accuracy (set seconds here)

bool doseTriggered[numDoseTimes] = {false};   // Automatically initializes all entries to false

// ======================================================
// SYSTEM STATE VARIABLES
// ======================================================
bool trayInPlace = false;              // Current tray state from Hall sensor
bool previousTrayInPlace = false;      // Previous tray state to detect transitions

bool pillWaiting = false;              // True after pill is dispensed and waiting in tray
int pendingDoseCount = 0;              // Counts doses that have triggered but not yet dispensed

int lastDay = -1;                      // Used to reset daily schedule flags when a new day starts

// ======================================================
// FUNCTION: turnOffStepper
// Purpose:
//   Fully de-energize all stepper coils when motor is not rotating
//   This keeps idle current near zero and prevents heating
// ======================================================
void turnOffStepper() {
  digitalWrite(motorPin1, LOW);        // Turn OFF coil 1
  digitalWrite(motorPin2, LOW);        // Turn OFF coil 2
  digitalWrite(motorPin3, LOW);        // Turn OFF coil 3
  digitalWrite(motorPin4, LOW);        // Turn OFF coil 4
}

// ======================================================
// FUNCTION: updateTrayState
// Purpose:
//   Read analog Hall sensor and update trayInPlace using hysteresis
// ======================================================
void updateTrayState() {
  int hallValue = analogRead(hallPin);   // Read Hall sensor value

  // If tray is currently considered OUT, only switch to IN when value is clearly high enough
  if (!trayInPlace && hallValue >= trayInThreshold) {
    trayInPlace = true;
  }

  // If tray is currently considered IN, only switch to OUT when value is clearly low enough
  if (trayInPlace && hallValue <= trayOutThreshold) {
    trayInPlace = false;
  }

  // Serial debug output
  Serial.print("Hall Value: ");
  Serial.print(hallValue);
  Serial.print(" | Tray: ");
  if (trayInPlace) {
    Serial.println("IN PLACE");
  } else {
    Serial.println("REMOVED");
  }
}

// ======================================================
// FUNCTION: updateRedLed
// Purpose:
//   RED LED ON when tray missing
//   RED LED OFF when tray inserted
// ======================================================
void updateRedLed() {
  if (trayInPlace) {
    digitalWrite(redLedPin, LOW);      // Tray inserted -> RED OFF
  } else {
    digitalWrite(redLedPin, HIGH);     // Tray removed/missing -> RED ON
  }
}

// ======================================================
// FUNCTION: updateGreenLed
// Purpose:
//   GREEN LED ON when a dispensed pill is waiting in tray
//   GREEN LED OFF otherwise
// ======================================================
void updateGreenLed() {
  if (pillWaiting) {
    digitalWrite(greenLedPin, HIGH);   // Pill waiting -> GREEN ON
  } else {
    digitalWrite(greenLedPin, LOW);    // No pill waiting -> GREEN OFF
  }
}

// ======================================================
// FUNCTION: dispenseOnePill
// Purpose:
//   Rotate one compartment, then de-energize motor
// ======================================================
void dispenseOnePill() {
  Serial.println("Dispensing one pill...");

  stepperMotor.step(stepsPerDose);     // Rotate 45 degrees = one compartment
  turnOffStepper();                    // Immediately remove holding current after motion

  pillWaiting = true;                  // Pill is now waiting in tray
  updateGreenLed();                    // Turn GREEN LED ON

  Serial.println("Dispense complete -> GREEN LED ON");
}

// ======================================================
// FUNCTION: checkScheduledDoseTimes
// Purpose:
//   Compare current RTC time against all preset time slots
//   Each matching slot adds one pending dose only once per day
// ======================================================
void checkScheduledDoseTimes(DateTime now) {
  for (int i = 0; i < numDoseTimes; i++) {

    // Only trigger this slot if it has not already triggered today
    if (!doseTriggered[i] &&
        now.hour() == doseHours[i] &&
        now.minute() == doseMinutes[i]
         // && now.second() == doseSeconds[i]   // Uncomment to include seconds accuracy
       ) {

      doseTriggered[i] = true;         // Mark this time slot as triggered for today
      pendingDoseCount++;              // Add one pending dose

      Serial.print("Scheduled dose triggered at ");
      if (doseHours[i] < 10) Serial.print("0");
      Serial.print(doseHours[i]);
      Serial.print(":");
      if (doseMinutes[i] < 10) Serial.print("0");
      Serial.print(doseMinutes[i]);

       //Serial.print(":");                              // Uncomment to include seconds accuracy
       //if (doseSeconds[i] < 10) Serial.print("0");    // Uncomment to include seconds accuracy
       //Serial.print(doseSeconds[i]);                  // Uncomment to include seconds accuracy

      Serial.print(" | Pending doses = ");
      Serial.println(pendingDoseCount);
    }
  }
}

// ======================================================
// FUNCTION: resetDailyScheduleIfNeeded
// Purpose:
//   At the start of a new day, allow all scheduled slots to trigger again
// ======================================================
void resetDailyScheduleIfNeeded(DateTime now) {
  if (now.day() != lastDay) {
    lastDay = now.day();               // Store new day

    for (int i = 0; i < numDoseTimes; i++) {
      doseTriggered[i] = false;        // Reset all daily trigger flags
    }

    Serial.println("New day detected -> daily schedule reset");
  }
}

// ======================================================
// FUNCTION: printCurrentTime
// Purpose:
//   Print RTC time to Serial Monitor
// ======================================================
void printCurrentTime(DateTime now) {
  Serial.print("Time: ");
  Serial.print(now.year());
  Serial.print("/");
  if (now.month() < 10) Serial.print("0");
  Serial.print(now.month());
  Serial.print("/");
  if (now.day() < 10) Serial.print("0");
  Serial.print(now.day());
  Serial.print("  ");

  if (now.hour() < 10) Serial.print("0");
  Serial.print(now.hour());
  Serial.print(":");
  if (now.minute() < 10) Serial.print("0");
  Serial.print(now.minute());
  Serial.print(":");
  if (now.second() < 10) Serial.print("0");
  Serial.println(now.second());
}

// ======================================================
// SETUP
// ======================================================
void setup() {
  Serial.begin(9600);                  // Start Serial Monitor
  Wire.begin();                        // Start I2C bus

  // Set LED pins as outputs
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  // Set stepper pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  // Initialize LEDs OFF
  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, LOW);

  // Set stepper speed
  stepperMotor.setSpeed(10);           // 10 RPM is a safe working speed for this motor

  // Make sure motor starts fully de-energized
  turnOffStepper();

  // Start RTC
  if (!rtc.begin()) {
    Serial.println("RTC not found");
    while (1) {                        // Stop here if RTC is not detected
    }
  }

  // Uncomment this ONCE to set RTC to compile/upload time, then comment it again
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  Serial.println("System started");
}

// ======================================================
// LOOP
// ======================================================
void loop() {
  DateTime now = rtc.now();            // Read current RTC time

  printCurrentTime(now);               // Print current time to Serial Monitor

  // Step 1: reset dose flags if a new day has started
  resetDailyScheduleIfNeeded(now);

  // Step 2: update Hall sensor / tray state
  updateTrayState();

  // Step 3: update RED LED from tray state
  updateRedLed();

  // Step 4: detect tray removal AFTER a pill was dispensed
  // This implements:
  // tray removed while pillWaiting == true -> user is taking pill
  if (previousTrayInPlace == true && trayInPlace == false && pillWaiting == true) {
    pillWaiting = false;               // Pill has been taken
    updateGreenLed();                  // Turn GREEN LED OFF
    Serial.println("Tray removed while pill waiting -> GREEN LED OFF, pillWaiting = false");
  }

  // Step 5: remember tray state for next loop
  previousTrayInPlace = trayInPlace;

  // Step 6: check all scheduled times and add pending doses
  checkScheduledDoseTimes(now);

  // Step 7: dispense only if:
  // - there is at least one pending dose
  // - tray is inserted
  // - no previous pill is still waiting
  if (pendingDoseCount > 0 && trayInPlace == true && pillWaiting == false) {
    dispenseOnePill();                 // Dispense one dose
    pendingDoseCount--;                // One pending dose has now been dispensed

    Serial.print("Pending doses remaining = ");
    Serial.println(pendingDoseCount);
  }

  // Step 8: if tray is missing and a dose is pending, do not dispense yet
  if (pendingDoseCount > 0 && trayInPlace == false) {
    Serial.println("Dose pending, but tray missing -> waiting for tray insertion");
  }

  // Step 9: if nothing is moving, keep motor fully OFF
  turnOffStepper();

  delay(200);                          // Small loop delay for stable operation
}