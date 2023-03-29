#include "MotorControl.h"
#include "IMU.h"
#include "Timer.h"
#include "ToF.h"

#define TOUCH_SENSOR 4

enum States{
  state1,
  state2,
  state3,
  state4,
  testTOF,
  s1,
  s2,
  s3,
  s4,
  s5,
  s6,
  s7
};

States state = testTOF;

void setup() {
  // Set up pins of peripherals
  Serial.begin(115200);

  setupTimer();
  setupMotors();
  setupIMU();
  setupToF();

  pinMode(TOUCH_SENSOR, INPUT);

  while(!digitalRead(TOUCH_SENSOR)){}
  
  delay(1000);
}

//three states -- go straight for a bit, left turn, go straight and then stop



void loop() {

  if(state == state1) {

    int time1 = millis();
    
    driveForward(3000);

    while(millis() < time1 + 12000){
      PIDCalc();
      driveStraight();
    }

    stop();

    state = state4;
  }

  else if(state == state2) {

    turnDegrees(90);
    stop();
    delay(1000);
    turnDegrees(-90);
    stop();
    state = state4;

  }

  else if(state == state3) {
    
    int time1 = millis();
    
    driveBackward(2000);

    while(millis() < time1 + 5000){
      PIDCalc();
    }

    stop();

    state = state4;


  }

  else if(state == state4) {
    // Serial.println(getRightEncoder());
    // Serial.println(getRightMeasuredRPM());
  }

  else if(state == testTOF) {
    int16_t a = testData();
    Serial.println(a);
    if(a == -1) {
      state = state4;
    }
  }

  else if(state == s1) {
    //drive straight until TOF sees ramp
    driveForward(3000);

    
    int16_t tof_input = testData();

    while(tof_input >= 50){
      PIDCalc();
      driveStraight();
      tof_input = testData();
    }

    //then turn 90 degrees left
    stop();
    delay(500);
    turnDegrees(90);
    stop();
    state = s2;
  }

  else if(state == s2) {
    //drive straight until IMU senses incline
    driveForward(3000);

    //drive


  }

  else if(state == s3) {
    //drive straight until IMU senses flat

    //drive slower 

  }

  else if(state == s4) {
    //drive slow until IMU senses downhill

    //reverse wheels


  }

  else if(state == s5) {
    //drive slightly backwards until IMU senses level

    //drive straight a little bit

    //turn 90 degrees left

  }

  else if(state == s6) {
    //drive straight until IMU senses box
    
    //turn 90 degrees left

  }

    else if(state == s7) {
    //drive straight until it hits something

    //stop motors

  }  
}