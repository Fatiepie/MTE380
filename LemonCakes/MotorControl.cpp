#include "MotorControl.h"
#include <Arduino.h>

MotorControl::MotorControl(int leftEncoderPin, int leftIn1Pin, int leftIn2Pin, int leftPwmPin, int rightEncoderPin, int rightIn1Pin, int rightIn2Pin, int rightPwmPin) {
  leftMotor = new Motor(leftEncoderPin, leftIn1Pin, leftIn2Pin, leftPwmPin);
  rightMotor = new Motor(rightEncoderPin, rightIn1Pin, rightIn2Pin, rightPwmPin);
}

MotorControl::~MotorControl() {
  delete leftMotor;
  delete rightMotor;
}

void MotorControl::setup() {
  leftMotor->setup();
  rightMotor->setup();

  return;
}

void MotorControl::driveForward() {
  leftMotor->setDirection(CW);
  rightMotor->setDirection(CCW);

  leftMotor->setPWM(100);
  rightMotor->setPWM(100);

  return;
}

void MotorControl::turnDegrees(int deg) {
  return;
}