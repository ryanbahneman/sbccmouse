/* Maze Solve
 *by Ryan
 *
 *sorry for the crappy commenting job,it's 1 AM and i have a morning class,
 * but I wanted to throw this up before I Leave tomorrow, so you can possibly
 * use some of the code.
 *
 *this program is still in the works, but you are welcome to use it as a base
 *for your own algorithms.
 *
 *eventually It will randomly generate the maze, but since we switched the way
 *we are storing the wall information, that code isn't ready yet. It will also
 *someday contain an option to run a rediculous # of simulations.
 *
 *If you are interested in coding in any of those, feel free :)
 */
#include <stdlib.h>
#include <stdio.h>

#define NORTH 1     //00000001
#define EAST 2      //00000010
#define SOUTH 4     //00000100
#define WEST 8      //00001000
#define ALLWALLS 15 //00001111
#define TRAVELED 16 //00010000


void FloodFill(unsigned int maze[][16], int side, int xGoal, int yGoal);
int SolveWithFF0(unsigned int map[][16], unsigned int maze[][16], int side, int xStart, int yStart, int xGoal, int yGoal);
int SolveWithFF1(unsigned int map[][16], unsigned int maze[][16], int side, int xStart, int yStart, int xGoal, int yGoal);
int GoFFtoCell(unsigned int map[][16], unsigned int maze[][16], int side, int xStart, int yStart, int xGoal, int yGoal);

int main (void) {


//A Static maze for testing
unsigned int maze[16][16] ={{13, 3, 9, 5, 5, 3, 9, 3, 13, 1, 5, 5, 3, 9, 5, 3},
{11, 12, 6, 11, 9, 6, 10, 10, 9, 6, 11, 9, 6, 10, 9, 2},
{8, 5, 5, 2, 10, 9, 6, 12, 2, 9, 2, 12, 3, 10, 10, 10},
{14, 9, 1, 6, 10, 10, 9, 5, 0, 0, 4, 7, 10, 10, 10, 10},
{9, 6, 10, 9, 4, 4, 2, 9, 2, 12, 5, 5, 4, 2, 10, 14},
{10, 9, 6, 8, 1, 3, 14, 10, 14, 9, 3, 9, 5, 2, 12, 3},
{10, 12, 3, 12, 6, 12, 3, 12, 5, 6, 12, 4, 1, 6, 9, 2},
{12, 3, 12, 5, 5, 7, 10, 9, 1, 1, 3, 9, 4, 5, 6, 10},
{9, 2, 9, 5, 5, 5, 2, 12, 6, 10, 10, 10, 9, 1, 7, 10},
{10, 10, 10, 13, 1, 3, 12, 5, 7, 10, 12, 6, 10, 12, 1, 6},
{10, 10, 12, 3, 12, 0, 1, 5, 3, 8, 3, 13, 2, 13, 0, 3},
{10, 12, 3, 12, 5, 6, 12, 3, 12, 6, 8, 3, 8, 5, 4, 2},
{12, 5, 4, 5, 1, 1, 7, 10, 9, 3, 14, 10, 12, 3, 9, 6},
{9, 5, 3, 9, 6, 14, 9, 6, 10, 12, 3, 10, 9, 2, 10, 11},
{8, 3, 12, 6, 9, 5, 6, 13, 2, 9, 6, 10, 10, 14, 12, 2},
{14, 12, 5, 5, 4, 5, 5, 5, 6, 12, 5, 6, 12, 5, 5, 6},
};
//initializing the mouse's map to a blank one with borders
unsigned int map[16][16] = {{9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
       			{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
			{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
			{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
			{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
			{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
			{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
			{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
			{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
			{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
			{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
			{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
			{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
			{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
			{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
			{12,4,4,4,4,4,4,4,4,4,4,4,4,4,4,6}};

int side = 16;// 16x16 maze
int goal = 7, start = 0; //start and finish locations
int steps0, steps1;//the number of steps for each algorithm

steps0 = SolveWithFF0( map, maze, side, start, start, goal, goal);

steps1 = SolveWithFF1( map, maze, side, start, start, goal, goal);

	printf("Number of Steps for FF0: %d \n", steps0);
        printf("Number of Steps for FF1: %d \n", steps1);
        FloodFill(maze, side, goal, goal);// to get the shortest possible route to the center
	printf("Shortest Route: %d \n",((maze[0][0] & 65280) >> 8));
        //((maze[0][0] & 65280) >> 8) = only look that top byte of maze

        return(0);
}

int SolveWithFF0(unsigned int map[][16], unsigned int maze[][16], int side, int xStart, int yStart, int xGoal, int yGoal){
/* This is a simple solution to find the fastest route
 *It uses floodfill everytime it moves to a new cell and updates a wall.
 *when it finds the center it retraces it's steps (not acutally coded here [I simply
 *multiplied the number of steps to the center by 2 and reset the starting location
 *to 0,0])
 *This is extremely inefficient and was only created as a benchmark
 */

int steps, totalSteps = 0;

do{

steps = GoFFtoCell(map, maze, side, xStart, yStart, xGoal, yGoal);
/*GoFFtoCell is a function that moves the mouse from start to the goal, "reflooding"
 *the maze every time it moves to a new cell, and choosing the lowest value neighbor.
 */

totalSteps += 2*steps;//accounting for the backtracking to the center

}while( steps != ((map[yStart][xStart] & 65280) >> 8));
//checks to see if the path traveled is the same as the value of the start cell.
//if they match, the shortest route is guarnteed.

return totalSteps;
}

int SolveWithFF1(unsigned int map[][16], unsigned int maze[][16], int side, int xStart, int yStart, int xGoal, int yGoal){
/*This solution is slightly more elegant.
 *once it reaches the center it switches the goal and start location and tries to
 * get back to the center in as few steps as possible.
 *
 *while this is much improved over FF0 there is still room for improvement
 */

//int yCurrent = yStart, xCurrent = xStart;
int steps, totalSteps = 0;


FloodFill(map, side, xGoal, yGoal);

do{
//Same as FF0, but tries to find a quicker way back
steps = GoFFtoCell(map, maze, side, xStart, yStart, xGoal, yGoal);
totalSteps += steps;
steps = GoFFtoCell(map, maze, side, xGoal, yGoal, xStart, yStart);
totalSteps += steps;

//This extra floodfill is necessary because the maze is currently floodfilled assuming
//that the starting cell in the goal
FloodFill(map, side, xGoal, yGoal);
}while( steps != ((map[yStart][xStart] & 65280) >> 8));
//checks to see if the path traveled is the same as the value of the start cell.
//if they match, the shortest route is guarnteed.

return totalSteps;

}

int GoFFtoCell(unsigned int map[][16], unsigned int maze[][16], int side, int xStart, int yStart, int xGoal, int yGoal){
/*a function that moves the mouse from start to the goal, "reflooding"
 *the maze every time it moves to a new cell, and choosing the lowest value neighbor.
 */
    int steps = 0, dir;
    unsigned int neighbor[4];
    int yCurrent = yStart, xCurrent = xStart;

     // initially Flood the maze with new distance values
	FloodFill(map, side, xGoal, yGoal);
    
    do{

        if ((map[yCurrent][xCurrent] & TRAVELED) == 0){
           
//(1) Update the wall map

/*This checks for walls and updates map acordingly */
	if (yCurrent > 0){
		if ((maze[yCurrent][xCurrent] & NORTH) != 0){
			map[yCurrent][xCurrent] |= NORTH;
			map[yCurrent - 1][xCurrent] |= SOUTH;
		}
	}
	else
		map[yCurrent][xCurrent] |= NORTH;



	if (xCurrent < (side - 1)){
		if ((maze[yCurrent][xCurrent] & EAST) != 0){
			map[yCurrent][xCurrent] |= EAST;
			map[yCurrent][xCurrent + 1] |= WEST;
		}
	}
	else
		map[yCurrent][xCurrent] |= EAST;



	if (yCurrent < (side - 1)){
		if ((maze[yCurrent][xCurrent] & SOUTH) != 0){
			map[yCurrent][xCurrent] |= SOUTH;
			map[yCurrent + 1][xCurrent] |= NORTH;
		}
	}
	else
		map[yCurrent][xCurrent] |= SOUTH;



	if (xCurrent > 0){
		if ((maze[yCurrent][xCurrent] & WEST) != 0){
			map[yCurrent][xCurrent] |= WEST;
			map[yCurrent][xCurrent - 1] |= EAST;
		}
	}
	else
		map[yCurrent][xCurrent] |= WEST;

    

//(2) Flood the maze with new distance values
	FloodFill(map, side, xGoal, yGoal);



map[yCurrent][xCurrent] |= TRAVELED;
        }

//(3) Decide which neighboring cell has the lowest distance value
const int MAX = 255;

	if (yCurrent > 0){
		if ((map[yCurrent][xCurrent] & NORTH) == 0)
			neighbor[0] = ((map[yCurrent - 1][xCurrent]& 65280) >> 8);
		else
			neighbor[0] = MAX;
	}
	else
			neighbor[0] = MAX;

	if (xCurrent < (side - 1)){
		if ((map[yCurrent][xCurrent] & EAST) == 0)
			neighbor[1] = ((map[yCurrent][xCurrent + 1] & 65280) >> 8);
		else
			neighbor[1] = MAX;
	}
	else
			neighbor[1] = MAX;

	if (yCurrent < (side - 1)){
		if ((map[yCurrent][xCurrent] & SOUTH) == 0)
			neighbor[2] = ((map[yCurrent + 1][xCurrent] & 65280) >> 8);
		else
			neighbor[2] = MAX;
	}
	else
			neighbor[2] = MAX;

	if (xCurrent > 0){
		if ((map[yCurrent][xCurrent] & WEST) == 0)
			neighbor[3] = ((map[yCurrent][xCurrent - 1] & 65280) >> 8);
		else
			neighbor[3] = MAX;
	}
	else
			neighbor[3] = MAX;


int i, lowest = MAX;
	for( i = 0; i < 4; i++){
		if (neighbor[i] < lowest){
			dir = i;
			lowest = neighbor[i];
		}
	}

//(4) Move to the neighboring cell with the lowest distance value

if(dir == 0)
	yCurrent--;
else if(dir == 1)
	xCurrent++;
else if(dir == 2)
	yCurrent++;
else if(dir == 3)
	xCurrent--;


steps +=1;

}while(yCurrent != yGoal || xCurrent != xGoal);
//checks to see if it is made it to the goal
    
return steps;
}


void FloodFill(unsigned int maze[][16], int side, int xGoal, int yGoal){
int i, j;
	for( i = 0; i < side; i++){
		for( j = 0; j < side; j++){
			maze[i][j] |= (255<<8);
		}
	}
	int level = 0;
		const int MAX = 16*16-1;
		int currentLevel[MAX][2];
		int nextLevel[MAX][2];
		int count;
		int endY = yGoal;
		int endX = xGoal;
		int current;
		currentLevel[0][0] = endY;
		currentLevel[0][1] = endX;
		int currentLevelSize = 1;
		int nextLevelSize = 0;
		   do {
               count = 0;
               nextLevelSize=0;
               for( i=0;i<currentLevelSize;i++) {
                        if (((maze[currentLevel[i][0]][currentLevel[i][1]] & 65280) >> 8) == MAX) {
                               current = level<<8;
                               maze[currentLevel[i][0]][currentLevel[i][1]] &=255;
                               maze[currentLevel[i][0]][currentLevel[i][1]] |= current;
                               if((maze[currentLevel[i][0]][currentLevel[i][1]] & 1) != 1) {
                                       nextLevel[count][0] = currentLevel[i][0] - 1;
                                       nextLevel[count][1] = currentLevel[i][1];
                                       count++;
                                       nextLevelSize++;
                               }
                               if((maze[currentLevel[i][0]][currentLevel[i][1]] & 2) != 2) {
                                       nextLevel[count][0] = currentLevel[i][0];
                                       nextLevel[count][1] = currentLevel[i][1]+1;
                                       count++;
                                       nextLevelSize++;
                               }
                               if((maze[currentLevel[i][0]][currentLevel[i][1]] & 4) != 4) {
                                       nextLevel[count][0] = currentLevel[i][0]+1;
                                       nextLevel[count][1] = currentLevel[i][1];
                                       count++;
                                       nextLevelSize++;
                               }
                               if((maze[currentLevel[i][0]][currentLevel[i][1]] & 8) != 8) {
                                       nextLevel[count][0] = currentLevel[i][0];
                                       nextLevel[count][1] = currentLevel[i][1] - 1;
                                       count++;
                                       nextLevelSize++;
                               }

                       }
               }
               for( i =0;i<nextLevelSize;i++) {
                       currentLevel[i][0] = nextLevel[i][0];
                       currentLevel[i][1] = nextLevel[i][1];
               }
               currentLevelSize=nextLevelSize;
               level++;
       } while (nextLevelSize != 0);

}

/* for debugging
 int n;
scanf ("%d",&n);
 */

