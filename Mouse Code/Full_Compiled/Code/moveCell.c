#include "main.h"
#include "irFuncs.h"
#include "motorFuncs.h"
#include <stdlib.h>





//moves forward a certain number of cells
//USES GLOBAL CONSTANT "FASTEST_TIMER_SPEED"
void moveCell(unsigned int numberCells)
{
	const unsigned int STEPS_IN_A_CELL = 1000;	//Needs to be calculated based on new motor step size and wheel diameter
	const int MAX_DIST = 60;	//Maximum feasible distance from the wall the robot can be (for checking if there is a wall)
	const int CENTERED_DIST = 99;	//Centered distance between the IR and walls (for calibrating when only one wall present)
	const int NUM_SAMPLES = 200;	//Number of IR samples to take to average

	int calibrationFunction(int numWalls, int IRDiff){	//Needs to be worked on.  takes a calibration number from 
														//IR and converts it to a motor slowing timer subtraction
		int timerSubtraction;
		switch(numWalls){
			case 1:
			/*
				if(abs(IRDiff) < 10){
					timerSubtraction = 1;
				}else if(abs(IRDiff) < 20){
					timerSubtraction = 2;
				}else if(abs(IRDiff) < 30){
					timerSubtraction = 3;
				}else{
					timerSubtraction = 4;
				}
				*/
				timerSubtraction = 0;
			break;
			case 2:
				if(abs(IRDiff) < 10){
					timerSubtraction = 1;
				}else if(abs(IRDiff) < 30){
					timerSubtraction = 3;
				}else if(abs(IRDiff) < 50){
					timerSubtraction = 5;
				}else{
					timerSubtraction = 9;
				}
			break;
			default:
				timerSubtraction = 0;
		}
		return timerSubtraction;
	}
	

	int leftVal, rightVal;
	int leftValAry[NUM_SAMPLES];
	int rightValAry[NUM_SAMPLES];
	int IRDiff;
	int timerCalibration;


	startTimerCtrl();
	while((STEPS_TOTAL/2) < (STEPS_IN_A_CELL * numberCells)) //average of the steps between the two motors
	{
		{
			int i;
			for (i = 0; i < NUM_SAMPLES; i++){
				leftValAry[i] = readLeftIR();
				rightValAry[i] = readRightIR();
			}

			leftVal = 0;
			rightVal = 0;
			for (i = 0; i < NUM_SAMPLES; i++){
				leftVal += leftValAry[i];
				rightVal += rightValAry[i];
			}
			leftVal = leftVal/NUM_SAMPLES;
			rightVal = leftVal/NUM_SAMPLES;
		}
		

		////BOTH WALLS//////////////////////////////////////////////////////
		if ((rightVal >= MAX_DIST) & (leftVal >= MAX_DIST)){	
			
			IRDiff = rightVal - leftVal;	//negative if close to left, positive if close to right
			
			timerCalibration = calibrationFunction(2, IRDiff);
			
		////LEFT WALL ONLY////////////////////////////////////////////////////
		}else if (leftVal >= MAX_DIST){	

			IRDiff = CENTERED_DIST - leftVal;	//negative if close to left, positive if close to right

			timerCalibration = calibrationFunction(1, IRDiff);

		////RIGHT WALL ONLY///////////////////////////////////////////////////
		}else if (rightVal >= MAX_DIST){

			IRDiff = rightVal - CENTERED_DIST;	//negative if close to left, positive if close to right

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
