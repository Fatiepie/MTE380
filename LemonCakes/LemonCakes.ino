#include "MotorControl.h"
#include "IMU.h"
#include "Timer.h"
 
void setup() {
  // Set up pins of peripherals
  Serial.begin(115200);

  setupTimer();
  setupMotors();
  setupIMU();
  
}

void loop() {
  testMotors();
  saveIMUData();
  Serial.println(getAbsGyroDeg());
  // Serial.println(testIMU());
  
}