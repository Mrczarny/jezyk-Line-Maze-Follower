#include <Arduino.h>
#include "movement.h"

#define LEFT_MOTOR_ROTATION 3            // left rotation sensor
#define RIGHT_MOTOR_ROTATION 2           // right rotation sensor
#define LEFT_SPEED_PIN 11                // left speed 
#define LEFT_DIRECTION_PIN 8            // left direction
#define RIGHT_SPEED_PIN 9                // right speed 
#define RIGHT_DIRECTION_PIN 12           // right direction

void setup()
{
  Serial.begin(9600);
  pinMode(LEFT_MOTOR_ROTATION, INPUT_PULLUP);
  pinMode(LEFT_DIRECTION_PIN, INPUT_PULLUP);
  pinMode(LEFT_DIRECTION_PIN, OUTPUT);
  pinMode(LEFT_SPEED_PIN, OUTPUT);
  pinMode(RIGHT_DIRECTION_PIN, OUTPUT);
  pinMode(RIGHT_SPEED_PIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(LEFT_MOTOR_ROTATION), leftRotationCheck, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RIGHT_MOTOR_ROTATION), rightRotationCheck, CHANGE);
  rotationStop();
  constWait();
}


void loop()
{
 rotationZeroLeft(100);
 rotationStop();
 constWait();
 rotationZeroRight(100);
 rotationStop();
 constWait();
 rotationBackward(100);
 rotationStop();
 constWait();
 rotationForward(100);
 rotationStop();
 constWait();
 motorLeftTurn(0, 0);
 rotationStop();
 constWait();
 motorRightTurn(0, 0);
 rotationStop();
 constWait();
 while(1);
 
}

