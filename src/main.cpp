#include<avr/io.h>
#include <avr/interrupt.h>

int main() {
  // Begin setup Timer0 - FAST PWM - Non Inverting
  //*********************************************************
  //
  //fast pwm mode                                       : WGM00 =1,  WGM01=1     ----> TCCR0A
  //clear OC0B on compare match and nor inverting output: COM0B1=1, COM0B0=0     ----> TCCR0A
  //clear OC0A on compare match and non inverting output: COM0A1=1, COM0A0=0     ----> TCCR0A
  //Clock PreScale: div 64                              : CS02=0, CS01=1, CS00=1 ----> TCCR0B
  
  //DDRD = _BV(PD6) | _BV(PD5); //Output Mode Timer0 Pins : D5, D6

  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);  
  TCCR0B = _BV(CS01)   | _BV(CS00); 

  OCR0A = 62;
  OCR0B = 31;
  //******************* End setup Timer0 *********************

  //Need for enable interrupt vector ISR(TIMER0_COMPA_vect)
  //TIMSK0 |= _BV(TOIE0);               //TIMSK0 = 0b00000001;    //trigger interrupt when ctr (TCNT0) >= 255 (overflow)
  TIMSK0 |= _BV(OCIE0A) | _BV(OCIE0B);  //TIMSK0 = 0b00000010;    //trigger interrupt when ctr (TCNT0) >= OCR0A and (TCNT0) >= OCR0B
  sei();                                //Enable interrupts()
  //********************************************************
 
  DDRD  |= _BV(PD7) | _BV(PD6) | _BV(PD5) | _BV(PD4);  

  while(1) {  }
  return 1;
}


ISR(TIMER0_COMPA_vect){
  PORTD &= ~_BV(PD4);
}
ISR(TIMER0_COMPB_vect){
  PORTD |=  _BV(PD4);
}

