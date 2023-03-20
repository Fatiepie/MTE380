#include "Motor.h"

Motor::Motor(uint8_t encoderPin, uint8_t in1Pin, uint8_t in2Pin, uint8_t pwmPin) {
  EncoderCnt = 0;
  EncoderPin = encoderPin;
  IN1Pin = in1Pin;
  IN2Pin = in2Pin;
  PWMPin = pwmPin;
  PWM = 0;
  MeasuredRPM = 0;
  ActualCommandedRPM = 0;
  NominalCommandedRPM = 0;
  LastEncoderTime = 0;
  Error = 0;
  Proportional = 0;
  Integral = 0;
}

void Motor::setup() {
  pinMode(EncoderPin, INPUT);
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT);
  pinMode(PWMPin, OUTPUT);

  motorStop();

  return;
}

int16_t Motor::getPWM() {
  return PWM;
}

void Motor::setPWM(int16_t pwm) {
  PWM = pwm;
  analogWrite(PWMPin, PWM);

  return;
}

int16_t Motor::getMeasuredRPM() {
  return MeasuredRPM;
}

void Motor::setMeasuredRPM(int16_t rpm) {
  MeasuredRPM = rpm;

  return;
}

int16_t Motor::getActualCommandedRPM() {
  return ActualCommandedRPM;
}

int16_t Motor::getNominalCommandedRPM() {
  return NominalCommandedRPM;
}

void Motor::setActualCommandedRPM(int16_t rpm) {
  ActualCommandedRPM = rpm;

  return;
}

void Motor::setCommandedRPM(int16_t rpm) {
  ActualCommandedRPM = rpm;
  NominalCommandedRPM = rpm;

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
  Error = getActualCommandedRPM() - getMeasuredRPM();

  // Calc proportional
  Proportional = Error * KP;

  // Calc Integral
  Integral += 100000 * Error * KI / 100;

  // Calc new PWM
  PWM = (int16_t)Proportional + (int16_t)(Integral / 100000);

  if(PWM > 255) {
    PWM = 255;
  }
  else if(PWM < 0) {
    PWM = 0;
  }

  analogWrite(PWMPin, PWM);

  return;
}

void Motor::resetPID() {
  MeasuredRPM = 0;
  ActualCommandedRPM = 0;
  NominalCommandedRPM = 0;
  Error = 0;
  Proportional = 0;
  Integral = 0;

  return;
}

int32_t Motor::getError() {
  return Error;
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
  PWM = 0;
  analogWrite(PWMPin, PWM);

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
  LastEncoderTime = 0;

  return;
}

uint32_t Motor::getEncoderCnt() {
  return EncoderCnt;
}