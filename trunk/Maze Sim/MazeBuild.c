#include "MazeBuild.h"



int MakeMaze(unsigned int maze[][16], int loops){

	// populate the maze using the lowest four bits; bits (high -> low): WSEN
	//	(1 - wall, 0 - open)

	int xCurrent = 0, yCurrent = 0;
	int xStack[256], yStack[256], stackNum = 0;
	
        int i, j;

	for(i = 0; i < SIDE; i++){
		for(j = 0; j < SIDE; j++){
			maze[i][j] = ALLWALLS;
		}
	}

BuildMaze(maze, xCurrent, yCurrent, xStack, yStack, stackNum);

//Removes all but the wall information
for(i = 0; i < SIDE; i++){
    for(j = 0; j < SIDE; j++){
			maze[i][j] &= ALLWALLS;
    }
}

////////// knock down walls to make loops
while(loops > 0){

int randx = rand()%(SIDE-2) +1;
int randy = rand()%(SIDE-2) +1;
int randdir = rand()%4;
int exit = 0;

do{

		if(maze[randy][randx] & (1<<((randdir)%4))){
			if (randdir%4 == 0){
				maze[randy][randx] &= ~NORTH;
				maze[randy-1][randx] &= ~SOUTH;
				exit = 1;
			}
			else if (randdir%4 == 1){
				maze[randy][randx] &= ~EAST;
				maze[randy][randx+1] &= ~WEST;
				exit = 1;
			}
			else if (randdir%4 == 2){
				maze[randy][randx] &= ~SOUTH;
				maze[randy+1][randx] &= ~NORTH;
				exit = 1;
			}
			else if (randdir%4 == 3){
				maze[randy][randx] &= ~WEST;
				maze[randy][randx-1] &= ~EAST;
				exit = 1;
			}
		}
		else{
			if (randdir < 10)
			randdir += 1;
			else{
				exit = 1;
				loops++;
			}

		}
	}while(exit == 0);
loops -= 1;
}




///make a wall around the center
    maze[7][7] = (NORTH | WEST);
    maze[6][7] |= SOUTH;
    maze[7][6] |= EAST;
    maze[7][8] = (NORTH | EAST);
    maze[6][8] |= SOUTH;
    maze[7][9] |= WEST;
    maze[8][7] = (SOUTH | WEST);
    maze[8][6] |= EAST;
    maze[9][7] |= NORTH;
    maze[8][8] = (SOUTH | EAST);
    maze[8][9] |= WEST;
    maze[9][8] |= NORTH;

//make one exit out of the center
int hole = rand()%8;

if (hole == 0){
maze[7][7] &= ~NORTH;
maze[6][7] &= ~SOUTH;
}
else if (hole == 1){
maze[7][8] &= ~NORTH;
maze[6][8] &= ~SOUTH;
}
else if (hole == 2){
maze[7][8] &= ~EAST;
maze[7][9] &= ~WEST;
}
else if (hole == 3){
maze[8][8] &= ~EAST;
maze[8][9] &= ~WEST;
}
else if (hole == 4){
maze[8][8] &= ~SOUTH;
maze[9][8] &= ~NORTH;
}
else if (hole == 5){
maze[8][7] &= ~SOUTH;
maze[9][7] &= ~NORTH;
}
else if (hole == 6){
maze[8][7] &= ~WEST;
maze[8][6] &= ~EAST;
}
else if (hole == 7){
maze[7][7] &= ~WEST;
maze[7][6] &= ~EAST;
}

FloodFill(maze, GOALX, GOALY);
if((maze[STARTY][STARTX] >> 8) < 255)
return(EXIT_SUCCESS); //0
else
    return(EXIT_FAILURE); //1
}

void BuildMaze(unsigned int maze[][16], int xCurrent, int yCurrent, int xStack[], int yStack[], int stackNum){

	maze[yCurrent][xCurrent] |= TRAVELED;

	int i = 0, dir = 0;

	if (yCurrent - 1 >= 0){
		if((maze[yCurrent - 1][xCurrent] & TRAVELED) == 0){
			dir |= NORTH;
			i+=1;
		}
	}
	if (xCurrent + 1 < SIDE){
		if((maze[yCurrent][xCurrent + 1] & TRAVELED) == 0){
			dir |= EAST;
			i+=1;
		}
        if (yCurrent + 1 < SIDE){
		if((maze[yCurrent + 1][xCurrent] & TRAVELED) == 0){
			dir |= SOUTH;
			i+=1;
		}
	}
	if (xCurrent - 1 >= 0){
		if((maze[yCurrent][xCurrent - 1] & TRAVELED) == 0){
			dir |= WEST;
			i+=1;
		}
	}
	
	}

	if (i > 0){//there is an unvisited neighbor

		//move cell onto stack
		xStack[stackNum] = xCurrent;
		yStack[stackNum] = yCurrent;
		stackNum++;

		//select a direction
		int exit = 0;
		int random = rand()%4;

		do{
			if((1<<(random%4)) & dir){
				dir &= (1<<(random%4));
				exit =1;
			}
			else
				random += 1;
		}while(exit == 0);


		if ( dir == NORTH){
			maze[yCurrent][xCurrent] &= ~NORTH;//turn off wall
			maze[yCurrent - 1][xCurrent] &= ~SOUTH;//turn off wall
			yCurrent -= 1;//set new cell position
		}
		if ( dir == EAST){
			maze[yCurrent][xCurrent] &= ~EAST;
			maze[yCurrent][xCurrent + 1] &= ~WEST;
			xCurrent += 1;
		}
		if ( dir == SOUTH){
			maze[yCurrent][xCurrent] &= ~SOUTH;
			maze[yCurrent + 1][xCurrent] &= ~NORTH;
			yCurrent += 1;
		}
		if ( dir == WEST){
			maze[yCurrent][xCurrent] &= ~WEST;
			maze[yCurrent][xCurrent - 1] &= ~EAST;
			xCurrent -= 1;
		}

        //Recursively calls itself
	BuildMaze(maze, xCurrent, yCurrent, xStack, yStack, stackNum);
	}


	else{
		if (stackNum > 0){
		stackNum -=1;
		xCurrent = xStack[stackNum];
		yCurrent = yStack[stackNum];

		BuildMaze(maze, xCurrent, yCurrent, xStack, yStack, stackNum);
		}

	}

}

void InitializeMap(unsigned int map[][16]){

    int i, j;

    for(i = 0; i < SIDE; i++){
        for(j = 0; j < SIDE; j++){

            if(i == 0){
                if (j == 0)
                    map[i][j] = WEST | NORTH;
                else if (j == SIDE-1)
                    map[i][j] = NORTH | EAST;
                else
                    map[i][j] = NORTH;
            }
            else if(i == SIDE-1){
                 if (j == 0)
                    map[i][j] = SOUTH | WEST;
                else if (j == SIDE-1)
                    map[i][j] = SOUTH | EAST;
                else
                    map[i][j] = SOUTH;
            }
            else{
                if (j == 0)
                    map[i][j] = WEST;
                else if (j == SIDE-1)
                    map[i][j] = EAST;
                else
                    map[i][j] = 0;
            }
        }
      }
}

