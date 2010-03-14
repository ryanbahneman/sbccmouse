#include "main.h"
#include "init.h"
#include "turn.h"
#include "moveCell.h"


const int FASTEST_TIMER_SPEED = 25;	//fastest speed the timer for motors can run at (25-255)
unsigned int MOTOR_R = 0;	//Which cycle the right motor is on, needed by interrupts
unsigned int MOTOR_L = 0;	//Which cycle the left motor is on, needed by interrupts

unsigned int STEPS_TOTAL = 0;




int main (void)
{
	///////////////////////Vital Initialization///////////////////////
	initMotorTimers();
	initIR();
	sei();					//Enable Global Interrupts
	//////////////////////////////////////////////////////////////////

//	turnCCW();	//CounterClockWise (90 deg)
//	turnCW();	//ClockWise	(90 deg)

	moveCell(10);
	return 0;
}






//////////////////////////////////////////////////////////////////////
//////////////////////////////INTERRUPTS//////////////////////////////
//////////////////////////////////////////////////////////////////////


//RELIANT ON GLOBAL
ISR(TIMER0_COMPA_vect){ //Controls Right Motor
	switch(MOTOR_R){	//switches depending on the phase the motor is in.
	case 0:
		PORTD |= (1<<5);
		MOTOR_R++;
	break;

	case 1:
		PORTD |= (1<<4);
		MOTOR_R++;
	break;

	case 2:
		PORTD &= ~(1<<5);
		MOTOR_R++;
	break;

	case 3:
		PORTD &= ~(1<<4);
		MOTOR_R = 0;
	break;
	}
	STEPS_TOTAL++;
	TCNT0 = 0;	//Sets counter to zero; shouldnt be needed
}

//RELIANT ON GLOBAL
ISR(TIMER2_COMPA_vect){	//Controls Left Motor
	switch(MOTOR_L){	//switches depending on the phase the motor is in.
	case 0:
		PORTD |= (1<<1);
		MOTOR_L++;
	break;

	case 1:
		PORTD |= (1<<0);
		MOTOR_L++;
	break;

	case 2:
		PORTD &= ~(1<<1);
		MOTOR_L++;
	break;

	case 3:
		PORTD &= ~(1<<0);
		MOTOR_L = 0;
	break;
	}
	STEPS_TOTAL++;
	TCNT2 = 0;	//Sets counter to zero; shouldnt be needed
}
