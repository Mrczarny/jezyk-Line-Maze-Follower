#include <Arduino.h>

#define ROTATION_LEFT 3
#define ROTATION_RIGHT 2

#define COUNTER_INTERVAL 10

void leftRotationCheck();
void rightRotationCheck();

int _leftCount = 0;
int _rightCount = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ROTATION_LEFT, INPUT_PULLUP);
  pinMode(ROTATION_RIGHT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ROTATION_LEFT), leftRotationCheck, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTATION_RIGHT), rightRotationCheck, CHANGE);
}

void loop() {
  Serial.print("Left: ");
  Serial.println(_leftCount);
  Serial.print("Right: ");
  Serial.println(_rightCount);
  delay(1000);
}


void leftRotationCheck() {
  static unsigned long timer;
  static bool lastState;
  noInterrupts();
  if (millis() > timer) {
    bool state = digitalRead(ROTATION_LEFT);
    if (state != lastState) {
      _leftCount++;
      lastState = state;
    }
    timer = millis() + COUNTER_INTERVAL;
  }
  interrupts();
}

void rightRotationCheck() {
  static unsigned long timer;
  static bool lastState;
  noInterrupts();
  if (millis() > timer) {
    bool state = digitalRead(ROTATION_RIGHT);
    if (state != lastState) {
      _rightCount++;
      lastState = state;
    }
    timer = millis() + COUNTER_INTERVAL;
  }
  interrupts();
}
