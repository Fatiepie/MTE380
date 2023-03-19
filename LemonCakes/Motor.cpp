#include "Motor.h"

Motor::Motor(uint8_t encoderPin, uint8_t in1Pin, uint8_t in2Pin, uint8_t pwmPin) {
  EncoderCnt = 0;
  EncoderPin = encoderPin;
  IN1Pin = in1Pin;
  IN2Pin = in2Pin;
  PWMPin = pwmPin;
  PWM = 0;
  MeasuredRPM = 0;
  LastEncoderTime = 0;
  Error = 0;
  Proportional = 0;
}

void Motor::setup() {
  pinMode(EncoderPin, INPUT);
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT);
  pinMode(PWMPin, OUTPUT);

  motorStop();

  return;
}

uint8_t Motor::getPWM() {
  return PWM;
}

void Motor::setPWM(uint8_t pwm) {
  PWM = pwm;
  analogWrite(PWMPin, PWM);

  return;
}

uint16_t Motor::getMeasuredRPM() {
  return MeasuredRPM;
}

void Motor::setMeasuredRPM(uint16_t rpm) {
  MeasuredRPM = rpm;

  return;
}

uint16_t Motor::getCommandedRPM() {
  return CommandedRPM;
}

void Motor::setCommandedRPM(uint16_t rpm) {
  CommandedRPM = rpm;

  return;
}

void Motor::RPMCalc() {
  uint32_t time = micros();

  if(LastEncoderTime == 0) { // First encoder count
    LastEncoderTime = time;
    return;
  }

  // Calc speed (with filter)
  uint16_t rpm = 1000000 * 60 / ((time - LastEncoderTime) * 7);
  setMeasuredRPM((uint16_t)(getMeasuredRPM() * 0.9 + rpm * 0.1));

  LastEncoderTime = time;

  return;
}

void Motor::PIDCalc() {
  Error = getCommandedRPM() - getMeasuredRPM();

  return;
}

void Motor::resetPID() {
  setMeasuredRPM(0);
  setCommandedRPM(0);
  Error = 0;
  Proportional = 0;

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

  resetEncoder();
  resetPID();

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

uint32_t Motor::getEncoderCnt() {
  return EncoderCnt;
}