#include <Arduino.h>
#include <motors.h>
#include <line.h>
// #include <sonar.h>
#include <rotation.h>
#include <string.h>

#define A1_PIN 6
#define A2_PIN 7
#define B1_PIN 4
#define B2_PIN 5

int Find(uint8_t arr[], uint8_t x);
boolean tryFindLine();

int linePins[] = {A0, A1, A2, A3, A4, A5, A6, A7};
Motors motors(A1_PIN, A2_PIN, B2_PIN, B1_PIN);
Line line(8, linePins);
// Sonar sonar(9, 10);
Rotation rotation(2, 3);
uint8_t lineForward[] = {
  0b00011000,
  0b01110000,
  0b00110000,
  0b01100000,
  0b11000000,
  0b00111000,
  0b00001100,
  0b00001110,
  0b00000110,
  0b00000011,
  0b00011100
};

static int lastTime = 0;

static int ignoreLeft = 0;
static int ignoreRight = 0;
static int ignoreForward = 0;
static int ignoreNoLine = 0;

static lineSensorData lineState;

void setup()
{
  // put your setup code here, to run once:
  motors.setup(
      32, 32, 216, 216);
  // motors.setup(20, 20, 240, 240);
  Serial.begin(9600);
  line.setup(700);
  lineState = line.readLine();
  rotation.setup(&motors, 0, 0);
  // Serial.println("setup");
}


void loop()
{
  lineState = line.readLine();
  uint8_t decimal = convertToBinary(lineState);
    // for (size_t i = 0; i < 8; i++)
    // {
    //   Serial.print(lineState.linePoints[i].sensorValue);
    //   Serial.print(" ");
    // }
    // Serial.println();
  switch (decimal)
  {
  default:
    // Serial.print("unknown state: ");
    // for (size_t i = 0; i < 8; i++)
    // {
    //   Serial.print(lineState.linePoints[i].isLine);
    // }
    // Serial.println();
    break;

  case 0b00011000:
    Serial.print("forward ");
    Serial.println();
    motors.forward();
    break;

  // case 0b01110000:
  case 0b00110000:
  case 0b01100000:
  case 0b11000000:
  case 0b00111000:
  //case 0b00010000:
    Serial.print("zeroLeft ");
    Serial.println();
    motors.zeroLeft();
    break;

  case 0b00001100:
  case 0b00001110:
  case 0b00000110:
  case 0b00000011:
  case 0b00011100:
  case 0b00001000:
    Serial.print("zeroRight ");
    Serial.println();
    motors.zeroRight();
    break;

  case 0b11101100:
  case 0b11011000:
  case 0b10111000:
  case 0b11110000:
  case 0b10010000:
    if (ignoreLeft < 5) {
      ignoreLeft++;
      motors.forward();
      break;
    }
    rotation.moveForwardFor(5);
    // rotation.turnDegreesRight(90);
    // for (size_t i = 0; i < 8; i++)
    // {
    //   Serial.print(lineState.linePoints[i].isLine);
    // }
    Serial.println();
    if (tryFindLine())
    {
      Serial.print("crossroad w left ");
      //rotation.turnDegreesLeft(50);
      for (size_t i = 0; i < 8; i++)
      {
        Serial.print(lineState.linePoints[i].isLine);
      }
      break;
    };
    Serial.print("zeroLeft ");
        for (size_t i = 0; i < 8; i++)
    {
      Serial.print(lineState.linePoints[i].isLine);
    }
    while (convertToBinary(line.readLine()) != 0b00011000)
    {
      motors.zeroLeft(70);
    }
    motors.stop();
    ignoreLeft = 0;
    break;
  case 0b00010111:
  case 0b00011101:
  case 0b00011001:
  case 0b00011011:
  case 0b00011111:
    if (ignoreRight < 5) {
      ignoreRight++;
      motors.forward();
      break;
    }
    rotation.moveForwardFor(5);
    // rotation.turnDegreesLeft(90);

    Serial.println();

    if (tryFindLine())
    {
      Serial.print("crossroad w right ");
      for (size_t i = 0; i < 8; i++)
      {
        Serial.print(lineState.linePoints[i].isLine);
      }
      rotation.turnDegreesRight(50);
      while (convertToBinary(line.readLine()) != 0b00011000)
      {
        motors.zeroRight(70);
      }
      break;
    }
    Serial.print("zeroRight ");
    for (size_t i = 0; i < 8; i++)
    {
      Serial.print(lineState.linePoints[i].isLine);
    }
    while (convertToBinary(line.readLine()) != 0b00011000)
    {
      motors.zeroRight(70);
    }
    motors.stop();
    ignoreRight = 0;
    break;
  case 0b10111101:
  case 0b11111101:
  case 0b11111011:
  case 0b11111111:
  // if (ignoreForward < 3) {
  //   ignoreForward++;
  //   motors.forward();
  //   break;
  // }
    rotation.moveForwardFor(5);
    Serial.println();
    if (convertToBinary(line.readLine()) == 0b11111111)
    {
      // the end
      motors.stop();
      while (1)
        ;
    }
    else if (tryFindLine())
    {
      Serial.print("crossroad");
      for (size_t i = 0; i < 8; i++)
      {
        Serial.print(lineState.linePoints[i].isLine);
      }
      //rotation.moveForwardFor(5);
       rotation.turnDegreesRight(50);
      while (convertToBinary(line.readLine()) != 0b00011000)
      {
        motors.zeroRight();
      }
    }
    else if (tryFindNoLine())
    {
      Serial.print("T-crossroad ");
      for (size_t i = 0; i < 8; i++)
      {
        Serial.print(lineState.linePoints[i].isLine);
      }
      rotation.turnDegreesRight(50);
      while (convertToBinary(line.readLine()) != 0b00011000)
      {
        motors.zeroRight();
      }
    }
    ignoreForward = 0;
    break;
  case 0b00000000:
    if (ignoreNoLine < 30) {
      ignoreNoLine++;
      motors.forward();
      break;
    }
    rotation.moveForwardFor(3);
    rotation.turnDegreesRight(180);
    Serial.println();
    Serial.print("turn around");
    while (convertToBinary(line.readLine()) != 0b00011000)
    {
      motors.zeroLeft();
    }
    ignoreNoLine = 0;
    break;
  }
}

int detectChange()
{
  // line
  lineSensorData newLineState = line.readLine();
  for (int i = 0; i < 8; i++)
  {
    if (newLineState.linePoints[i].isLine != lineState.linePoints[i].isLine)
    {
      lineState = newLineState;
      return 1;
    }
    return -1;
  }

  // object
  // use milis
  // int currentTime = millis();
  // if (currentTime - lastTime > 1000)
  // {
  //   int d = sonar.getDistance();
  //   // Serial.println(d);
  //   lastTime = currentTime;
  //   if (d < 10)
  //   {
  //     return 2;
  //   }
  // }

  return 0;
}

// uint8_t convertToBinary(lineSensorData line)
// {
//   uint8_t decimal = 0b00000000;
//   for (int i = 0; i < 8; i++)
//   {
//     if (line.linePoints[i].isLine)
//     {
//       decimal |= 1 << 7 - i;
//     }
//   }
//   // Serial.println(decimal);
//   return decimal;
// }

// void moveForward()

int Find(uint8_t arr[], uint8_t x)
{
  int n = sizeof(arr) / sizeof(arr[0]);
  for (int i = 0; i < n; i++)
    if (arr[i] == x)
      return i;
  return -1;
}

boolean tryFindLine() {
  long timer = millis();
  while (millis() - timer < 200)
  {
    motors.zeroLeft();
    if (Find(lineForward,convertToBinary(line.readLine())) != -1)
    {
      return true;
    }
  }
  timer = millis();
  while (millis() - timer < 400)
  {
    motors.zeroRight();
    if (Find(lineForward,convertToBinary(line.readLine())) != -1)
    {
      return true;
    }
  }
  return false;
}

boolean tryFindNoLine() {
  long timer = millis();
  while (millis() - timer < 200)
  {
    motors.zeroLeft();
    if (convertToBinary(line.readLine()) == 0b00000000)
    {
      return true;
    }
  }
  timer = millis();
  while (millis() - timer < 400)
  {
    motors.zeroRight();
    if (convertToBinary(line.readLine()) == 0b00000000)
    {
      return true;
    }
  }
  return false;
}