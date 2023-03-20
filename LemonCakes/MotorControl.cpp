#include "MotorControl.h"
#include "IMU.h"

Motor* leftMotor;
Motor* rightMotor;

float driveStraightInitialAngle;
bool encoderDisabled = false;

void leftEncoderISR() {
  if(!encoderDisabled) {
    leftMotor->incrementEncoder();
    leftMotor->RPMCalc();
  }

  return;
}

void rightEncoderISR() {
  if(!encoderDisabled) {
    rightMotor->incrementEncoder();
    rightMotor->RPMCalc();
  }

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

uint32_t getLeftEncoder() {
  return leftMotor->getEncoderCnt();
}

uint32_t getLeftMeasuredRPM() {
  return leftMotor->getMeasuredRPM();
}

uint32_t getRightEncoder() {
  return rightMotor->getEncoderCnt();
}

uint32_t getRightMeasuredRPM() {
  return rightMotor->getMeasuredRPM();
}

void driveForward() {
  driveStraightInitialAngle = getAbsGyroDeg();
  encoderDisabled = false;
  
  leftMotor->setDirection(CW);
  rightMotor->setDirection(CCW);

  leftMotor->setCommandedRPM(5968);
  rightMotor->setCommandedRPM(5968);

  // leftMotor->setPWM(50);
  // rightMotor->setPWM(50);

  return;
}

void driveBackward() {
  driveStraightInitialAngle = getAbsGyroDeg();
  encoderDisabled = false;

  leftMotor->setDirection(CCW);
  rightMotor->setDirection(CW);

  leftMotor->setCommandedRPM(5968);
  rightMotor->setCommandedRPM(5968);

  // leftMotor->setPWM(50);
  // rightMotor->setPWM(50);

  return;
}

void driveStraight() {
  saveIMUData();
  if(getAbsGyroDeg() > driveStraightInitialAngle + 1) { // Drifting CW
    leftMotor->setActualCommandedRPM(leftMotor->getNominalCommandedRPM() - 500);
    rightMotor->setActualCommandedRPM(rightMotor->getNominalCommandedRPM() + 500);
    digitalWrite(12, HIGH);
  }
  else if(getAbsGyroDeg() < driveStraightInitialAngle - 1) { //Drifting CCW
    leftMotor->setActualCommandedRPM(leftMotor->getNominalCommandedRPM() + 500);
    rightMotor->setActualCommandedRPM(rightMotor->getNominalCommandedRPM() - 500);
    digitalWrite(11, HIGH);
  }
  else {
    leftMotor->setActualCommandedRPM(leftMotor->getNominalCommandedRPM());
    rightMotor->setActualCommandedRPM(rightMotor->getNominalCommandedRPM());
    digitalWrite(11, LOW);   
    digitalWrite(12, LOW);  
  }
  
  return;
}

void stop() {
  encoderDisabled = true;
  leftMotor->motorStop();
  rightMotor->motorStop();
  resetGyro();
}

void turnDegrees(float deg) {

  float initialAngle = getAbsGyroDeg();

  if(deg >= 0){
    deg -= 2.5;
    //do a clockwise turn
    leftMotor->setDirection(CW);
    rightMotor->setDirection(CW);
    leftMotor->setPWM(60);
    rightMotor->setPWM(60);     

    while(getAbsGyroDeg() < initialAngle + deg){
      saveIMUData();
    }

  }
  else{
    deg += 2.5;
    //do a ccw turn
    leftMotor->setDirection(CCW);
    rightMotor->setDirection(CCW);
    leftMotor->setPWM(60);
    rightMotor->setPWM(60); 

    while(getAbsGyroDeg() > initialAngle + deg){
      saveIMUData();
    }

  }

  return;

}

void PIDCalc() {
  static uint32_t timer = 0;
  
  if(millis() > timer + 10) {
    leftMotor->PIDCalc();
    rightMotor->PIDCalc();

    timer = millis();
  }

  return;
}

int32_t getError() {
  return rightMotor->getError();
}