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
  uint16_t EncoderCnt;
  uint8_t EncoderPin;
  uint8_t IN1Pin;
  uint8_t IN2Pin;
  uint8_t PWMPin;
  uint8_t PWM;

public:
  Motor(uint8_t encoderPin, uint8_t in1Pin, uint8_t in2Pin, uint8_t pwmPin);
  void setup();

  int getPWM();
  void setPWM(uint8_t pwm);

  void setDirection(MotorDirection dir);
  void motorStop();

  void incrementEncoder();
  void resetEncoder();
  uint16_t getEncoderCnt();
};

#endif