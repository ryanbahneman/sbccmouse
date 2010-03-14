#include "main.h"


char passNumber = 0;		//0 is center, 1 is left, 2 is right

void initIR(){
	//Setup the ADC
	ADMUX |= (1<<REFS0);//set the refrence voltage to 5V with a capacitor attached to VREF
	ADMUX |= (1<<ADLAR);//left shifts the ADC conversion so it can be read directly from ADCH

	ADCSRA |= (1<<ADPS1) | (1<<ADPS2);// Sets the ADC prescaler to 64, which scalse the 8MHZ system clock to 125KHz
	ADCSRA |= (1 << ADEN); // Enable ADC
	ADCSRA |= (1 << ADSC);//Does a dummy conversion to initialize the adc hardware.
	
	ADCSRA &= ~(1<<ADIE); //Disable the ADC complete interrupt

	DIDR0 |= (1<<ADC0D)|(1<<ADC1D)|(1<<ADC2D);//Disables the digital input on these pins, saving power.
}

int readIR(){

	/*The following block of code sets the adc multiplexer 
	to the corresponding input.
	*/
	int IRval = -1;
	if (passNumber == 0){
		//set ADMUCX to center IR
		ADMUX &= ~(1<<0) & ~(1<<1) & ~(1<<2) & ~(1<<3) & ~(1<<4); //clear MUX 0-4 for ADC0
		ADCSRA |= (1 << ADSC);	//Starts ADC conversion
		while ((ADCSRA & (1<<ADIF))!= (1<<ADIF)){
		}
		IRval = (int) ADCH;	//sets IRval to the ADC value from the IR sensor
	}else if (passNumber == 1){
		//set ADMUCX to left IR
		ADMUX &= ~(1<<0) & ~(1<<1) & ~(1<<2) & ~(1<<3) & ~(1<<4); //clear MUX 0-4
		ADMUX |= (1<<0); 	//set ADC1
		ADCSRA |= (1 << ADSC);	//Starts ADC conversion
		while ((ADCSRA & (1<<ADIF))!= (1<<ADIF)){
		}
		IRval = (int) ADCH;	//sets IRval to the ADC value from the IR sensor
	}else if (passNumber == 2){
		//set ADMUCX to right IR
		ADMUX &= ~(1<<0) & ~(1<<1) & ~(1<<2) & ~(1<<3) & ~(1<<4); //clear MUX 0-4
		ADMUX |= (1<<1); 	//set ADC2
		ADCSRA |= (1 << ADSC);	//Starts ADC conversion
		while ((ADCSRA & (1<<ADIF))!= (1<<ADIF)){
		}
		IRval = (int) ADCH;	//sets IRval to the ADC value from the IR sensor
	} 
	ADCSRA |= (1<<ADIF);	//resets AD flag
	return IRval;
}


int readCenterIR(){
	passNumber = 0;
	return readIR();
}

int readLeftIR(){
	passNumber = 1;
	return readIR();
}

int readRightIR(){
	passNumber = 2;
	return readIR();
}

