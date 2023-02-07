#ifndef Motor_h
#define Motor_h

enum MotorDirection {
  CW,
  CCW
};

class Motor {

private:
  int EncoderCnt;
  int EncoderPin;
  int IN1Pin;
  int IN2Pin;
  int PWMPin;
  int PWM;

public:
  Motor(int encoderPin, int in1Pin, int in2Pin, int pwmPin);
  void setup();

  int getPWM();
  void setPWM(int pwm);

  void setDirection(MotorDirection dir);
  void motorStop();
};

#endif