// Aircraft Navigation Lights System - Simplified for Tinkercad
// Red (Left Wing): Blinks at 1Hz
// Green (Right Wing): Blinks at 1Hz (opposite phase to red)
// Blue (Tail): Continuous ON

// Pin definitions
const int redLED = 8;      // Left wing (Red LED)
const int greenLED = 9;    // Right wing (Green LED)
const int blueLED = 10;    // Tail light (Blue LED)

// Timing variables
unsigned long previousMillis = 0;
const unsigned long interval = 500; // 500ms for 1Hz blinking (0.5s ON, 0.5s OFF)
bool ledState = false;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize LED pins as outputs
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  
  // Turn on tail light (always on)
  digitalWrite(blueLED, HIGH);
  
  // Initialize navigation lights
  digitalWrite(redLED, HIGH);   // Red starts ON
  digitalWrite(greenLED, LOW);  // Green starts OFF (opposite phase)
  
  Serial.println("Aircraft Navigation Lights System Started");
  Serial.println("Red LED: Pin 8 (1Hz)");
  Serial.println("Green LED: Pin 9 (1Hz opposite phase)");  
  Serial.println("Blue LED: Pin 10 (always ON)");
}

void loop() {
  // Get current time
  unsigned long currentMillis = millis();
  
  // Check if it's time to toggle the LEDs
  if (currentMillis - previousMillis >= interval) {
    // Save the last time we toggled
    previousMillis = currentMillis;
    
    // Toggle the state
    ledState = !ledState;
    
    // Update LEDs - opposite states for red and green
    digitalWrite(redLED, ledState);        // Red follows ledState
    digitalWrite(greenLED, !ledState);     // Green is opposite of ledState
    
    // Tail light stays on
    digitalWrite(blueLED, HIGH);
    
    // Debug output
    Serial.print("Time: ");
    Serial.print(currentMillis/1000.0);
    Serial.print("s | Red: ");
    Serial.print(ledState ? "ON " : "OFF");
    Serial.print(" | Green: ");
    Serial.print(!ledState ? "ON " : "OFF");
    Serial.println(" | Blue: ON");
  }
}