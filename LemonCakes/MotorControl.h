#ifndef MotorControl_h
#define MotorControl_h

#include "Motor.h"

#define LEFT_ENCODER 2
#define LEFT_IN1 7
#define LEFT_IN2 8
#define LEFT_PWM 9

#define RIGHT_ENCODER 3
#define RIGHT_IN1 5
#define RIGHT_IN2 6
#define RIGHT_PWM 10

void leftEncoderISR();
void rightEncoderISR();
void setupMotors();

void testMotors();

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