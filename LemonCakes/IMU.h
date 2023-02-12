#ifndef IMU_h
#define IMU_h

#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

void setupIMU();

void testIMU();

class IMU {

private:
  Adafruit_ICM20948 imu;
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;  

public:
  void setup();
  void saveData();

  sensors_vec_t getAccel();
  sensors_vec_t getGyro();
};

#endif