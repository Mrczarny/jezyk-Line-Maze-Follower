#ifndef MOVEMENT_H
#define movement.h

#include <Arduino.h>


void motorForward(byte _left_speed, byte _right_speed);
void motorBackward(byte _left_speed, byte _right_speed);
void motorLeftTurn(byte _left_speed, byte _right_speed);
void motorRightTurn(byte _left_speed, byte _right_speed);
void motorStop();
void motorZeroLeft(byte _left_speed, byte _right_speed);
void motorZeroRight(byte _left_speed, byte _right_speed);
void constWait();
void setLeftMotorSpeed(int speed);
void setRightMotorSpeed(int speed);
void leftRotationCheck();
void rightRotationCheck();
void rotationZeroLeft(int distance, byte _left_speed, byte _right_speed);
void rotationZeroRight(int distance, byte _left_speed, byte _right_speed);
void rotationForward(int distance, byte _left_speed, byte _right_speed);
void rotationBackward(int distance, byte _left_speed, byte _right_speed);
void rotationLeftTurn(int distance, byte _left_speed, byte _right_speed);
void rotationRightTurn(int distance, byte _left_speed, byte _right_speed);
void rotationStop();

#endif 