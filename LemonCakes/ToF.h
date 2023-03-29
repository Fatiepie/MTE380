#ifndef ToF_h
#define ToF_h

#include <Arduino.h>
#include <Wire.h>  
#include <TFMPI2C.h> 

void setupToF();

int16_t testData();

#endif