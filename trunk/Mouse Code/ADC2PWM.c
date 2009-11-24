#include <avr/io.h> 
#include <avr/interrupt.h> 

int main (void) 

{
/*
///////////////Pin Configuration//////////////////////////
Pin 1. N/C (reset pin)
Pin 2:3. (N/C eventually a 16 MHz Crystal will be added)
Pin 4. GND
Pin 5. PB0 / OC0A (Hooked up to an H-Bridge and when High (assuming Pin 6 is low) drives the motor forward)
Pin 6. PB1 / OC0B (Hooked up to an H bridge and when High (assuming Pin 5 is low) drives the motor reverse)
Pin 7. PB2 / ADC1 (used to measure voltage from a potentiometer) 
Pin 8. VCC
//////////////////////////////////////////////////////////
*/



//PWM

DDRB |= (1<<1)|(1<<2); //Set PDB1:2 as ouputs
PORTB =0; //sets all output to 0

TCCR0A |= (1<<WGM00); //Sets the Mode of the timer to be Phase Correct PWM w/TOP=MAX
TCCR0B |= (1<<CS00); // Sets the Clock for the timer to be the I/O clock.

// ADC

ADCSRA |= (1<<ADPS1) | (1<<ADPS0);// Sets the ADC prescaler to 8, which makes the ADC clock rate 1/8 of the 1MHZ system clock (125KHz)
ADMUX |= (1<<ADLAR);// Left adjusts the output from the DAC so the 8 MSB are found in ADCH
ADMUX |= (1<<MUX0); // Sets the ADC input voltage to ADC1 (pin 7)
ADCSRA |= (1 << ADATE);  // Set ADC to Free-Running Mode 
ADCSRA |= (1 << ADEN);  // Enable ADC


ADCSRA |=(1<<ADIE); //Enable the ADC complete interrupt
sei();//Enables Interrupts 

ADCSRA |= (1 << ADSC);  //Starts first ADC conversion


for(;;)//endless loop
{
}

}

ISR(ADC_vect)// When ADC completes
{
// 0<=ADCH <= 255
// low = 0:127
// high = 128:255

//Note: in TCCR0A, setting COM0A1:0 and COM0B1:0 changes how the pins react
//all 0's (default) means that the pins function as normal I/O's
//1 on COM0n1 = Clear OC0A/OC0B on Compare Match when up-counting. Set OC0A/OC0B on Compare Match when down-counting.
// 1 on both = opposite of above. aka inverse PWM

if (ADCH > 127) // ADCH = register that ADC value is held
{
OCR0A = ((ADCH - 128)*2);//sets the Output Compare Register to correspond to the measured voltage
TCCR0A &= ~((1<<COM0B0)|(1<<COM0B1)); //removes PWM from OC0B (Pin 6 is now low)
TCCR0A |= (1<<COM0A1);//Turns on OC0A to PWM mode
}

else // ADCH is less than half (motor is in reverse)
{
OCR0B = ((ADCH*2)+1);//sets the Output Compare Register to correspond to the measured voltage
TCCR0A &= ~(1<<COM0A1); //removes PWM from OC0A (Pin 5 is now low)
TCCR0A |= (1<<COM0B0)|(1<<COM0B1);//Turns on OC0B to inverse PWM mode
}


}
