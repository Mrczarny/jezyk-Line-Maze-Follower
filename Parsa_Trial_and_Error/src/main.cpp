#include <Arduino.h>
#include <math.h>

#define LEFT_MOTOR_ROTATION 3    // left rotation sensor (pin 3 to allow intterupt)
#define RIGHT_MOTOR_ROTATION 2   // right rotation sensor (pin 2 to allow interrupt)

const int MOTOR_A_2 = 8; // left wheel forward
const int MOTOR_A_1 = 11; // left wheel digital
const int MOTOR_B_2 = 12;  // right wheel forward
const int MOTOR_B_1 = 9;  // right wheel digital

#define COUNTER_INTERVAL 10

void leftRotationCheck();
void rightRotationCheck();
void moveForward(int distance);
void fullStop();

int _leftCount = 0;
int _rightCount = 0;

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_A_2, OUTPUT);
  pinMode(MOTOR_A_1, OUTPUT);
  pinMode(MOTOR_B_2, OUTPUT);
  pinMode(MOTOR_B_1, OUTPUT);
  pinMode(LEFT_MOTOR_ROTATION, INPUT_PULLUP);
  pinMode(RIGHT_MOTOR_ROTATION, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LEFT_MOTOR_ROTATION), leftRotationCheck, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RIGHT_MOTOR_ROTATION), rightRotationCheck, CHANGE);
}

void loop() {
  moveForward(100);
  fullStop();
  while(1);
}

void leftRotationCheck() {
  static unsigned long timer;
  static bool lastState;
  noInterrupts();
  if (millis() > timer) {
    bool state = digitalRead(LEFT_MOTOR_ROTATION);
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
    bool state = digitalRead(RIGHT_MOTOR_ROTATION);
    if (state != lastState) {
      _rightCount++;
      lastState = state;
    }
    timer = millis() + COUNTER_INTERVAL;
  }
  interrupts();
}

void moveForward(int distance) {
  _leftCount = 0;
  _rightCount = 0;
  int pulses = round(distance / 17.0 * 40);
  while (_leftCount <= pulses && _rightCount <= pulses)
  {
    Serial.println("pulses:");
    Serial.println(pulses);
    Serial.println("left:");
    Serial.println(_leftCount);
    Serial.println("right:");
    Serial.println(_rightCount);
    digitalWrite(MOTOR_A_2, HIGH);
    analogWrite(MOTOR_A_1, 0);
    digitalWrite(MOTOR_B_1, HIGH);
    analogWrite(MOTOR_B_2, 0);
  }
}

void fullStop() {
  digitalWrite(MOTOR_A_2, LOW);
  analogWrite(MOTOR_B_1, 0);
  digitalWrite(MOTOR_B_1, LOW);
  analogWrite(MOTOR_B_2, 0);
}