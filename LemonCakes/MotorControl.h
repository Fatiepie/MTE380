#ifndef MotorControl_h
#define MotorControl_h

#include "Motor.h"

class MotorControl {
public:
  Motor* leftMotor;
  Motor* rightMotor;

  MotorControl(uint8_t leftEncoderPin, uint8_t leftIn1Pin, uint8_t leftIn2Pin, uint8_t leftPwmPin, uint8_t rightEncoderPin, uint8_t rightIn1Pin, uint8_t rightIn2Pin, uint8_t rightPwmPin);
  ~MotorControl();

  void setup();
  
  void driveForward();
  void stop();
  void turnDegrees(int deg);
};

#endif