For all intents and purposes, the only headers that should be used for programming alorithms are those that are  included in the current main.c (main.h init.h turn.h moveCell.h)
The only functions you will likely need are:
	turnCCW();
	turnCW();
	moveCell(numCells);
just make sure to do the includes and be sure to include these lines before any other code in main:
	initMotorTimers();
	initIR();
	sei();
unless you are going to be doing something not involving motor control or IR reading.

The current headers and their descriptions:

main.h		--Main includes required for AVR to work.  Includes useful commented configuration info.
init.h  	--Minimal include that uses the init function from irFuncs.c and the init function from motorFuncs.c
turn.h		--Minimal include for turn functions from motorFuncs.c
motorFuncs.h	--All motor functions for manipulating control, initialzation, and turning
irFuncs.h	--All IR functions for reading and initialization.  DO NOT USE readIR() unless you know what's up.
moveCell.h	--Header for exclusively moveCell.c . It's just that cool.