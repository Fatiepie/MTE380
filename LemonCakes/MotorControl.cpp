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
  pinMode(LEFT_LED, OUTPUT);
  pinMode(RIGHT_LED, OUTPUT);

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

  leftMotor->setCommandedRPM(3000);
  rightMotor->setCommandedRPM(3000);

  return;
}

void driveBackward() {
  driveStraightInitialAngle = getAbsGyroDeg();
  encoderDisabled = false;

  leftMotor->setDirection(CCW);
  rightMotor->setDirection(CW);

  leftMotor->setCommandedRPM(2000);
  rightMotor->setCommandedRPM(2000);

  return;
}

void driveStraight() {
  saveIMUData();
  if(getAbsGyroDeg() > driveStraightInitialAngle + 0.5) { // Drifting CW
    leftMotor->setActualCommandedRPM(leftMotor->getNominalCommandedRPM() - 1250);
    rightMotor->setActualCommandedRPM(rightMotor->getNominalCommandedRPM() + 1250);
    digitalWrite(RIGHT_LED, HIGH);
  }
  else if(getAbsGyroDeg() < driveStraightInitialAngle - 0.5) { //Drifting CCW
    leftMotor->setActualCommandedRPM(leftMotor->getNominalCommandedRPM() + 1000);
    rightMotor->setActualCommandedRPM(rightMotor->getNominalCommandedRPM() - 1000);
    digitalWrite(LEFT_LED, HIGH);
  }
  else {
    leftMotor->setActualCommandedRPM(leftMotor->getNominalCommandedRPM());
    rightMotor->setActualCommandedRPM(rightMotor->getNominalCommandedRPM());
    digitalWrite(RIGHT_LED, LOW);   
    digitalWrite(LEFT_LED, LOW);  
  }
  
  return;
}

void stop() {
  encoderDisabled = true;
  leftMotor->motorStop();
  rightMotor->motorStop();
  resetGyro();

  digitalWrite(RIGHT_LED, LOW);   
  digitalWrite(LEFT_LED, LOW); 
  
  return;
}

void turnDegrees(float deg) {

  float initialAngle = getAbsGyroDeg();

  if(deg >= 0){
    deg -= 8;
    //do a clockwise turn
    leftMotor->setDirection(CW);
    rightMotor->setDirection(CW);
    leftMotor->setPWM(70);
    rightMotor->setPWM(65);     

    while(getAbsGyroDeg() < initialAngle + deg){
      saveIMUData();
    }

  }
  else{
    deg += 8;
    //do a ccw turn
    leftMotor->setDirection(CCW);
    rightMotor->setDirection(CCW);
    leftMotor->setPWM(70);
    rightMotor->setPWM(65); 

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