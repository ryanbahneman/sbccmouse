#ifndef MOTORFUNCS_H_
#define MOTORFUNCS_H_

void initMotorTimers();

void turnCW();	//turns ClockWise 90 degrees
void turnCCW();	//turns CounterClockWise 90 degrees
void startTimerCtrl();	//Gives motor control to the timers
void haltTimerCtrl();	//Stops motors until startTimerCtrl gives motor control back


#endif /* MOTORFUNCS_H_ */
