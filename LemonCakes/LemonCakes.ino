#include "MotorControl.h"
#include "IMU.h"
#include "Timer.h"

enum States{
  state1,
  state2,
  state3,
  state4
};

States state = state1;

void setup() {
  // Set up pins of peripherals
  Serial.begin(115200);

  setupTimer();
  setupMotors();
  setupIMU();

  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  
  delay(1000);
}

//three states -- go straight for a bit, left turn, go straight and then stop



void loop() {
  


  if(state == state1) {

    int time1 = millis();
    
    driveForward();
    
    // while(millis() < time1 + 10000){
    //   driveStraight();
    //   Serial.println(getLeftEncoder());
    // }

    // while(getRightEncoder() < 2785){
    //   driveStraight();
    //   Serial.println(getRightMeasuredRPM());
    // }

    while(millis() < time1 + 5000){
      PIDCalc();
      driveStraight();
      // Serial.println(getError());
      // Serial.println(getRightMeasuredRPM());
      // Serial.println(getLeftMeasuredRPM());
    }

    stop();

    state = state2;
  }

  else if(state == state2) {

    delay(2000);
    turnDegrees(90);
    stop();
    state = state3;


  }

  else if(state == state3) {
    delay(2000);
    
    int time1 = millis();
    
    driveBackward();
    
    // while(millis() < time1 + 10000){
    //   driveStraight();
    //   Serial.println(getLeftEncoder());
    // }

    // while(getRightEncoder() < 2785){
    //   driveStraight();
    //   Serial.println(getRightEncoder());
    // }

    while(millis() < time1 + 5000){
      PIDCalc();
      // driveStraight();
      // Serial.println(getError());
      // Serial.println(getRightMeasuredRPM());
      // Serial.println(getLeftMeasuredRPM());
    }

    stop();

    state = state4;


  }

  else if(state == state4) {
    // Serial.println(getRightEncoder());
    // Serial.println(getRightMeasuredRPM());
  }
  
}