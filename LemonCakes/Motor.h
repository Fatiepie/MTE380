#ifndef Motor_h
#define Motor_h

#include <stdint.h>
#include <Arduino.h>

#define KP 0.03
#define KI 0.05

enum MotorDirection {
  CW,
  CCW
};

class Motor {

private:
  uint32_t EncoderCnt;
  uint8_t EncoderPin;

  uint8_t IN1Pin;
  uint8_t IN2Pin;
  uint8_t PWMPin;
  int16_t PWM;
  
  int16_t MeasuredRPM;
  int16_t ActualCommandedRPM;
  int16_t NominalCommandedRPM;
  uint32_t LastEncoderTime;

  int32_t Error;
  float Proportional;
  float Integral;

public:
  Motor(uint8_t encoderPin, uint8_t in1Pin, uint8_t in2Pin, uint8_t pwmPin);
  void setup();

  int16_t getPWM();
  void setPWM(int16_t pwm);

  int16_t getMeasuredRPM();
  void setMeasuredRPM(int16_t rpm);
  int16_t getActualCommandedRPM();
  int16_t getNominalCommandedRPM();
  void setActualCommandedRPM(int16_t rpm);
  void setCommandedRPM(int16_t rpm);
  void RPMCalc();

  void PIDCalc();
  void resetPID();

  int32_t getError();

  void setDirection(MotorDirection dir);
  void motorStop();

  void incrementEncoder();
  void resetEncoder();
  uint32_t getEncoderCnt();
};

#endif