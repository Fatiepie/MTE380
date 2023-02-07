#include "Motor.h"
#include <Arduino.h>

Motor::Motor(int encoderPin, int in1Pin, int in2Pin, int pwmPin) {
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

void Motor::setPWM(int pwm) {
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
  digitalWrite(IN1Pin, LOW);
  digitalWrite(IN2Pin, LOW);
  setPWM(0);

  return;
}