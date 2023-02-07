#ifndef MotorControl_h
#define MotorControl_h

#include "Motor.h"

class MotorControl {
private:
  Motor* leftMotor;
  Motor* rightMotor;

public:
  MotorControl(int leftEncoderPin, int leftIn1Pin, int leftIn2Pin, int leftPwmPin, int rightEncoderPin, int rightIn1Pin, int rightIn2Pin, int rightPwmPin);
  ~MotorControl();

  void setup();
  void driveForward();
  void turnDegrees(int deg);
};

#endif