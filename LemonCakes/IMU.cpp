#include "IMU.h"

IMU* imu = new IMU();

void setupIMU() {
  imu->setup();
  
  return;
}

void testIMU() {
  imu->saveData();

  return;
}

void IMU::setup() {
  imu.begin_I2C();

  imu.setAccelRange(ICM20948_ACCEL_RANGE_2_G);
  imu.setGyroRange(ICM20948_GYRO_RANGE_250_DPS);

  return;
}

void IMU::saveData() {
  imu.getEvent(&accel, &gyro, &temp);

  return;
}

sensors_vec_t IMU::getAccel() {
  return accel.acceleration;
}
sensors_vec_t IMU::getGyro() {
  return gyro.gyro;
}