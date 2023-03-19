#ifndef Motor_h
#define Motor_h

#include <stdint.h>
#include <Arduino.h>

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
  uint8_t PWM;
  
  uint16_t MeasuredRPM;
  uint16_t CommandedRPM;
  uint32_t LastEncoderTime;

  int32_t Error;
  int32_t Proportional;

public:
  Motor(uint8_t encoderPin, uint8_t in1Pin, uint8_t in2Pin, uint8_t pwmPin);
  void setup();

  uint8_t getPWM();
  void setPWM(uint8_t pwm);

  uint16_t getMeasuredRPM();
  void setMeasuredRPM(uint16_t rpm);
  uint16_t getCommandedRPM();
  void setCommandedRPM(uint16_t rpm);
  void RPMCalc();

  void PIDCalc();
  void resetPID();

  void setDirection(MotorDirection dir);
  void motorStop();

  void incrementEncoder();
  void resetEncoder();
  uint32_t getEncoderCnt();
};

#endif