#include <stdio.h>
#include <stdlib.h>
#include "MazeSim.h"
#include "MazeBuild.h"
#include "RyanSolve.h"
#include "MazeDraw.h"


int main() {

  srand((unsigned)time(0));

    int mazesGenerated = 0, successfulMazes = 0;
    int numberOfMazesToGenerate = 1000;
    int loops= 15;
    unsigned int maze[16][16];
    int exit;
    int steps[10];
    float aveSteps[10], aveShortestRoute, successRate;

    do{
        do{
            exit = MakeMaze(maze, loops);
            mazesGenerated ++;
        }while(exit != 0 );
        successfulMazes++;

        aveSteps[0] = (successfulMazes*aveSteps[0] + steps[0])/(successfulMazes + 1);
        aveSteps[1] = (successfulMazes*aveSteps[1] + steps[1])/(successfulMazes + 1);

        aveShortestRoute = ((successfulMazes*aveShortestRoute) + ((maze[0][0] & 65280) >> 8))/(successfulMazes + 1);
    steps[0] = SolveWithFF0( maze, STARTX, STARTY, GOALX, GOALY);

    steps[1] = SolveWithFF1( maze,STARTX, STARTY, GOALX, GOALY);






        // DrawMaze(maze);

    }while(successfulMazes < numberOfMazesToGenerate);

    successRate = ((float)successfulMazes / (float)mazesGenerated) * 100;

        printf("Total Mazes Generated: %d \n", mazesGenerated);
        printf("Total Successful Mazes: %d \n", successfulMazes);
        printf("Success Rate: %f Percent \n\n", successRate);

        printf("Average Number of Steps for FF0: %f \n", aveSteps[0]);
        printf("Average Number of Steps for FF1: %f \n", aveSteps[1]);
        printf("Average Shortest Possible Route: %f \n",aveShortestRoute);
        FloodFill(maze, GOALX, GOALY);// to get the shortest possible route to the center
	
        //((maze[0][0] & 65280) >> 8) = only look that top byte of maze


    return (EXIT_SUCCESS);
}

