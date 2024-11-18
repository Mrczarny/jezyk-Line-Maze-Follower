#include <Arduino.h>
#include <movement.h>
// get rid of gllobal variables
// try to use static variable

// attach intterupt w change use a counter to intterupt and increment each intterupt -- ?
// debounce -- ?


void setup()
{
  mStop();
  constWait();
}


void loop()
{
 mFront();
 delay(3750); 
 mStop();
 mBack();
 delay(3750);
 mStop();
 mLeft();
 delay(2650);
 mStop();
 mRight();
 delay(4350);
 mStop();
 ztLeft();
 constWait();
 mStop();
 ztRight();
 constWait();
 mStop();
 while(1);
}
