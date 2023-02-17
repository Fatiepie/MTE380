#include "MotorControl.h"
#include "IMU.h"

Motor* leftMotor;
Motor* rightMotor;

void leftEncoderISR() {
  leftMotor->incrementEncoder();

  return;
}

void rightEncoderISR() {
  rightMotor->incrementEncoder();

  return;
}

void setupMotors() {
  leftMotor = new Motor(LEFT_ENCODER, LEFT_IN1, LEFT_IN2, LEFT_PWM);
  rightMotor = new Motor(RIGHT_ENCODER, RIGHT_IN1, RIGHT_IN2, RIGHT_PWM);

  leftMotor->setup();
  rightMotor->setup();

  // Set up encoder interrupts
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER), leftEncoderISR, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER), rightEncoderISR, RISING);

  return;
}

void testMotors() {
  driveForward();
  delay(5000);
  stop();
  delay(5000);
  
  return;
}

void driveForward() {
  leftMotor->setDirection(CW);
  rightMotor->setDirection(CCW);

  leftMotor->setPWM(50);
  rightMotor->setPWM(50);

  return;
}

void driveBackward() {
  leftMotor->setDirection(CCW);
  rightMotor->setDirection(CW);

  leftMotor->setPWM(50);
  rightMotor->setPWM(50);

  return;
}

void stop() {
  leftMotor->motorStop();
  rightMotor->motorStop();
}

void turnDegrees(int deg) {

  float initialAngle = getAbsGyroDeg();

  if(deg >= 0){
    //do a clockwise turn
    leftMotor->setDirection(CW);
    rightMotor->setDirection(CW);
    leftMotor->setPWM(50);
    rightMotor->setPWM(50);     

    while(getAbsGyroDeg() < initialAngle + deg){
      saveIMUData();
    }

  }
  else{
    //do a ccw turn
    leftMotor->setDirection(CCW);
    rightMotor->setDirection(CCW);
    leftMotor->setPWM(50);
    rightMotor->setPWM(50); 

    while(getAbsGyroDeg() > initialAngle + deg){
      saveIMUData();
    }

  }

  

  return;

}

