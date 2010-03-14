#include <avr/io.h>
#include <avr/interrupt.h>


#ifndef F_CPU

//define cpu clock speed if not defined

#define F_CPU 8000000

#endif


#ifndef MAIN_H_
#define MAIN_H_

extern const int FASTEST_TIMER_SPEED;	//fastest speed the timer for motors can run at

extern unsigned int STEPS_TOTAL;

#endif /* MAIN_H_ */

/*
///////////////Pin Configuration//////////////////////////
-14 left motor (PD0)
-15 left motor (PD1)

-18 right motor (PD4)
-19 right motor (PD5)

-22	LED1 (PC0)
-23	LED2 (PC1)
-24	LED3 (PC2)

-40 fwd IR (PA0)
-39 right IR (PA1)
-38 left IR (PA2)
//////////////////////////////////////////////////////////

/////////////Timer0 Configuration/////////////////////////
TCCR0B values for CS00, CS01, CS02 (shown as binary)

000		Clock Stop
001		Clock frequency
010		Clock/8 from prescaler
011		Clock/64 from prescaler
100		Clock/256 from prescaler
101		Clock/1024 from prescaler
//////////////////////////////////////////////////////////

/////////////Timer2 Configuration/////////////////////////
TCCR2B values for CS20, CS21, CS22 (shown as binary)

000		Clock Stop
001		Clock frequency
010		Clock/8 from prescaler
011		Clock/32 from prescaler
100		Clock/64 from prescaler
101		Clock/128 from prescaler
110		Clock/256 from prescaler
111		Clock/1024 from prescaler
//////////////////////////////////////////////////////////
*/
