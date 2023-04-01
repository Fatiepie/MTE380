#include "MotorControl.h"
#include "IMU.h"
#include "Timer.h"
#include "ToF.h"

#define TOUCH_SENSOR 4
#define BACKWARDS_RAMP_ANGLE 20
#define FORWARDS_RAMP_ANGLE 20

enum States{
  idle,
  testTOF,
  s1,
  s2,
  s3,
  s4,
  s5,
  s6,
  s7,
  testIMU
};

enum Mode{
  forwards,
  backwards
};

States state = s1;
Mode mode = backwards;

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

void loop() {

  if(state == testIMU) {
    while(true) {
      saveIMUData();
      // Serial.print(getAccel().x);
      // Serial.print(" ");
      // Serial.print(getAccel().y);
      // Serial.print(" ");
      Serial.println(getAbsGyroDegSideways());
    }
  }

  else if(state == idle) {
    // Serial.println(getRightEncoder());
    // Serial.println(getRightMeasuredRPM());
    stop();
  }

  else if(state == testTOF) {
    int16_t a = testData();
    Serial.println(a);
  }
///////////////////////////////////////////////////////////////STATE 1//////////////////////////////////////////////////////////
  else if(state == s1) {
    //drive straight until TOF sees ramp
    if(mode == backwards) {
      driveForward(7000);
    } else {
      driveForward(8000);
    }
    
    int16_t tof_input = testData();

    while(tof_input >= 100){
      PIDCalc();
      driveStraight();
      tof_input = testData();
    }
    //small delay before stopping
    int time = millis();
    if(mode == backwards) {
      while(millis() < time + 100){
        PIDCalc();
        driveStraight();
      }    
    } else {
      while(millis() < time + 50){
        PIDCalc();
        driveStraight();
      }       
    }

    //then turn 90 degrees left
    stop();
    resetGyro();
    delay(500);
    if(mode == backwards) {
      turnDegrees(90);
    } else {
      turnDegrees(-90);
    }
    stop();
    resetGyro();
    delay(500);
    state = s2;
  }
///////////////////////////////////////////////////////////////STATE 2//////////////////////////////////////////////////////////
  else if(state == s2) {
    //drive straight until IMU senses incline
    if(mode == backwards) {
      driveBackward(10000);
    } else {
      driveForward(10000);      
    }

    saveIMUData();
    //drive

    resetVerticalDegree();

    if(mode == backwards) {
      while(getAbsGyroDegVertical() > -BACKWARDS_RAMP_ANGLE){
        PIDCalc();
        saveIMUData();
      }
      int time = millis();
      while(millis() < time + 1500){
        PIDCalc();
        saveIMUData();
      } 
    } else {
      while(getAbsGyroDegVertical() < FORWARDS_RAMP_ANGLE){
        PIDCalc();
        driveStraight();
        saveIMUData();
      }
      int time = millis();
      while(millis() < time + 1000){
        PIDCalc();
        saveIMUData();
      } 
    }

    state = s3;
  }
///////////////////////////////////////////////////////////////STATE 3//////////////////////////////////////////////////////////
  else if(state == s3) {
    //drive straight until IMU senses flat
    resetVerticalDegree();

    if(mode == backwards) {
      while(getAbsGyroDegVertical() < BACKWARDS_RAMP_ANGLE){
        PIDCalc();
        saveIMUData();
      }
      delay(500);
    } else {
      while(getAbsGyroDegVertical() > -FORWARDS_RAMP_ANGLE){
        PIDCalc();
        saveIMUData();
      }
      delay(50);
    }

    state = s4;
  }
///////////////////////////////////////////////////////////////STATE 4//////////////////////////////////////////////////////////
  else if(state == s4) {
    stop();
    delay(100);
    resetVerticalDegree();
    resetGyro();

    if(mode == backwards) {
      driveBackward(2000);
      //drive slow until IMU senses downhill
      while(getAbsGyroDegVertical() < BACKWARDS_RAMP_ANGLE){
        PIDCalc();
        saveIMUData();
      }
      stop();

      int time = millis();
      while(millis() < time + 1000){
        saveIMUData();
      } 
    } else {
      driveForward(2000);
      //drive slow until IMU senses downhill
      while(getAbsGyroDegVertical() > -FORWARDS_RAMP_ANGLE){
        PIDCalc();
        saveIMUData();
      }
      stop();
      
      int time = millis();
      while(millis() < time + 150){
        saveIMUData();
      } 
    }

    state = s5;
  }
///////////////////////////////////////////////////////////////STATE 5//////////////////////////////////////////////////////////
  else if(state == s5) {
    resetVerticalDegree();

    //wait until IMU senses level (time)
    if(mode == backwards) {
      int time = millis();
      while(millis() < time + 2500){
        saveIMUData();
      }

      //drive straight a little bit (?)
      driveForward(8000);
      time = millis();
      while(millis() < time + 250){
        PIDCalc();
        driveStraight();
      }  
      stop();

      time = millis();
      while(millis() < time + 500){
        saveIMUData();
      } 

      turnDegrees(95 - getAbsGyroDeg());
      stop();
      resetGyro();
      delay(250);
    } else {
      while(getAbsGyroDegVertical() < FORWARDS_RAMP_ANGLE){
        saveIMUData();
      }

      //drive straight a little bit (?)
      stop();

      int time = millis();
      while(millis() < time + 500){
        saveIMUData();
      } 

      //turn 90 degrees left
      turnDegrees(-90 - getAbsGyroDeg());
      stop();
      resetGyro();
      delay(500);
    }

    state = s6;
  }
///////////////////////////////////////////////////////////////STATE 6//////////////////////////////////////////////////////////
  else if(state == s6) {
    
    //drive straight until IMU senses box
    driveForward(8000);
    int time = millis();
    while(millis() < time + 1000){
      PIDCalc();
      driveStraight();
    }  

    int16_t tof_input = testData();
    resetVerticalDegree();
    time = millis();
    while(tof_input >= 165){
      PIDCalc();
      driveStraight();
      tof_input = testData();
      if(millis() > time + 2000) {
        resetVerticalDegree();
        time = millis();
      }
      // if(getAbsGyroDegVertical() >= 3.1 || getAbsGyroDegSideways() >= 3.2 || getAbsGyroDegSideways() <= -3.2) {
      //   delay(200);
      //   stop();
      //   resetGyro();
      //   state = idle;
      //   break;
      // }
    }

    //turn 90 degrees left
    if(state == s6) {
      stop();
      resetGyro();

      driveBackward(8000);
      time = millis();
      while(millis() < time + 250){
        PIDCalc();
      }  
      stop();
      resetGyro();

      delay(500);
      turnDegrees(-90);
      stop();
      resetGyro();
      delay(50);
      state = s7;
    }
  }
///////////////////////////////////////////////////////////////STATE 7//////////////////////////////////////////////////////////
  else if(state == s7) {
    driveForward(12000);
    saveIMUData();
    //drive
    int time = millis();
    resetVerticalDegree();
    while(getAbsGyroDegVertical() < 3.1){
      PIDCalc();
      driveStraight();
      if(millis() > time + 2000) {
        resetVerticalDegree();
        time = millis();
      }
      //       Serial.print(getAbsGyroDegVertical());
      // Serial.println(getAbsGyroDegSideways());
    }
    delay(50);
    stop();
    resetGyro();
    state = idle;
  }  
}