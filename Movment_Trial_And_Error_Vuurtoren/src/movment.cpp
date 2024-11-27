#include <Arduino.h>
#include "movement.h"

#define LEFT_SPEED_PIN 11                // left speed ~
#define LEFT_DIRECTION_PIN 8            // left direction
#define RIGHT_SPEED_PIN 9                // right speed ~
#define RIGHT_DIRECTION_PIN 12           // right direction
#define LEFT_MOTOR_ROTATION 3    // left rotation sensor (pin 3 to allow intterupt)
#define RIGHT_MOTOR_ROTATION 2   // right rotation sensor (pin 2 to allow interrupt)

#define FORWARD HIGH             // TBD, but define forward as 1
#define BACKWARD LOW             // TBD, but define backward as 0


byte _left_speed = 127;          // byte speed to go from 0-255 set to 128 for base 50% left
byte _right_speed = 127;         // byte speed to go from 0-255 set to 127 for base 50% right

// back stop = 0 back full speed = 255
// front stop = 255 front full speed = 0

/// @brief Forward motion via dtermining direction and speed (speed can be changed in loop, 255 = stop, 0 = full speed)
void motorForward(byte _left_speed, byte _right_speed)                    // xx
{
  //if (millis() > timer)
  //{
    digitalWrite(LEFT_DIRECTION_PIN, FORWARD*0.9);          // direction of left motor
    analogWrite(LEFT_SPEED_PIN, _left_speed);       // speed of left motor 
    digitalWrite(RIGHT_DIRECTION_PIN, FORWARD);         // direction of right motor
    analogWrite(RIGHT_SPEED_PIN, _right_speed);         // speed of right motor 
  //}
  //timer = millis()+500;
}

/// @brief Backward motion via determining direction and speed (speed can be changed in loop, 0 = stop, 255 = full speed)
void motorBackward(byte _left_speed, byte _right_speed)                     // xx
{
  //if (millis() > timer)
  //{
    digitalWrite(LEFT_DIRECTION_PIN, BACKWARD*0.9);     // direction of left motor
    analogWrite(LEFT_SPEED_PIN, _left_speed);   // speed of left motor 
    digitalWrite(RIGHT_DIRECTION_PIN, BACKWARD);     // direction of right motor
    analogWrite(RIGHT_SPEED_PIN, _right_speed);  // speed of right motor 
  //}
  //timer = millis() + 500;
}

/// @brief Left hand turn via operating both wheels forward (speed can be changed in loop, 255 = stop, 0 = full speed)
void motorLeftTurn(byte _left_speed, byte _right_speed)                     // x
{
  //if (millis() > timer)
  //{
    digitalWrite(LEFT_DIRECTION_PIN, FORWARD);       // direction of left motor
    analogWrite(LEFT_SPEED_PIN, _left_speed*0.65);    // speed of left motor 
    digitalWrite(RIGHT_DIRECTION_PIN, FORWARD);       // direction of right motor
    analogWrite(RIGHT_SPEED_PIN, _right_speed);   // speed of right motor normal
  //}
  //timer = millis()+500;
}

/// @brief Right hand turn vi operating both wheels forward (speed can be changed in loop, 255 = stop, 0 = full speed)
void motorRightTurn(byte _left_speed, byte _right_speed)                    // x
{
  //if (millis() > timer)
  //{
    digitalWrite(LEFT_DIRECTION_PIN, FORWARD);        // direction of left motor
    analogWrite(LEFT_SPEED_PIN, _left_speed);         // speed of left motor normal 
    digitalWrite(RIGHT_DIRECTION_PIN, FORWARD);       // direction of right motor
    analogWrite(RIGHT_SPEED_PIN, _right_speed*0.65);   // speed of right motor
  //}
  //timer = millis()+500;
}


/// @brief Full stop (halt all motors(direction is unimportant, but for back stop = 0, for front stop = 255))
void motorStop()                     // xx
{
  //if (millis() > timer)
  //{
    digitalWrite(LEFT_DIRECTION_PIN, BACKWARD); // direction of left motor
    analogWrite(LEFT_SPEED_PIN, 0);         // speed of left motor 
    digitalWrite(RIGHT_DIRECTION_PIN, BACKWARD); // direction of right motor
    analogWrite(RIGHT_SPEED_PIN, 0);         // speed of right motor 
  //}
  //timer = millis()+500;
}
  

/// @brief Rotate Left on center axis by Left wheel backward and Right wheel forward (speed of rotation taken as arguments in loop, back full = 255, front full = 0)
void motorZeroLeft(byte _left_speed, byte _right_speed)                    // xx
{
  //if (millis() > timer)
  //{
    digitalWrite(LEFT_DIRECTION_PIN, BACKWARD);      // direction of left motor
    analogWrite(LEFT_SPEED_PIN, _left_speed);    // speed of left motor
    digitalWrite(RIGHT_DIRECTION_PIN, FORWARD);       // direction of right motor
    analogWrite(RIGHT_SPEED_PIN, _right_speed);   // speed of right motor
  //}
  //timer = millis()+500;
}

/// @brief Rotate right on center axis by Left wheel forward and Right wheel backward (speed of rotation taken as arguments in loop, back full = 255, front full = 0)
void motorZeroRight(byte _left_speed, byte _right_speed)                   // xx
{
  //if (millis() > timer)
  //{
    digitalWrite(LEFT_DIRECTION_PIN, FORWARD);       // direction of left motor
    analogWrite(LEFT_SPEED_PIN, _left_speed);    // speed of left motor
    digitalWrite(RIGHT_DIRECTION_PIN, BACKWARD);      // direction of right motor
    analogWrite(RIGHT_SPEED_PIN, _right_speed);   // speed of right motor
  //}
  //timer = millis()+500;
}

/// @brief Universal Delay (for testing purposes only)
void constWait()
{
  delay(2250);
}


/// @brief Set Left motor speed according to speed byte base 50% (can be used in loop to adjust speed during runtime)
/// @param _speed 
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

