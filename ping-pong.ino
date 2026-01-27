/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/digital/Button/
*/

#include <cstdlib>

// constants won't change. They're used here to set pin numbers:
const int buttonLPin = D9;  // the number of the pushbutton pin
const int buttonRPin = D8;  // the number of the pushbutton pin

const int ledLPin = D0;    // the number of the LED pin
const int ledRPin = D6;    // the number of the LED pin

// variables will change:
int buttonLState = 0;  // variable for reading the pushbutton status
int buttonRState = 0;  // variable for reading the pushbutton status

bool playing = false;
int winner = 0; // 0 is no winner, 1 is left, 2 is right
int light = 1; // 1 is left, 2 is right
int randDelay = 0;

// flicker winner's light
void flicker(int ledPin) {
    digitalWrite(ledPin, HIGH);
    delay(80);
    digitalWrite(ledPin, LOW);
    delay(80);
}


void setup() {
  // initialize the LED pin as an output:
  pinMode(ledLPin, OUTPUT);
  pinMode(ledRPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonLPin, INPUT);
  pinMode(buttonRPin, INPUT);
}

void loop() {
  // read the state of each pushbutton value:
  buttonLState = digitalRead(buttonLPin);
  buttonRState = digitalRead(buttonRPin);

  // check if the game has been reset
  if (buttonLState == HIGH && buttonRState == HIGH) {
      playing = true;
      winner = 0;
      delay(15);
      digitalWrite(ledLPin, HIGH); //begin with left
  }
  while (playing){
    buttonLState = digitalRead(buttonLPin);
    buttonRState = digitalRead(buttonRPin);
    randDelay = rand() % 1000 + 100;
    // the game has two states: the left light is on or the right
    if (light == 1) {

      // if correct button is pressed, swap LEDs
      if (buttonLState == HIGH) {
        digitalWrite(ledLPin, LOW);
        delay(randDelay);
        digitalWrite(ledRPin, HIGH);
        light = 2;
        // if the wrong player presses a button, they lose and the game ends
      } else if (buttonRState == HIGH) {
        playing = false;
        winner = 1;
      }

    } else {
      // if correct button is pressed, swap LEDs

      if (buttonRState == HIGH) {
        digitalWrite(ledRPin, LOW);
        delay(randDelay);
        digitalWrite(ledLPin, HIGH);
        light = 1;
      } else if (buttonLState == HIGH) {
        playing = false;
        winner = 2;
      }

    }

  }
  // game over
  if (winner == 1) {
    flicker(ledLPin);
  } else if (winner == 2) {
    flicker(ledRPin);
  }
}
