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

  
  
}

//three states -- go straight for a bit, left turn, go straight and then stop



void loop() {
  


  if(state == state1) {

    int time1 = millis();
    
    driveForward();
    
    while(millis() < time1 + 5000){
    }


    state = state2;
  }

  else if(state == state2) {
    
    stop();
    delay(5000);
    turnDegrees(90);
    stop();
    state = state3;


  }

    else if(state == state3) {
    
    delay(5000);

    driveBackward();

    delay(5000);

    stop();

    state = state4;


  }

  // testMotors();
  // saveIMUData();
  // Serial.println(getAbsGyroDeg());
  // turnDegrees(90)
  // Serial.println(testIMU());
  
}