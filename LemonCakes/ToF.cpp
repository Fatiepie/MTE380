#include "ToF.h"

TFMPI2C tof;
int16_t dist = 0;

void setupToF() {
  tof.recoverI2CBus();

  return;
}

int16_t testData() {

  static int lastCall = 0;
  int currentTime = millis();

  if(currentTime-lastCall > 50){
    tof.getData(dist); // Get a frame of data
    lastCall = currentTime; // Reset last call
    // if( tof.status == TFMP_READY) {  // If no error...
        // Serial.println(dist);
        // return dist;
    // }  

    // return -1;
  }

   return dist; 
  
}