#include "Timer.h"
#include "IMU.h"

void setupTimer() {
  cli();

  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 6249;// = (16*10^6) / (1*256) - 1 (must be <65536)
  // OCR1A = 15624;// = (16*10^6) / (1*256) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 256 prescaler
  TCCR1B |= (1 << CS12);  
  // TCCR1B |= (1 << CS12) | (1 << CS10); 
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();

  return;
}

ISR(TIMER1_COMPA_vect){ //timer1 interrupt 10Hz
  calcAbsGyro();
}