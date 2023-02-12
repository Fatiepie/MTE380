#include "MotorControl.h"
#include "IMU.h"
 
void setup() {
  // Set up pins of peripherals
  Serial.begin(115200);
  
  setupMotors();
  setupIMU();
  
}

void loop() {
  testMotors();
  
  testIMU();
  
}