#ifndef MotorControl_h
#define MotorControl_h

#include "Motor.h"

#define LEFT_ENCODER 2
#define LEFT_IN1 7
#define LEFT_IN2 8
#define LEFT_PWM 5
#define LEFT_LED 13

#define RIGHT_ENCODER 3
#define RIGHT_IN1 9
#define RIGHT_IN2 10
#define RIGHT_PWM 6
#define RIGHT_LED 12

void leftEncoderISR();
void rightEncoderISR();
void setupMotors();

uint32_t getLeftEncoder();
uint32_t getLeftMeasuredRPM();

uint32_t getRightEncoder();
uint32_t getRightMeasuredRPM();

void driveForward(int speed);
void stop();
void turnDegrees(float deg);
void driveBackward(int speed);
void driveStraight();

void PIDCalc();
int32_t getError();

#endif