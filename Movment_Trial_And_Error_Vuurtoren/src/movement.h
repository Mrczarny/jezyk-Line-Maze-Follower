#ifndef MOVEMENT_H
#define movement.h

#include <Arduino.h>

void mFront(byte _left_speed, byte _right_speed);
void mBack(byte _left_speed, byte _right_speed);
void mLeft(byte _left_speed, byte _right_speed);
void mRight(byte _left_speed, byte _right_speed);
void mStop();
void ztLeft(byte _left_speed, byte _right_speed);
void ztRight(byte _left_speed, byte _right_speed);
void constWait();
void setLeftMotorSpeed(int speed);
void setRightMotorSpeed(int speed);

#endif 