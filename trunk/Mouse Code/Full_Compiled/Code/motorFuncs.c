#include "main.h"
#include <util/delay.h>

/*
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

//USES GLOBAL CONSTANT "FASTEST_TIMER_SPEED"
void initMotorTimers(){
	DDRD |= (1<<0)|(1<<1)|(1<<4)|(1<<5);	//Outputs for motors

	TCCR0B |= (1<<WGM02);	//Set Timer0 to CTC mode
	TCCR2B |= (1<<WGM22);	//Set Timer2 to CTC mode

	TIMSK0 = (1<<OCIE0A);	//Output compare on for Timer0
	TIMSK2 = (1<<OCIE2A);	//Output compare on for Timer2

	OCR0A = FASTEST_TIMER_SPEED;	//overflow value for Timer0
	OCR2A = FASTEST_TIMER_SPEED;	//overflow value for Timer2
}

void turnCW(){	
	int delay = 20;	//Edit this for speed
	
	unsigned int steps;
	unsigned int tempTimer0 = TCCR0B;	
	unsigned int tempTimer2 = TCCR2B;
	
	PORTD = 0; //sets all PortD outputs to 0
	TCCR0B = (1<<WGM02);	//Set Timer0 to stopped CTC mode
	TCCR2B = (1<<WGM22);	//Set Timer2 to stopped CTC mode
	for(steps = 0; steps < 39; steps++){

			PORTD |= (1<<1);
			PORTD |= (1<<4);
			_delay_ms (delay);

			PORTD |= (1<<0);
			PORTD |= (1<<5);
			_delay_ms (delay);

			PORTD &= ~(1<<1);
			PORTD &= ~(1<<4);
			_delay_ms (delay);

			PORTD &= ~(1<<0);
			PORTD &= ~(1<<5);
			_delay_ms (delay);
		}
	TCCR0B = tempTimer0;	//Reset Timer0 with previous settings
	TCCR2B = tempTimer2;	//Reset Timer2 with previous settings
}

void turnCCW(){
	int delay = 20;	//Edit this for speed

	unsigned int steps;
	unsigned int tempTimer0 = TCCR0B;	
	unsigned int tempTimer2 = TCCR2B;
	
	PORTD = 0; //sets all PortD outputs to 0
	TCCR0B = (1<<WGM02);	//Set Timer0 to stopped CTC mode
	TCCR2B = (1<<WGM22);	//Set Timer2 to stopped CTC mode
	for(steps = 0; steps < 39; steps++){

			PORTD |= (1<<5);
			PORTD |= (1<<0);
			_delay_ms (delay);

			PORTD |= (1<<4);
			PORTD |= (1<<1);
			_delay_ms (delay);

			PORTD &= ~(1<<5);
			PORTD &= ~(1<<0);
			_delay_ms (delay);

			PORTD &= ~(1<<4);
			PORTD &= ~(1<<1);
			_delay_ms (delay);
		}
	TCCR0B = tempTimer0;	//Reset Timer0 with previous settings
	TCCR2B = tempTimer2;	//Reset Timer2 with previous settings
}

void startTimerCtrl(){
	TCCR0B |= (1<<CS00)|(1<<CS02);	//Start Timer0 with 1024 prescaler
	TCCR2B |= (1<<CS20)|(1<<CS21)|(1<<CS22);	//Start Timer2 with 1024 prescaler
}

void haltTimerCtrl(){
	TCCR0B = (1<<WGM02);	//Set Timer0 to stopped CTC mode
	TCCR2B = (1<<WGM22);	//Set Timer2 to stopped CTC mode	
}
