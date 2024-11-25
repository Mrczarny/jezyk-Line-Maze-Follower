// Rotation sensors
// 
#include <Arduino.h>
#include "movement.h"
#include <motors.h>

#define LEFT_MOTOR_ROTATION 3            // left rotation sensor
#define RIGHT_MOTOR_ROTATION 2           // right rotation sensor
#define LEFT_SPEED_PIN 11                // left speed 
#define LEFT_DIRECTION_PIN 13            // left direction
#define RIGHT_SPEED_PIN 9                // right speed 
#define RIGHT_DIRECTION_PIN 12           // right direction
#define LEFt_MAX_SPEED 255               // maximum speed for left motor
#define RIGHT_MAX_SPEED 255              // maximum speed for right wheel
#define FORWARD HIGH                     // but define forward as 1
#define BACKWARD LOW                     // define backward as 0
#define PI 3.14159265358979323846264338327950288419716939937510

#define COUNT_INTERVAL 10                // 10ms interval for interrupt

int _leftCount = 0;                      // variable to update left count
int _rightCount = 0;                     // variable to update right count
  #define _wheelC (5.4*PI)                // wheel circumfrence
byte _left_speed = 127;                  // byte speed to go from 0-255 set to 128 for base 50% left
byte _right_speed = 127;                 // byte speed to go from 0-255 set to 127 for base 50% right

int steps[5]={10,20,30,40,50};           // approx cm to travel

Motors motor(11,13,9,12);

             

// back stop = 0 back full speed = 255
// front stop = 255 front full speed = 0

// circumfrence of the wheel / 40 gives us the pulse length
// circumfrence is 17 cm / 40 = 0.425 cm per pulse
// determine # of pulses passed, tell left and right certain # of pulses

void leftRotationCheck()
{
  static unsigned long timer;
  static bool lastState;
  noInterrupts();
  if (millis() > timer) 
  {
    bool state = digitalRead(LEFT_MOTOR_ROTATION);
        if (state != lastState) 
        {
        _leftCount++;
        Serial.print('l');
        Serial.print(_leftCount);
        Serial.println();
        lastState = state;
        }
    timer = millis() + COUNT_INTERVAL;
  }
  interrupts();
}

void rightRotationCheck()
{
  static unsigned long timer;
  static bool lastState;
  noInterrupts();
  if (millis() > timer) 
  {
    bool state = digitalRead(RIGHT_MOTOR_ROTATION);
        if (state != lastState) 
        {
        _rightCount++;
        Serial.print('r');
        Serial.print(_rightCount);
        Serial.println();
        lastState = state;
        }
    timer = millis() + COUNT_INTERVAL;
  }
  interrupts();
}

void rotationZeroLeft(int distance,)
{
    rotationStop();

    noInterrupts();
    _leftCount = 0;
    _rightCount = 0;
    interrupts();

    int rotations = distance / _wheelC;
    while(_leftCount/40 <= rotations && _rightCount/40 <= rotations)
    {
      motorZeroLeft(255, 0);    
    }
    rotationStop();
}

void rotationZeroRight(float distance)
{
    rotationStop();
    _leftCount = 0;
    _rightCount = 0;
    int rotations = distance / _wheelC;
    while(_leftCount <= rotations && _rightCount <= rotations)
    {
     motorZeroRight(0, 255);
    }
}

void rotationForward(float distance)
{
    rotationStop();
    _leftCount = 0;
    _rightCount = 0;
    int rotations = distance / _wheelC;
    while(_leftCount/40 <= rotations && _rightCount/40 <= rotations)
    {
      motorForward(0, 0);
    }
}

void rotationBackward(float distance)
{
    rotationStop();
    _leftCount = 0;
    _rightCount = 0;
    int rotations = distance / _wheelC;
    while(_leftCount <= rotations && _rightCount <= rotations)
    {
     motorBackward(255, 255);
    }
}

void rotationLeftTurn(float distance)
{
    rotationStop();
    _leftCount = 0;
    _rightCount = 0;
    int rotations = distance / _wheelC;
    while(_leftCount <= rotations && _rightCount <= rotations)
    {
     motorLeftTurn(255, 255);
    }
}

void rotationRightTurn(float distance)
{
    rotationStop();
    _leftCount = 0;
    _rightCount = 0;
    int rotations = distance / _wheelC;
    while(_leftCount <= rotations && _rightCount <= rotations)
    {
     motorZeroRight(255,255);
    }
}

void rotationStop()
{
    motorStop();
}
    

void setLeftMotorSpeed(int speed)
{
  if (speed >= 0 && speed <= 255)
  {
    _left_speed = speed;                 // set the left motor speed
    analogWrite(LEFT_SPEED_PIN, _left_speed);    // update PWM output left motor
    Serial.print("Left Speed Set to: ");
    Serial.println(_left_speed);
  }
}

/// @brief Set right motor speed according to speed byte base 50% (can be used in loop to adjust speed during runtime)
/// @param _speed 
void setRightMotorSpeed(int speed)
{
  if (speed >= 0 && speed <= 255)
  {
    _right_speed = speed;                 // set the right motor speed
    analogWrite(RIGHT_SPEED_PIN, _right_speed);    // update PWM output left motor
    Serial.print("Right Speed Set to: ");
    Serial.println(_right_speed);
  }
}
