#include <Joystick.h>

// Create a Joystick instance
Joystick_ Joystick;

// Define the pins for the buttons, including A1, A2, and A3
const int buttonPins[15] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A1, A2, A3};
bool buttonStates[15] = {false};

void setup() {
  // Initialize Joystick with 15 buttons and no axes
  Joystick.begin(false); // false = no auto send state

  // Initialize button pins
  for (int i = 0; i < 15; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP); // Set button pins as input with pull-up resistor
  }
}

void loop() {
  // Read the state of each button
  for (int i = 0; i < 15; i++) {
    bool currentButtonState;

    // Check if the pin is an analog pin (A1, A2, A3) and read appropriately
    if (buttonPins[i] >= A0) {
      currentButtonState = analogRead(buttonPins[i]) < 512; // Change threshold as needed
    } else {
      currentButtonState = digitalRead(buttonPins[i]) == LOW; // LOW means pressed
    }

    // Update the joystick button state
    Joystick.setButton(i, currentButtonState);

    // Store the state for later use if needed
    buttonStates[i] = currentButtonState;
  }

  // Send the current button state to the host
  Joystick.sendState();

  // Add delay between updates
  delay(100); // Update every 100 ms
}

