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
const int potentLeftPin = ;  // the number of the pushbutton pin
const int potentRightPin = ;  // the number of the pushbutton pin

const int resetPin = ;

const int ledL1Pin = ;
const int ledL2Pin = ;

const int ledR1Pin = ;
const int ledR2Pin = ;

// variables will change:
int potentLState = 0;  // variable for reading the potentiometer status - will set a threshold for low/high
int potentRState = 0;  // variable for reading the potentiometer status

bool playing = false; // reset button sets this to true
int winner = 0; // 0 is no winner, 1 is left, 2 is right
bool canHit = false; //
bool leftTurn = true;
int randDelay = 0;

// time variables
unsigned long previousMillis = 0; // time the ball is hit
unsigned long currentMillis = 0;
unsigned long timeDiff = 0;
const long interval = 1000;  // interval at which to blink

// flicker winner's light
void hitToRight(int ledPin) {
    digitalWrite(ledPin, HIGH);
    delay(80);
    digitalWrite(ledPin, LOW);
    delay(80);
}

void hitToLeft() {
  currentMillis = millis();
  timeDiff = currentMillis - previousMillis;
  if (timeDiff < 200){
    digitalWrite(ledR2Pin, HIGH);
  }
  else if (timeDiff < 400){
    digitalWrite(ledR1Pin, HIGH);
  } else if (timeDiff < 600) {
    // LED SCREEN THING
  } else if (timeDiff < 800) {
    digitalWrite(ledL2Pin, HIGH);
  } else {
    digitalWrite(ledL1Pin, HIGH);
    previousMillis = millis();
    canHit = true;
  }
}

void hitToRight() {
  currentMillis = millis();
  timeDiff = currentMillis - previousMillis;
  if (timeDiff < 200){
    digitalWrite(ledL1Pin, HIGH);
  }
  else if (timeDiff < 400){
    digitalWrite(ledL2Pin, HIGH);
  } else if (timeDiff < 600) {
    // LED SCREEN THING
  } else if (timeDiff < 800) {
    digitalWrite(ledR1Pin, HIGH);
  } else {
    digitalWrite(ledR2Pin, HIGH);
    canHit = true;
  }
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
  // read the state of each potentiometer value:
  buttonLState = digitalRead(buttonLPin);
  buttonRState = digitalRead(buttonRPin);

  // check if the game has been reset - change this to button
  if (buttonLState == HIGH && buttonRState == HIGH) {
      playing = true;
      winner = 0;
      delay(15);
      digitalWrite(ledLPin, HIGH); //begin with left
  }
  while (playing){
    // get potentiometer values and threshold them
    buttonLState = digitalRead(buttonLPin);
    buttonRState = digitalRead(buttonRPin);
    

    // check which turn - if left, call hitToLeft
    if (leftTurn){
      hitToLeft();

    }
    


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
