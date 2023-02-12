#include "MotorControl.h"

MotorControl* motors = new MotorControl(LEFT_ENCODER, LEFT_IN1, LEFT_IN2, LEFT_PWM, RIGHT_ENCODER, RIGHT_IN1, RIGHT_IN2, RIGHT_PWM);

void leftEncoderISR() {
  motors->leftMotor->incrementEncoder();

  return;
}

void rightEncoderISR() {
  motors->rightMotor->incrementEncoder();

  return;
}

void setupMotors() {
  motors->setup();

  // Set up encoder interrupts
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER), leftEncoderISR, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER), rightEncoderISR, RISING);

  return;
}

void testMotors() {
  // motors->driveForward();
  // delay(5000);
  // motors->stop();
  // delay(5000);
  
  return;
}

//////////////////////////////////////////// MOTOR OBJECT FUNCTIONS //////////////////////////////////////////////

MotorControl::MotorControl(uint8_t leftEncoderPin, uint8_t leftIn1Pin, uint8_t leftIn2Pin, uint8_t leftPwmPin, uint8_t rightEncoderPin, uint8_t rightIn1Pin, uint8_t rightIn2Pin, uint8_t rightPwmPin) {
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

  leftMotor->setPWM(50);
  rightMotor->setPWM(50);

  return;
}

void MotorControl::stop() {
  leftMotor->motorStop();
  rightMotor->motorStop();
}

void MotorControl::turnDegrees(int deg) {
  return;
}