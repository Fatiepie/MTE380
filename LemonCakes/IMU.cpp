#include "IMU.h"


Adafruit_ICM20948 imu;
sensors_event_t accel;
sensors_event_t gyro;
sensors_event_t temp;  
float absGyro;
float absGyroVertical;
float absGyroSideways;


void setupIMU() {
  imu.begin_I2C();

  imu.setAccelRange(ICM20948_ACCEL_RANGE_2_G);
  imu.setGyroRange(ICM20948_GYRO_RANGE_250_DPS);

  absGyro = 0;
  absGyroVertical = 0;
  absGyroSideways = 0;

  return;
}

void calcAbsGyro() { 
  if(getGyro().z > 0.07 || getGyro().z < -0.04) {
    absGyro = absGyro + getGyro().z * 0.01;
  }
  if(getGyro().x > 0.04 || getGyro().x < -0.04) {
    absGyroVertical = absGyroVertical + getGyro().x * 0.01;
  }
  if(getGyro().y > 0.04 || getGyro().y < -0.04) {
    absGyroSideways = absGyroSideways + getGyro().y * 0.01;
  }
  return;
}

float getAbsGyroDeg() {
  return absGyro * 180 / 3.14159265358979323846;
}

float getAbsGyroDegVertical() {
  return absGyroVertical * 180 / 3.14159265358979323846;
}

float getAbsGyroDegSideways() {
  return absGyroSideways * 180 / 3.14159265358979323846;
}

void resetGyro() {
  saveIMUData();
  absGyro = 0;

  return;
}

void resetVerticalDegree() {
  absGyroVertical = 0;
  absGyroSideways = 0;

  return;
}

void saveIMUData() {
  imu.getEvent(&accel, &gyro, &temp);

  return;
}

sensors_vec_t getAccel() {
  return accel.acceleration;
}
sensors_vec_t getGyro() {
  return gyro.gyro;
}