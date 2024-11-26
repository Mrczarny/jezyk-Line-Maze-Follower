# Line Maze Follower

Made in C++ for Arduino Nano with Visual Studio Code

This code controls the RelayBot that is supposed to go through the Line Maze

## Table of Contents
- Requirements
- Installation
- Configuration
- How It Works

## Requirements
- [Visual Studio Code](https://code.visualstudio.com/download)
- [Jira](https://adamskijj.atlassian.net/jira/your-work)
- Arduino Nano
- RelayBot
- USB cable to connect Arduino to PC

## Installation
- Download Zip file from Github
- Open the folder in Visual Studio Code

## Configuration
- Turn the switches on Arduino Nano off
- Connect Arduino Nano to PC using USB cable
- Verify the port is correctly chosen
- Compile and upload the code
- Reset Arduino Uno

## How It Works
RelayBot picks up the object and follows the maze to the end and then puts down the object. RelayBot uses rotation sensors and movement functions to move through the maze. RelayBot fails if the robot ends up in the same place it started. It can find its way by trial and error.