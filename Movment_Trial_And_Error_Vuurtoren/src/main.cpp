#include <Arduino.h>
#include "movement.h"

#define LEFT_MOTOR_ROTATION 3            // left rotation sensor
#define RIGHT_MOTOR_ROTATION 2           // right rotation sensor
#define LEFT_SPEED_PIN 11                // left speed 
#define LEFT_DIRECTION_PIN 13            // left direction
#define RIGHT_SPEED_PIN 9                // right speed 
#define RIGHT_DIRECTION_PIN 12           // right direction

void setup()
{
  Serial.begin(9600);
  pinMode(LEFT_MOTOR_ROTATION, INPUT_PULLUP);
  pinMode(LEFT_DIRECTION_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LEFT_MOTOR_ROTATION), leftRotationCheck, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RIGHT_MOTOR_ROTATION), rightRotationCheck, CHANGE);
  rotationStop();
  constWait();
}


void loop()
{
  
 rotationForward(30, 0, 0);
//  rsStop();
//  delay(5000);
 /*
 constWait();
 rsZTRight(100, 0, 255);
 rsStop();
 constWait();
 rsBackward(100, 255, 255);
 rsStop();
 constWait();
 rsForward(100, 0, 0);
 rsStop();
 constWait();
 rsLeftTurn(100, 0, 0);
 rsStop();
 constWait();
 rsRightTurn(100, 255, 255);
 rsStop();
 constWait();
 while(1);
 */
}

