
#ifndef _MAZEBUILD_H
#define	_MAZEBUILD_H

#include "MazeDefinitions.h"

#include <stdlib.h>


int MakeMaze(unsigned int maze[][16], int loops);
void BuildMaze(unsigned int maze[][16], int xCurrent, int yCurrent, int xStack[], int yStack[], int stackNum);
void InitializeMap(unsigned int map[][16]);



#endif	/* _MAZEBUILD_H */

