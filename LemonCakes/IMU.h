#ifndef IMU_h
#define IMU_h

#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


void setupIMU();
void calcAbsGyro();
float getAbsGyroDeg();

void resetGyro();

float testIMU();

void saveIMUData();

sensors_vec_t getAccel();
sensors_vec_t getGyro();

#endif