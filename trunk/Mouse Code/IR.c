/*This Isn't completed, but I wanted to throw up what I had.
We need to figure out how the program is going to flow so I 
can talior these functions to work with the code.*/


/*
WHEN WE RESOLDER THE IR PINS!!!!!!!!!
SET UP THE CENTER ON ADC0
LEFT ON ADC1
AND RIGHT ON ADC2
*/

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

//DIDR0 |= (1<<ADC0D)|(1<<ADC1D)|(1<<ADC2D);//Disables the digital input on these pins, saving power.
}




void ReadIR(){

/*The following block of code sets the adc multiplexer 
to the corresponging input.
*/

if (passNumber == 0){
//set ADMUCX to center IR
ADMUX &= ~(1<<ADC0) & ~(1<<ADC1) & ~(1<<ADC2);//clears the ADMUX0:2 bits
}
else if (passNumber == 1){
//set ADMUCX to left IR
ADMUX &= ~(1<<ADC0) & ~(1<<ADC1) & ~(1<<ADC2);//clears the ADMUX0:2 bits
ADMUX |= (1<<ADC0);
} 
else if (passNumber == 2){
//set ADMUCX to right IR
ADMUX &= ~(1<<ADC0) & ~(1<<ADC1) & ~(1<<ADC2);//clears the ADMUX0:2 bits
ADMUX |= (1<<ADC1);
} 


ADCSRA |= (1 << ADSC);//Starts ADC conversion


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


