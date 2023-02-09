#include "Motor.h"

Motor::Motor(uint8_t encoderPin, uint8_t in1Pin, uint8_t in2Pin, uint8_t pwmPin) {
  EncoderCnt = 0;
  EncoderPin = encoderPin;
  IN1Pin = in1Pin;
  IN2Pin = in2Pin;
  PWMPin = pwmPin;
  PWM = 0;
}

void Motor::setup() {
  pinMode(EncoderPin, INPUT);
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT);
  pinMode(PWMPin, OUTPUT);

  motorStop();

  return;
}

int Motor::getPWM() {
  return PWM;
}

void Motor::setPWM(uint8_t pwm) {
  PWM = pwm;
  analogWrite(PWMPin, PWM);

  return;
}

void Motor::setDirection(MotorDirection dir) {
  switch(dir) {
    case CW:
      digitalWrite(IN1Pin, LOW);
      digitalWrite(IN2Pin, HIGH);
      break;
    case CCW:
      digitalWrite(IN1Pin, HIGH);
      digitalWrite(IN2Pin, LOW);
      break;      
  }

  return;
}

void Motor::motorStop() {
  setPWM(0);

  digitalWrite(IN1Pin, LOW);
  digitalWrite(IN2Pin, LOW);

  return;
}

void Motor::incrementEncoder() {
  EncoderCnt++;

  return;
}

void Motor::resetEncoder() {
  EncoderCnt = 0;

  return;
}

uint16_t Motor::getEncoderCnt() {
  return EncoderCnt;
}