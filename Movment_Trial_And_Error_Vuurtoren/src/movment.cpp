#include <Arduino.h>
#include <movement.h>
#define A1_PIN 11
#define A2_PIN 10
#define B1_PIN 6
#define B2_PIN 5

// get rid of gllobal variables
// try to use static variable

// attach intterupt w change use a counter to intterupt and increment each intterupt -- ?
// debounce -- ?


void mFront()                    // x
{
  analogWrite(A2_PIN, 205);      // left forward
  analogWrite(B2_PIN, 246);      // right forward
  analogWrite(A1_PIN, 0);        // left back
  analogWrite(B1_PIN, 0);        // right back
}


void mBack()                     // x
{
  analogWrite(A2_PIN, 0);        // l f
  analogWrite(B2_PIN, 0);        // r f
  analogWrite(A1_PIN, 196);      // l b
  analogWrite(B1_PIN, 249);      // r b
}

void mLeft()                     // x
{
  analogWrite(A2_PIN, 160);      // l f
  analogWrite(B2_PIN, 255);      // r f
  analogWrite(A1_PIN, 0);        // l b
  analogWrite(B1_PIN, 0);        // r b
}


void mRight()                    // x
{
  analogWrite(A2_PIN, 255);      // l f
  analogWrite(B2_PIN, 200);      // r f
  analogWrite(A1_PIN, 0);        // l b
  analogWrite(B1_PIN, 0);        // r b
}


void mStop()                     // x
{
  analogWrite(A1_PIN, 0);        // l b 
  analogWrite(B1_PIN, 0);        // r b
  analogWrite(A2_PIN, 0);        // l f
  analogWrite(B2_PIN, 0);        // r f
  constWait();
}

void ztLeft()                    // x
{
  analogWrite(A1_PIN, 200);      // l b
  analogWrite(B2_PIN, 200);      // r f
  analogWrite(A2_PIN, 0);        // l f
  analogWrite(B1_PIN, 0);        // r b
}

void ztRight()                   // x
{
  analogWrite(A2_PIN, 200);      // l f
  analogWrite(B1_PIN, 200);      // r b
  analogWrite(A1_PIN, 0);        // l b
  analogWrite(B2_PIN, 0);        // r f
}

void constWait()
{
  delay(2250);
}

// make wheel functions?
// figure out rotation sensors instead of setting speed every time


// display sonar pings to ditect objects
// check for return pings
// route around the object
// continue down the path
