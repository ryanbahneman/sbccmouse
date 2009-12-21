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
//////////////////////////////////////////////////////////
*/


///////////////////////////////////////////////////////////////////////////
//NEEDS OPTIMIZATION 	(no true boolean type for AVR, make an 8-bit struct 
//						with 1-bit flags in it for fwd)
//
//func: rotate Left	
//					fwd -- boolean: if true, runs forward
//					delay -- time between phase change in motor pattern
//					cycles -- how many periods (motor steps) to execute
void rotateLeft(int fwd, int delay, int cycles);




///////////////////////////////////////////////////////////////////////////
//NEEDS OPTIMIZATION 	(no true boolean type for AVR, make an 8-bit struct 
//						with 1-bit flags in it for fwd)
//
//func: rotate Right	
//					fwd -- boolean: if true, runs forward
//					delay -- time between phase change in motor pattern
//					cycles -- how many periods (motor steps) to execute
void rotateRight(int fwd, int delay, int cycles);




///////////////////////////////////////////////////////////////////////////
//func: turn Clock-Wise
//					delay -- time between phase change in motor pattern
//					cycles -- how many periods (motor steps) to execute
void turnCW(int delay, int cycles);




///////////////////////////////////////////////////////////////////////////
//func: turn Counter-Clock-Wise
//					delay -- time between phase change in motor pattern
//					cycles -- how many periods (motor steps) to execute
void turnCCW(int delay, int cycles);




///////////////////////////////////////////////////////////////////////////
//NEEDS OPTIMIZATION 	(no true boolean type for AVR, make an 8-bit struct 
//						with 1-bit flags in it for fwd)
//
//func: "I'm givin it all she's got, captain!"
//					fwd -- boolean: if true, runs forward
//					delay -- time between phase change in motor pattern
//					cycles -- how many periods (motor steps) to execute
void warp5(int fwd, int delay, int cycles);


int main (void)
{		
	turnCW(20, 100);
	turnCCW(20, 90);
	turnCW(20, 80);
	turnCCW(20, 70);
	turnCW(20, 60);
	turnCCW(20, 50);
	turnCW(20, 40);
	turnCCW(20, 30);

	warp5(1, 20, 100);
	warp5(0, 10, 100);
	warp5(1, 5, 100);
	warp5(0, 3, 100);
	warp5(1, 2, 100);
	warp5(0, 1, 100);

	for (int i = 0; i < 45; i++){
		rotateLeft(1, i+5, 30);
		rotateRight(1, i+5, 30);
	}
}




/* /////////////////////////////////////////////////////////////////////////
READ THIS BEFORE LOOKING AT THIS TRASH

notation		explanation					example
a<<b			a, left shifted b bits		1<<5 is b00100000
a|=b			a or b, stored into a		b0001|=b1100 becomes b1101
a&=b			a and b, stored into a		b0001&=b1101 becomes b0001
~a				bitwise NOT of a			~b00101101 becomes b11010010

DDRD:	in order for ports to work, you need to set them for output.

PORTD:	7	6	5				4		3	2	1				0
				^right coil 2	^right coil 1	^left coil 2	^left coil 1
		ex:  b00100001 means right coil 2 is on and left coil 1 is on
///////////////////////////////////////////////////////////////////////// */

void rotateLeft(int fwd, int delay, int cycles){
	int i;
	
	DDRD |= (1<<0)|(1<<1); //Sets PortD 0,1 as ouputs.
	PORTD = 0; //sets all PortD outputs to 0
	
	if (fwd){
		for(i = 0; i < cycles; i++){

			PORTD |= (1<<1);
			_delay_ms (delay);

			PORTD |= (1<<0);
			_delay_ms (delay);

			PORTD &= ~(1<<1);
			_delay_ms (delay);

			PORTD &= ~(1<<0);
			_delay_ms (delay);
		}
	}else{
		for(i = 0; i < cycles; i++){
			PORTD |= (1<<0);
			_delay_ms (delay);

			PORTD |= (1<<1);
			_delay_ms (delay);

			PORTD &= ~(1<<0);
			_delay_ms (delay);

			PORTD &= ~(1<<1);
			_delay_ms (delay);
		}
	}
}


void rotateRight(int fwd, int delay, int cycles){
	int i;
	
	DDRD |= (1<<4)|(1<<5); //Sets PortD 4,5 as ouputs.
	PORTD = 0; //sets all PortD outputs to 0
	
	if (fwd){
		for(i = 0; i < cycles; i++){

			PORTD |= (1<<5);
			_delay_ms (delay);

			PORTD |= (1<<4);
			_delay_ms (delay);

			PORTD &= ~(1<<5);
			_delay_ms (delay);

			PORTD &= ~(1<<4);
			_delay_ms (delay);
		}
	}else{
		for(i = 0; i < cycles; i++){
			PORTD |= (1<<4);
			_delay_ms (delay);

			PORTD |= (1<<5);
			_delay_ms (delay);

			PORTD &= ~(1<<4);
			_delay_ms (delay);

			PORTD &= ~(1<<5);
			_delay_ms (delay);
		}
	}
}



void turnCW(int delay, int cycles){
	int i;
	
	DDRD |= (1<<4)|(1<<5)|(1<<0)|(1<<1); //Sets PortD 0,1,4,5 as ouputs.
	PORTD = 0; //sets all PortD outputs to 0

	for(i = 0; i < cycles; i++){

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
}


void turnCCW(int delay, int cycles){
	int i;

	DDRD |= (1<<4)|(1<<5)|(1<<0)|(1<<1); //Sets PortD 0,1,4,5 as ouputs.
	PORTD = 0; //sets all PortD outputs to 0

	for(i = 0; i < cycles; i++){

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
}

void warp5(int fwd, int delay, int cycles){
	int i;
	
	DDRD |= (1<<4)|(1<<5)|(1<<0)|(1<<1); //Sets PortD 0,1,4,5 as ouputs.
	PORTD = 0; //sets all PortD outputs to 0
	if (fwd){
		for(i = 0; i < cycles; i++){

			PORTD |= (1<<5);
			PORTD |= (1<<1);
			_delay_ms (delay);

			PORTD |= (1<<4);
			PORTD |= (1<<0);
			_delay_ms (delay);

			PORTD &= ~(1<<5);
			PORTD &= ~(1<<1);
			_delay_ms (delay);

			PORTD &= ~(1<<4);
			PORTD &= ~(1<<0);
			_delay_ms (delay);
		}
	}else{
		for(i = 0; i < cycles; i++){
			PORTD |= (1<<4);
			PORTD |= (1<<0);
			_delay_ms (delay);

			PORTD |= (1<<5);
			PORTD |= (1<<1);
			_delay_ms (delay);

			PORTD &= ~(1<<4);
			PORTD &= ~(1<<0);
			_delay_ms (delay);

			PORTD &= ~(1<<5);
			PORTD &= ~(1<<1);
			_delay_ms (delay);
		}
	}
}
