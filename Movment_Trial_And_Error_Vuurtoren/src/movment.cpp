#include <Arduino.h>
#include "movement.h"

#define A1_PIN 11                // left speed ~
#define A2_PIN 13                // left direction
#define B1_PIN 9                 // right speed ~
#define B2_PIN 12                // right direction
#define LEFT_MOTOR_ROTATION 3    // left rotation sensor (pin 3 to allow intterupt)
#define RIGHT_MOTOR_ROTATION 2   // right rotation sensor (pin 2 to allow interrupt)

#define COUNT_INTERVAL 10        // 10ms interval for interrupt
#define LEFt_MAX_SPEED 255       // maximum speed for left motor
#define RIGHT_MAX_SPEED 255      // maximum speed for right wheel

#define FORWARD HIGH             // TBD, but define forward as 1
#define BACKWARD LOW             // TBD, but define backward as 0


byte _left_speed = 127;          // byte speed to go from 0-255 set to 128 for base 50% left
byte _right_speed = 127;         // byte speed to go from 0-255 set to 127 for base 50% right

// back stop = 0 back full speed = 255
// front stop = 255 front full speed = 0

/// @brief Forward motion via dtermining direction and speed (speed can be changed in loop, 255 = stop, 0 = full speed)
void mFront(byte _left_speed, byte _right_speed)                    // xx
{
  digitalWrite(A2_PIN, FORWARD);      // direction of left motor
  analogWrite(A1_PIN, _left_speed);   // speed of left motor 
  digitalWrite(B2_PIN, FORWARD);      // direction of right motor
  analogWrite(B1_PIN, _right_speed);  // speed of right motor 
}

/// @brief Backward motion via determining direction and speed (speed can be changed in loop, 0 = stop, 255 = full speed)
void mBack(byte _left_speed, byte _right_speed)                     // xx
{
  digitalWrite(A2_PIN, BACKWARD);     // direction of left motor
  analogWrite(A1_PIN, _left_speed);   // speed of left motor 
  digitalWrite(B2_PIN, BACKWARD);     // direction of right motor
  analogWrite(B1_PIN, _right_speed);  // speed of right motor 
}

/// @brief Left hand turn via operating both wheels forward (speed can be changed in loop, 255 = stop, 0 = full speed)
void mLeft(byte _left_speed, byte _right_speed)                     // x
{
  digitalWrite(A2_PIN, FORWARD);       // direction of left motor
  analogWrite(A1_PIN, _left_speed);    // speed of left motor 
  digitalWrite(B2_PIN, FORWARD);       // direction of right motor
  analogWrite(B1_PIN, _right_speed);   // speed of right motor normal
}

/// @brief Right hand turn vi operating both wheels forward (speed can be changed in loop, 255 = stop, 0 = full speed)
void mRight(byte _left_speed, byte _right_speed)                    // x
{
  digitalWrite(A2_PIN, FORWARD);       // direction of left motor
  analogWrite(A1_PIN, _left_speed);    // speed of left motor normal 
  digitalWrite(B2_PIN, FORWARD);       // direction of right motor
  analogWrite(B1_PIN, _right_speed);   // speed of right motor
}


/// @brief Full stop (halt all motors(direction is unimportant, but for back stop = 0, for front stop = 255))
void mStop()                     // xx
{
  digitalWrite(A2_PIN, BACKWARD); // direction of left motor
  analogWrite(A1_PIN, 0);         // speed of left motor 
  digitalWrite(B2_PIN, BACKWARD); // direction of right motor
  analogWrite(B1_PIN, 0);         // speed of right motor 
}

/// @brief Rotate Left on center axis by Left wheel backward and Right wheel forward (speed of rotation taken as arguments in loop, back full = 255, front full = 0)
void ztLeft(byte _left_speed, byte _right_speed)                    // xx
{
  digitalWrite(A2_PIN, BACKWARD);      // direction of left motor
  analogWrite(A1_PIN, _left_speed);    // speed of left motor
  digitalWrite(B2_PIN, FORWARD);       // direction of right motor
  analogWrite(B1_PIN, _right_speed);   // speed of right motor
}

/// @brief Rotate right on center axis by Left wheel forward and Right wheel backward (speed of rotation taken as arguments in loop, back full = 255, front full = 0)
void ztRight(byte _left_speed, byte _right_speed)                   // xx
{
  digitalWrite(A2_PIN, FORWARD);       // direction of left motor
  analogWrite(A1_PIN, _left_speed);    // speed of left motor
  digitalWrite(B2_PIN, BACKWARD);      // direction of right motor
  analogWrite(B1_PIN, _right_speed);   // speed of right motor
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
    analogWrite(A1_PIN, _left_speed);    // update PWM output left motor
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
    analogWrite(B1_PIN, _right_speed);    // update PWM output left motor
    Serial.print("Right Speed Set to: ");
    Serial.println(_right_speed);
  }
}

