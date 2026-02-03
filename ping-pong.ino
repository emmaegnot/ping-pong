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

const int resetPin = D10;

const int ledL1Pin = D5;
const int ledL2Pin = D6;

const int ledR1Pin = D1;
const int ledR2Pin = D0;

const int buzzer = D9;

//TODO threshold for potentiometer
const int threshold = ;

// variables will change:
int potentLState = 0;  // variable for reading the potentiometer status - will set a threshold for low/high
int potentRState = 0;  // variable for reading the potentiometer status
int resetState = 0;

bool playing = false; // reset button sets this to true
int winner = 0; // 0 is no winner, 1 is left, 2 is right
bool canHit = false; //
bool leftTurn = true;

// time variables
unsigned long previousMillis = 0; // time the ball is hit
unsigned long currentMillis = 0;
unsigned long timeDiff = 0;
const long interval = 1000;  // interval at which to blink

// flicker winner's light
void flicker(int ledPin) {
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
    digitalWrite(ledR2Pin, LOW);

  } else if (timeDiff < 600) {
    // LED SCREEN THING
  } else if (timeDiff < 800) {
    digitalWrite(ledL2Pin, HIGH);
    digitalWrite(ledR1Pin, LOW);

  } else {
    digitalWrite(ledL2Pin, LOW);
    digitalWrite(ledL1Pin, HIGH);
    previousMillis = millis(); // reset timer
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
    digitalWrite(ledL1Pin, LOW);
    digitalWrite(ledL2Pin, HIGH);
  } else if (timeDiff < 600) {
    digitalWrite(ledL2Pin, LOW);
    // LED SCREEN THING
  } else if (timeDiff < 800) {
    digitalWrite(ledR1Pin, HIGH);
  } else {
    digitalWrite(ledR2Pin, HIGH);
    digitalWrite(ledR1Pin, LOW);
    previousMillis = millis();
    canHit = true;
  }
}



void setup() {
  // initialize the LED pin as an output:
  pinMode(ledL1Pin, OUTPUT);
  pinMode(ledL2Pin, OUTPUT);
  pinMode(ledR1Pin, OUTPUT);
  pinMode(ledR2Pin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(resetPin, INPUT);
}

void loop() {
  // read the state of each potentiometer value:
  potentLState = digitalRead(potentLeftPin);
  potentRState = digitalRead(potentRightPin);
  resetState = digitalRead(resetPin);

  // check if the game has been reset - change this to button
  if (resetState == HIGH) {
      playing = true;
      winner = 0;
      delay(15);
      leftTurn = true; //begin with left
  }

  while (playing){
    // get potentiometer values and threshold them
    potentLState = digitalRead(potentLeftPin);
    potentRState = digitalRead(potentRightPin);


    // check which turn - if left, call hitToLeft
    // this should only happen when canHit is false
    // if either potentiometer is high here, lose
    if (!canHit){
      if (potentLState > threshold){
        playing = false;
        winner = 2;
      } else if (potentRState > threshold){
        playing = false;
        winner = 1;
      }
      if (leftTurn){
        hitToLeft();
      } else {
        hitToRight();
      }
    } else {
      // once canHit is true, we need a new timer and detect if the hit has gone above the threshold
      // the funtion hitBall should be used for this
      if (leftTurn && (potentLState > threshold)) {
        // read left potentiometer and if higher than threshold 
        canHit = false;
        leftTurn = false;
        previousMillis = millis(); //reset timer

      } else if (!leftTurn && (potentRState > threshold)) {
        canHit = false;
        leftTurn = true;
        previousMillis = millis();

      }
    }
    


  }
  // game over
  //buzz
  if (winner == 1) {
    flicker(ledL1Pin);
  } else if (winner == 2) {
    flicker(ledR2Pin);
  }
  if (buttonRState == HIGH) {
    tone(buzzerPin, 100);
    delay(200);
    noTone(buzzerPin);
    delay(200);
}
}
