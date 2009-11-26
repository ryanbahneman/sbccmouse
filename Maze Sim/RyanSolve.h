
#ifndef _RYANSOLVE_H
#define	_RYANSOLVE_H


#include "MazeDefinitions.h"

int GoFFtoCell(unsigned int map[][16], unsigned int maze[][16], int xStart, int yStart, int xGoal, int yGoal);
int SolveWithFF0(unsigned int maze[][16], int xStart, int yStart, int xGoal, int yGoal);
int SolveWithFF1(unsigned int maze[][16], int xStart, int yStart, int xGoal, int yGoal);


#endif	/* _RYANSOLVE_H */

