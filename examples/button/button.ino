// This code turns a led on/off through a debounced switch

#include "digitalPin.h"

#define SWITCH 2
#define pinGreen 5
#define pinYellow 7
#define pinRed 6

// This variables will change:
volatile bool buttonState = LOW;         // current state of the button
volatile bool lastButtonState = LOW;     // previous state of the button
volatile uint8_t counter = 0;             // button click counter

// Instantiate a Button with a 5 millisecond debounce time
digitalPin Button(5, SWITCH);

// Instantiate 3 LED objects with on and off time in milliseconds
digitalPin ledGreen(pinGreen, 10, 5),
           ledYellow(pinYellow, 250, 250),
           ledRed(pinRed, 200, 200);

void setup() {
  // noop
}

// forever
void loop() {
  buttonState = Button.tread();
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    lastButtonState = buttonState;
    // increase counter only if button pressed
    if (buttonState == 1) counter++;
  }
  if (counter == 0) {
    ledGreen = HIGH;
    ledYellow = HIGH;
    ledRed = LOW;
  }
  if (counter == 1)  {
    ledRed = ledYellow + ledGreen;
    
  }
  if (counter == 2)  {
    ledRed = !ledRed;
    ledGreen = !ledGreen;
    ledYellow.flash();
  }
  if (counter == 3)  {
    ledGreen = LOW;
    ledYellow = LOW;
    ledRed = LOW;
  }
  if (counter == 4)  {
    ledGreen.flash(); // = HIGH;
    ledYellow = HIGH;
    ledRed = HIGH;
  }
  // reset counter
  if (counter > 4) counter = 0;
}
