#include <Arduino.h>
#include "movement.h"
#include <rotation.h>
#include <motors.h>
#include <line.h>
#include <sonar.h>

#define MOVETEST

#define LEFT_MOTOR_ROTATION 3            // left rotation sensor 3
#define RIGHT_MOTOR_ROTATION 2           // right rotation sensor 2
#define LEFT_SPEED_PIN 11                // left speed A1 11
#define LEFT_DIRECTION_PIN 8             // left direction A2 8
#define RIGHT_SPEED_PIN 9                // right speed B1 9
#define RIGHT_DIRECTION_PIN 12           // right direction B2 12
#define SONAR_ECHO_PIN 7                 // sonar echo
#define SONAR_TRIGGER_PIN 4              // sonar trigger
#define LEFT_MAX_SPEED 255               // maximum speed for left motor
#define RIGHT_MAX_SPEED 255              // maximum speed for right wheel
#define PI 3.141592
#define FORWARD HIGH             // TBD, but define forward as 1
#define BACKWARD LOW             // TBD, but define backward as 0


// #define COUNT_INTERVAL 10                // 10ms interval for interrupt

// volatile static int _leftCount = 0;                      // variable to update left count
// volatile static int _rightCount = 0;                     // variable to update right count
byte _left_speed = 127;          // byte speed to go from 0-255 set to 128 for base 50% left
byte _right_speed = 127;         // byte speed to go from 0-255 set to 127 for base 50% right


int linePins[] = {A0,A1,A2,A3,A4,A5,A6,A7};
Rotation rotation(3,2);
Motors motors(11,8,9,12);
Line line(8,linePins);
Sonar sonar(4,7);
lineSensorData lineState;

// function prototypes
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
void rotationZeroLeft(float distance);
void rotationZeroRight(float distance);
void rotationForward(float distance);
void rotationBackward(float distance);
void rotationLeftTurn(float distance);
void rotationRightTurn(float distance);
void rotationStop();
void rotationLeftTurnFix(float distance);
void lineFollow();
void objectAvoid();


void setup()
{
  Serial.begin(9600);
  pinMode(SONAR_ECHO_PIN, INPUT);
  pinMode(SONAR_TRIGGER_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_ROTATION, INPUT_PULLUP);
  pinMode(LEFT_DIRECTION_PIN, INPUT_PULLUP);
  pinMode(LEFT_DIRECTION_PIN, OUTPUT);
  pinMode(LEFT_SPEED_PIN, OUTPUT);
  pinMode(RIGHT_DIRECTION_PIN, OUTPUT);
  pinMode(RIGHT_SPEED_PIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(LEFT_MOTOR_ROTATION), leftRotationCheck, CHANGE);
  attachInterrupt(digitalPinToInterrupt(RIGHT_MOTOR_ROTATION), rightRotationCheck, CHANGE);
  rotationStop();
  constWait();
  motors.setup(0,0,255,255);
  rotation.setup(&motors,0,0);
  line.setup(700);
}

int intersection[8] = {1, 1, 1, 1, 1, 1, 1, 1};
int left[8] = {0, 0, 0, 0, 1, 1, 1, 1};
int right[8] = {1, 1, 1, 1, 0, 0, 0, 0};
bool compareArray(int array1[], int array2[]) {
  bool equal = true;
  for (int i = 0; i < 8; i++)
  {
    if (array1[i] != array2[i])
    {
      equal = false;
    }
  }
  return equal;
}

void loop() {
  lineState = line.readLine();
  int state[8];
  for (int i = 0; i < 8; i++)
  {
    if (lineState.linePoints[i].isLine == true)
    {
      state[i] = 1;
    }
    else
    {
      state[i] = 0;
    }
  }
  if (state[0] == 1 || state[1] == 1)
  {
    rotation.turnDegreesRight(5);
  }
  else if (state[6] == 1 || state[7] == 1)
  {
    rotation.turnDegreesRight(5);
  }
  else if (state[0] == 0 && state[1] == 0 && state[2] == 0 && state[3] == 0 && state[4] == 0 && state[5] == 0 && state[6] == 0 && state[7] == 0)
  {
    motors.stop();
  }
  else
  {
    motors.forward(1);
  }
}



// movement.cpp
/// @brief Forward motion via dtermining direction and speed (speed can be changed in loop, 255 = stop, 0 = full speed)
void motorForward(byte _left_speed, byte _right_speed)                    // xx
{
  //static unsigned long timer;
  //if (millis() > timer)
  //{
    digitalWrite(LEFT_DIRECTION_PIN, FORWARD);          // direction of left motor
    analogWrite(LEFT_SPEED_PIN, _left_speed);       // speed of left motor 
    digitalWrite(RIGHT_DIRECTION_PIN, FORWARD);         // direction of right motor
    analogWrite(RIGHT_SPEED_PIN, _right_speed);         // speed of right motor 
  //}
  //timer = millis()+500;
}

/// @brief Backward motion via determining direction and speed (speed can be changed in loop, 0 = stop, 255 = full speed)
void motorBackward(byte _left_speed, byte _right_speed)                     // xx
{
  //static unsigned long timer;
  //if (millis() > timer)
  //{
    digitalWrite(LEFT_DIRECTION_PIN, BACKWARD);     // direction of left motor
    analogWrite(LEFT_SPEED_PIN, _left_speed);   // speed of left motor 
    digitalWrite(RIGHT_DIRECTION_PIN, BACKWARD);     // direction of right motor
    analogWrite(RIGHT_SPEED_PIN, _right_speed);  // speed of right motor 
  //}
  //timer = millis() + 500;
}

/// @brief Left hand turn via operating both wheels forward (speed can be changed in loop, 255 = stop, 0 = full speed)
void motorLeftTurn(byte _left_speed, byte _right_speed)                     // x
{
  //static unsigned long timer;
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
  //static unsigned long timer;
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
  //static unsigned long timer;
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
  //static unsigned long timer;
  //if (millis() > timer)
  //{
    digitalWrite(LEFT_DIRECTION_PIN, BACKWARD);      // direction of left motor
    analogWrite(LEFT_SPEED_PIN, _left_speed);    // speed of left motor
    digitalWrite(RIGHT_DIRECTION_PIN, FORWARD);       // direction of right motor
    analogWrite(RIGHT_SPEED_PIN, _right_speed);   // speed of right motors
  //}
  //timer = millis()+500;
}

/// @brief Rotate right on center axis by Left wheel forward and Right wheel backward (speed of rotation taken as arguments in loop, back full = 255, front full = 0)
void motorZeroRight(byte _left_speed, byte _right_speed)                   // xx
{
  //static unsigned long timer;
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

#ifdef MOVETEST

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

#endif

// Rotation_Sensor.cpp

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
        lastState = state;
        }
    timer = millis() + 10;
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
        lastState = state;
        }
    timer = millis() + 10;
  }
  interrupts();
}

void rotationZeroLeft(float distance)
{
    static unsigned long timer;
    _leftCount = 0;
    _rightCount = 0;
    int rotations = round(distance / 17 * 40);
    Serial.print("Target Rotations: ");
    Serial.println(rotations);
  if (millis() > timer)
  {
    while(_leftCount <= rotations && _rightCount <= rotations)
    {
      motorZeroLeft(255, 0); 
       Serial.print("Left count: ");
       Serial.println(_leftCount);
       Serial.print("Right count: ");
       Serial.println(_rightCount);   
    }
    timer = millis()+500;
  }
  rotationStop();
  Serial.println("Target reached. Stopping motors.");
}

void rotationZeroRight(float distance)
{
  static unsigned long timer;
  _leftCount = 0;
  _rightCount = 0;
  int rotations = round(distance / 17 * 40);
  Serial.print("Target Rotations: ");
  Serial.println(rotations);
  if (millis() > timer)
  {
    int rotations = round(distance / 17 * 40);
    while(_leftCount <= rotations && _rightCount <= rotations)
      {
       motorZeroRight(0, 255);
       Serial.print("Left count: ");
       Serial.println(_leftCount);
       Serial.print("Right count: ");
       Serial.println(_rightCount);
      }
    timer = millis()+500;
  }
  rotationStop();
  Serial.println("Target reached. Stopping motors.");
}

void rotationForward(float distance)
{
  static unsigned long timer;
  _leftCount = 0;
  _rightCount = 0;
  int rotations = round(distance / 17 * 40);
  Serial.print("Target Rotations: ");
  Serial.println(rotations);
  if (millis() > timer)
  {
    while(_leftCount <= rotations && _rightCount <= rotations)
      {
        motorForward(0, 0);
        Serial.print("Left count: ");
        Serial.println(_leftCount);
        Serial.print("Right count: ");
        Serial.println(_rightCount);
      }
    timer = millis()+500;
  }
  rotationStop();
  Serial.println("Target reached. Stopping motors.");
}

void rotationBackward(float distance)
{
  static unsigned long timer;
  _leftCount = 0;
  _rightCount = 0;
  int rotations = round(distance / 17 * 40);
  Serial.print("Target Rotations: ");
  Serial.println(rotations);
  if (millis() > timer)
  {
    while(_leftCount <= rotations && _rightCount <= rotations)
      {
       motorBackward(255, 255);
       Serial.print("Left count: ");
       Serial.println(_leftCount);
       Serial.print("Right count: ");
       Serial.println(_rightCount);
      }
    timer = millis()+500;
  }
  rotationStop();
  Serial.println("Target reached. Stopping motors.");
}


void rotationLeftTurnFix(float distance)
{
  static unsigned long timer;
  int rotations = (distance / _wheelC) * 40;
  int leftRotations = _leftCount + rotations;
  int rightRotations = _rightCount + rotations;

  if (millis() > timer)
  {
    while ((_leftCount < leftRotations) && (_rightCount < rightRotations))
    {
      motorForward(69,0);
      Serial.print("Left count: ");
      Serial.println(_leftCount);
      Serial.print("Right count: ");
      Serial.println(_rightCount);
    }
    timer = millis() + COUNT_INTERVAL;
  }
  rotationStop();
}

void rotationLeftTurn(float distance)
{    
  static unsigned long timer;
  _leftCount = 0;
  _rightCount = 0;
  int rotations = round(distance / 17 * 40);
  //Serial.print("Target Rotations: ");
  //Serial.println(rotations);
  if (millis() > timer)
  {
    while(_leftCount < rotations && _rightCount < rotations)
      {
       motorForward(50, 0);
       Serial.print("Left count: ");
       Serial.println(_leftCount);
       Serial.print("Right count: ");
       Serial.println(_rightCount);
      }
      
    timer = millis()+500;
  }
  rotationStop();
  Serial.println("Target reached. Stopping motors.");
}

void rotationRightTurn(float distance)
{
  static unsigned long timer;
  _leftCount = 0;
  _rightCount = 0;
  int rotations = round(distance / 17 * 40);
  Serial.print("Target Rotations: ");
  Serial.println(rotations);
  if (millis() > timer)
  {
    while(_leftCount <= rotations && _rightCount <= rotations)
     {
       motorForward(0,50);
       //Serial.print("Left count: ");
       //Serial.println(_leftCount);
       //Serial.print("Right count: ");
       //Serial.println(_rightCount);
     }
    timer = millis()+500;
  }
  rotationStop();
  Serial.println("Target reached. Stopping motors.");
}

void rotationStop()
{
    motorStop();
    //timer = millis()+500;
}

void lineFollow()
{
  lineSensorData d = line.readLine();
  for (int i = 0; i < 8; i++)
  {
   Serial.println(d.linePoints[i].isLine);
      if (d.linePoints[i].isLine)
     {
      rotation.moveForwardFor(10);
     }
     else if (d.linePoints[i].isLine == false)
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
    motors.forward();
    sonar.getDistance();
    //record where bot has gone
    if(sonar.getDistance() < 14)
    {
      motors.setLeftMotorSpeed(120);
      motors.setRightMotorSpeed(120);
    }
  }
  if(sonar.getDistance() < 8)
  {
    motors.stop();
    rotation.turnDegreesRight(180);
  }
}
