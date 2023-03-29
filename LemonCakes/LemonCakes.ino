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
  testTOF
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
    
    driveForward();

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
    
    driveBackward();

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
  
}