#include "MazeFlood.h"

void FloodFill(unsigned int maze[][16], int xGoal, int yGoal){
int i, j;
	for( i = 0; i < SIDE; i++){
		for( j = 0; j < SIDE; j++){
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
