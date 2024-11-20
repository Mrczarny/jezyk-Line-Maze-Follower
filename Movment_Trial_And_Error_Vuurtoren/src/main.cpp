#include <Arduino.h>
#include "movement.h"

#define A1_PIN 11      // left speed ~
#define A2_PIN 13      // left direction
#define B1_PIN 9       // right speed ~
#define B2_PIN 12      // right direction

void setup()
{
  Serial.begin(9600);
  pinMode(A1_PIN, OUTPUT);
  pinMode(A2_PIN, OUTPUT);
  pinMode(B1_PIN, OUTPUT);
  pinMode(B2_PIN, OUTPUT);
  mStop();
  constWait();
}


void loop()
{
  // forward 0 = full speed 255 = stop
  // backward 255 = full speed 0 = stop
 mFront(0, 0);
 delay(3750); 
 mStop();
 mBack(255, 255);
 delay(3750);
 mStop();
 mLeft(100, 0);
 delay(2650);
 mStop();
 mRight(0, 100);
 delay(4350);
 mStop();
 ztLeft(255, 0);
 constWait();
 mStop();
 ztRight(0, 255);
 constWait();
 mStop();
 while(1); 
}
