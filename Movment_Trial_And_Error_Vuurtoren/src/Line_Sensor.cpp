//#define TEST

#ifdef TEST

#include <Arduino.h>
#include <movement.h>
#include <motors.h>
#include <line.h>
#include <rotation.h>
#include <sonar.h>


int linePins[] = {A0,A1,A2,A3,A4,A5,A6,A7};

Rotation rotation(3,2);
Motors motors(11,8,9,12);
Line line(8,linePins);
Sonar sonar(4,7);


void setup()
{
  motors.setup(0,0,255,255);
  rotation.setup(&motors,0,0);
  line.setup(700);
}


void lineFollow()
{
  lineSensorData d = line.readLine();
  for (int i = 0; i < 8; i++)
  {
   Serial.println(d.linePoints[i].isLine);
      if (d.linePoints[i].isLine)
     {
      rotation.moveForwardFor(1);
     }
     else if (d.linePoints[i].isLine = false)
     {
       motorStop();
     }
  }
  Serial.println();
  delay(1500);
}


void objectAvoid()
{
  while(sonar.getDistance() > 15)
  {
    motor.forward();
    distances();
    //record where bot has gone
    if(sonar.getDistance < 14)
    {
      motor.setLeftMotorSpeed(120);
      motor.setRightMotorSpeed(120);
    }
  }
  if(sonar.getDistance() < 8)
  {
    motor.stop();
    rotation.turnDegreesRight(180);
  }
}

#endif 