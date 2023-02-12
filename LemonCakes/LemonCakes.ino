#include "MotorControl.h"

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

MotorControl* motors = new MotorControl(LEFT_ENCODER, LEFT_IN1, LEFT_IN2, LEFT_PWM, RIGHT_ENCODER, RIGHT_IN1, RIGHT_IN2, RIGHT_PWM);
 
void setup() {
  // Set up pins of peripherals
  Serial.begin(115200);
  motors->setup();
  
  // Set up encoder interrupts
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER), leftEncoderISR, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER), rightEncoderISR, RISING);
}

void loop() {
  // motors->driveForward();
  // delay(5000);
  // motors->stop();
  // delay(5000);
}

void leftEncoderISR() {
  motors->leftMotor->incrementEncoder();

  return;
}

void rightEncoderISR() {
  motors->rightMotor->incrementEncoder();

  return;
}