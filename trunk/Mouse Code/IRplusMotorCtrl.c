#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#ifndef F_CPU

//define cpu clock speed if not defined

#define F_CPU 1000000

#endif

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
*/



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
*/



/*
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


const int FASTEST_TIMER_SPEED = 30;	//fastest speed the timer for motors can run at

unsigned int MOTOR_R = 0;	//Which cycle the right motor is on, needed by interrupts
unsigned int MOTOR_L = 0;	//Which cycle the left motor is on, needed by interrupts
unsigned int STEPS_TOTAL = 0;


void initMotorTimers();
void startTimerCtrl();	//Gives motor control to the timers
void haltTimerCtrl();	//Stops motors until startTimerCtrl gives motor control back
void turnCW();	//turns ClockWise 90 degrees
void turnCCW();	//turns CounterClockWise 90 degrees
void moveCell(unsigned int numberCells);



int main (void)
{
	initMotorTimers();
	
	_delay_ms (2500);
	turnCW();
	_delay_ms (2500);
	turnCCW();
	while(1)
	{
	} 
	return 0;
	
}

//USES GLOBAL CONSTANT "FASTEST_TIMER_SPEED"
void initMotorTimers(){
	DDRD |= (1<<0)|(1<<1)|(1<<4)|(1<<5);	//Outputs for motors

	TCCR0B |= (1<<WGM02);	//Set Timer0 to CTC mode
	TCCR2B |= (1<<WGM22);	//Set Timer2 to CTC mode

	TIMSK0 = (1<<OCIE0A);	//Output compare on for Timer0
	TIMSK2 = (1<<OCIE2A);	//Output compare on for Timer2

	sei();					//Enable Global Interrupts

	OCR0A = FASTEST_TIMER_SPEED;	//overflow value for Timer0
	OCR2A = FASTEST_TIMER_SPEED;	//overflow value for Timer2

	startTimerCtrl();
}

void startTimerCtrl(){
	TCCR0B |= (1<<CS02);	//Start Timer0 with 256 prescaler
	TCCR2B |= (1<<CS21)|(1<<CS22);	//Start Timer2 with 256 prescaler
}

void haltTimerCtrl(){
	TCCR0B = (1<<WGM02);	//Set Timer0 to stopped CTC mode
	TCCR2B = (1<<WGM22);	//Set Timer2 to stopped CTC mode	
}

void turnCW(){
	unsigned int steps;
	unsigned int tempTimer0 = TCCR0B;	
	unsigned int tempTimer2 = TCCR2B;
	
	int delay = 20;	//Edit this for speed
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
	unsigned int steps;
	unsigned int tempTimer0 = TCCR0B;	
	unsigned int tempTimer2 = TCCR2B;

	int delay = 20;	//Edit this for speed
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


//moves forward a certain number of cells
//USES GLOBAL CONSTANT "FASTEST_TIMER_SPEED"
void moveCell(unsigned int numberCells)
{
	const unsigned int STEPS_IN_A_CELL = 1000;	//Needs to be calculated based on new motor step size and wheel diameter
	const int MAX_DIST = 40;	//Maximum feasible distance from the wall the robot can be (for checking if there is a wall)
	const int CENTERED_DIST = 30;	//Centered distance between the IR and walls (for calibrating when only one wall present)

	int getLeftIR(){	//RYAN, you need to write this.  Integer return would be nice.
		return 0;
	}
	int getRightIR(){	//RYAN, you need to write this.  Integer return would be nice.
		return 0;
	}

	int calibrationFunction(int numWalls, int IRDiff){	//Needs to be worked on.  takes a calibration number from 
														//IR and converts it to a motor slowing timer subtraction
		int timerSubtraction;
		switch(numWalls){
			case 1:
				timerSubtraction = 0;
			break;
			case 2:
				timerSubtraction = 0;
			break;
			default:
				timerSubtraction = 0;
		}
		return timerSubtraction;
	}
	

	int leftVal, rightVal;
	int IRDiff;
	int timerCalibration;

	startTimerCtrl();
	while((STEPS_TOTAL/2) < (STEPS_IN_A_CELL * numberCells)) //average of the steps between the two motors
	{
		leftVal = getLeftIR();
		rightVal = getRightIR();
		

		////BOTH WALLS//////////////////////////////////////////////////////
		if ((rightVal <= MAX_DIST) & (leftVal <= MAX_DIST)){	
			
			IRDiff = leftVal - rightVal;	//negative if close to left, positive if close to right
			
			timerCalibration = calibrationFunction(2, IRDiff);
			
		////LEFT WALL ONLY////////////////////////////////////////////////////
		}else if (leftVal <= MAX_DIST){	

			IRDiff = leftVal - CENTERED_DIST;	//negative if close to left, positive if close to right

			timerCalibration = calibrationFunction(1, IRDiff);

		////RIGHT WALL ONLY///////////////////////////////////////////////////
		}else if (rightVal <= MAX_DIST){

			IRDiff = CENTERED_DIST - rightVal;	//negative if close to left, positive if close to right

			timerCalibration = calibrationFunction(1, IRDiff);

		////NO WALLS//////////////////////////////////////////////////////////
		}else{
			
			IRDiff = 0;  //flying blind
		}

		if (IRDiff < 0){	//turn right

			if (OCR0A > FASTEST_TIMER_SPEED){	//speed up left motor, toss remainder to be slowed on right
				int maxToBeAdded = OCR2A - FASTEST_TIMER_SPEED;

				if (maxToBeAdded >= timerCalibration){
					OCR2A = OCR2A - timerCalibration;
				}else{
					OCR2A = FASTEST_TIMER_SPEED;
					OCR0A = OCR0A + (timerCalibration - maxToBeAdded);
				}
			
			}else{	//slow right motor
				OCR0A = OCR0A + timerCalibration;
			}

			
		}else if (IRDiff > 0){	//turn left

			if (OCR0A > FASTEST_TIMER_SPEED){	//speed up right motor, toss remainder to be slowed on left
				int maxToBeAdded = OCR0A - FASTEST_TIMER_SPEED;

				if (maxToBeAdded >= timerCalibration){
					OCR0A = OCR0A - timerCalibration;
				}else{
					OCR0A = FASTEST_TIMER_SPEED;
					OCR2A = OCR2A + (timerCalibration - maxToBeAdded);
				}
			}else {	//slow left motor
				OCR2A = OCR2A + timerCalibration;
			}

		}else{	//assume the robot is going straight, set timers to full
			OCR0A = FASTEST_TIMER_SPEED;
			OCR2A = FASTEST_TIMER_SPEED;
			//advanced code: have a way to make sure that the robot is definately oriented 
			//correctly and not going skewed, just happening to take an IR sample when 
			//left and right samples are the same
		}

	}




	haltTimerCtrl();
	STEPS_TOTAL = 0;
}




/*

////BOTH WALLS//////////////////////////////////////////////////////
		if ((rightVal <= MAX_DIST) & (leftVal <= MAX_DIST)){	
			
			IRDiff = leftVal - rightVal;	//negative if close to left, positive if close to right
			
			timerCalibration = calibrationFunction(2, IRDiff);
			
			if (IRDiff < 0){	//turn right

				if (OCR0A > FASTEST_TIMER_SPEED){	//speed up left motor, toss remainder to be slowed on right
					int maxToBeAdded = OCR2A - FASTEST_TIMER_SPEED;

					if (maxToBeAdded >= timerCalibration){
						OCR2A = OCR2A - timerCalibration;
					}else{
						OCR2A = FASTEST_TIMER_SPEED;
						OCR0A = OCR0A + (timerCalibration - maxToBeAdded);
					}
				
				}else{	//slow right motor
					OCR0A = OCR0A + timerCalibration;
				}

				
			}else if (IRDiff > 0){	//turn left

				if (OCR0A > FASTEST_TIMER_SPEED){	//speed up right motor, toss remainder to be slowed on left
					int maxToBeAdded = OCR0A - FASTEST_TIMER_SPEED;

					if (maxToBeAdded >= timerCalibration){
						OCR0A = OCR0A - timerCalibration;
					}else{
						OCR0A = FASTEST_TIMER_SPEED;
						OCR2A = OCR2A + (timerCalibration - maxToBeAdded);
					}
				}else {	//slow left motor
					OCR2A = OCR2A + timerCalibration;
				}

			}else{	//assume the robot is going straight, set timers to full
				OCR0A = FASTEST_TIMER_SPEED;
				OCR2A = FASTEST_TIMER_SPEED;
				//advanced code: have a way to make sure that the robot is definately oriented 
				//correctly and not going skewed, just happening to take an IR sample when 
				//left and right samples are the same
			}
*/




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
