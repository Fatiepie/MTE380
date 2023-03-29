#include "ToF.h"

TFMPI2C tof;
int16_t dist = 0;

void setupToF() {
  tof.recoverI2CBus();

  return;
}

int16_t testData() {
  delay(25);
  tof.getData(dist); // Get a frame of data
  if( tof.status == TFMP_READY)         // If no error...
  {
      // Serial.println(dist);
      return dist;
  }  

  return -1;
}