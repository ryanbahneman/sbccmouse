/*This Isn't completed, but I wanted to throw up what I had.
We need to figure out how the program is going to flow so I 
can talior these functions to work with the code.*/

#include<avr/io.h>
#include<avr/interrupts.h>

char IRpassNumber = 0, centerIR, leftIR, rightIR;


void InitializeIR(){

/*
Setup the ADC
*/

ADMUX |= (1<<REFS0);//set the refrence voltage to 5V with a capacitor attached to VREF
ADMUX |= (1<<ADLAR);//left shifts the ADC conversion so it can be read directly from ADCH

ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);// Sets the ADC prescaler to 128, which scalse the 16MHZ system clock to 125KHz
ADCSRA |= (1 << ADEN); // Enable ADC
ADCSRA |= (1 << ADSC);//Does a dummy conversion to initialize the adc hardware.
ADCSRA |=(1<<ADIE); //Enable the ADC complete interrupt

//DIDR0 should be used to reduce power consumption when we know exactly what pins we will be using for the IR

}




void ReadIR(){

if (passNumber == 0){
//set ADMUCX to center IR
} 
else if (passNumber == 1){
//set ADMUCX to left IR
} 
else if (passNumber == 2){
//set ADMUCX to right IR
} 


ADCSRA |= (1 << ADSC);//Starts ADC conversion


/*

in the ADMUX register:
MUX 4 - 0
00000 ADC0
00001 ADC1
00010 ADC2
00011 ADC3
00100 ADC4
00101 ADC5
00110 ADC6
00111 ADC7

I'm not sure what pins the adc are going to end up on, so I'm leaving this part for now.

*/
}


ISR(ADC_vect)// When ADC completes
{

if (passNumber == 0){
centerIR = ADCH;//sets centerIR to the ADC value from the IR sensor
} 
else if (passNumber == 1){
leftIR = ADCH;//sets leftIR to the ADC value from the IR sensor
} 
else if (passNumber == 2){
rightIR = ADCH;//sets rightIR to the ADC value from the IR sensor
} 


IRpassNumber++;

}


