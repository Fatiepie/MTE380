#include "MotorControl.h"

#define LEFT_ENCODER 2
#define LEFT_IN1 7
#define LEFT_IN2 8
#define LEFT_PWM 9

#define RIGHT_ENCODER 3
#define RIGHT_IN1 5
#define RIGHT_IN2 6
#define RIGHT_PWM 10

MotorControl* motors = new MotorControl(LEFT_ENCODER, LEFT_IN1, LEFT_IN2, LEFT_PWM, RIGHT_ENCODER, RIGHT_IN1, RIGHT_IN2, RIGHT_PWM);

void setup() {
  // put your setup code here, to run once:
  motors->setup();

  // motors->driveForward();
}

void loop() {
  // put your main code here, to run repeatedly:

}
