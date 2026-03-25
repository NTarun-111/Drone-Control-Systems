#include <LiquidCrystal.h>

// Initialize the LCD library with interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pin definitions
const int potPin = A0;        // Potentiometer (throttle) input
const int motorPin = 9;       // PWM pin for transistor base
const int ledPin = 13;        // Built-in LED for status indication

// Variables
int potValue = 0;             // Raw potentiometer reading
int throttlePercent = 0;      // Throttle percentage (0-100%)
int motorSpeed = 0;           // PWM value for motor (0-255)
unsigned long lastUpdate = 0; // For display update timing

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  
  // Initialize pins
  pinMode(motorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  // Display startup message
  lcd.setCursor(0, 0);
  lcd.print("Aircraft Prop");
  lcd.setCursor(0, 1);
  lcd.print("Control System");
  delay(2000);
  
  // Clear display and show initial status
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Throttle: 0%");
  lcd.setCursor(0, 1);
  lcd.print("Motor: OFF");
  
  Serial.println("Aircraft Propeller Speed Control System");
  Serial.println("Throttle | Motor PWM | Status");
  Serial.println("---------|----------|-------");
}

void loop() {
  // Read potentiometer value
  potValue = analogRead(potPin);
  
  // Convert to throttle percentage (0-100%)
  throttlePercent = map(potValue, 0, 1023, 0, 100);
  
  // Convert to motor PWM value (0-255)
  motorSpeed = map(potValue, 0, 1023, 0, 255);
  
  // Apply motor speed
  analogWrite(motorPin, motorSpeed);
  
  // Status LED indication
  if (throttlePercent > 10) {
    digitalWrite(ledPin, HIGH);  // Motor running
  } else {
    digitalWrite(ledPin, LOW);   // Motor off/idle
  }
  
  // Update display every 100ms to avoid flickering
  if (millis() - lastUpdate >= 100) {
    updateDisplay();
    updateSerial();
    lastUpdate = millis();
  }
  
  // Small delay for system stability
  delay(10);
}

void updateDisplay() {
  // Clear the entire display first to avoid artifacts
  lcd.clear();
  
  // First line - Throttle percentage
  lcd.setCursor(0, 0);
  lcd.print("Throttle: ");
  lcd.print(throttlePercent);
  lcd.print("%");
  
  // Second line - Motor status and PWM value
  lcd.setCursor(0, 1);
  lcd.print("PWM:");
  lcd.print(motorSpeed);
  lcd.print(" ");
  
  // Add status text
  if (throttlePercent == 0) {
    lcd.print("OFF");
  } else if (throttlePercent <= 25) {
    lcd.print("LOW");
  } else if (throttlePercent <= 50) {
    lcd.print("MED");
  } else if (throttlePercent <= 75) {
    lcd.print("HIGH");
  } else {
    lcd.print("MAX");
  }
}

void updateSerial() {
  // Send data to serial monitor for debugging
  Serial.print(throttlePercent);
  Serial.print("%     | ");
  Serial.print(motorSpeed);
  Serial.print("      | ");
  
  if (throttlePercent == 0) {
    Serial.println("OFF");
  } else if (throttlePercent <= 25) {
    Serial.println("LOW");
  } else if (throttlePercent <= 50) {
    Serial.println("MED");
  } else if (throttlePercent <= 75) {
    Serial.println("HIGH");
  } else {
    Serial.println("MAX");
  }
}