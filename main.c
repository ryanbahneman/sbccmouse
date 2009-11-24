#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void MakeMaze (int unsigned maze[][16], int side, int xCurrent, int yCurrent, int xStack[], int yStack[], int stackNum); 
void createMaze (int unsigned maze[][16]);
void outputMaze (int unsigned maze[][16], int NUM);
void floodFill (int unsigned maze[][16], int NUM, int endY, int endX);
int tremaux (int unsigned maze[][16], int NUM, int tEndY, int tEndX,int unsigned map[][16]);
void reveal (int unsigned maze[][16],int unsigned map[][16], int y, int x);
int traverseFloodFill (int unsigned maze[][16], int NUM,int output, int unsigned map[][16], int endY, int endX);
int traverseFill (int unsigned maze[][16],int NUM, int output);
void outputFloodFill (int unsigned maze[][16], int NUM);

const int LOOPS = 15;
const int MAZES = 1000;
const int mapAll = 1;
const int ffIterations = 3;
const int awareFF = 0;
const int awareT = 0;
const int verbosity = 0;
const int tabsep = 0;

//int ffIterations;
//int LOOPS;

int main (int argc, const char * argv[]) {
	int output = 0;
	int reallyQuiet = 1;
	if(verbosity==1)
		reallyQuiet = 0;
	else if(verbosity==2) {
		reallyQuiet = 0;
		output = 1;
	}
	
	int unsigned maze[16][16];
	int unsigned map[16][16];	
	
	srand((unsigned)time(NULL));
	//for(ffIterations=3;ffIterations<4;ffIterations++) {
	//	printf("\n");
	//for(LOOPS=0;LOOPS<150;LOOPS++) {
	int FAILED = 0;
	int totalSteps = 0;
	int totalShortest = 0;
	int ffSteps = 0;
	int ffTotal = 0;
	const int endX = 8;
	const int endY = 8;
	int cc;
	for(cc=0;(cc-FAILED)<MAZES;cc++) {
		int moves[4];
		
		createMaze(map);
		const int NUM = sizeof(maze[0])/sizeof(int);
		
		int tEndX = 0;
		int tEndY = 0;
		if(!mapAll) {
			tEndX = endX;
			tEndY = endY;
		}
		
		for (int i =0;i<NUM;i++) {
			for(int j=0;j<NUM;j++) {
				maze[i][j] = 255;
			}
		}
		
		maze[0][0] = map[0][0];
		
		int count = 0;
		
		count = tremaux(maze,NUM,tEndY,tEndX,map);
		floodFill(maze,NUM,8,8);
		
		
		if(((maze[0][0] & 65280) >> 8) != 255) {
			moves[0] = count;
			if(!mapAll)
				count+=((maze[0][0] & 65280) >> 8);
			
			if(output)
				printf("%i moves\n\n",count);
			
			
			
			if (output) {
				outputMaze(maze, NUM);
			}
			
			
			if(output)
				printf("\n");			
			count = traverseFill(maze, NUM, output);
			if(output)
				printf("\n\n%i moves\n\n",count);
			totalSteps+=moves[0]+count;
			totalShortest+=count;
			moves[1] = count;
			moves[2] = moves[0] + moves[1];
			
			for (int i =0;i<NUM;i++) {
				for(int j=0;j<NUM;j++) {
					maze[i][j] = 0;
				}
			}
			maze[0][0] = map[0][0];

			for(int i =0;i<ffIterations;i++) {
				count = traverseFloodFill(maze, NUM, output, map, endY, endX);
				ffTotal+=count+((maze[0][0] & 65280) >> 8);
			}
			moves[4] = count;
			ffSteps+=count;
			if(output)
				printf("\n\n%i moves\n\n",count);
			if(!reallyQuiet)
				printf("%3i %3i %3i %3i\n",moves[0],moves[1],moves[2],moves[4]);
			
		} else {
			if(!reallyQuiet) {
				printf("unsolvable\n");
			}
			FAILED++;
		}
	}
	if(!tabsep) {
		printf("\n%i/%i failed\n",FAILED,cc);
		printf("average shortest: %.3f\n",(float)totalShortest/(cc-FAILED));
		printf("average steps: %i\n",totalSteps/(cc-FAILED));
		printf("average ff shortest: %.3f\n",(float)ffSteps/(cc-FAILED));
		printf("average ff steps: %i",ffTotal/(cc-FAILED));
	} else {
		printf("\n%i\t%i",LOOPS,ffIterations);
		printf("\t%i\t%i\t%i",FAILED,cc,cc-FAILED);
		printf("\t%.3f",(float)totalShortest/(cc-FAILED));
		printf("\t%.3f",(float)totalSteps/(cc-FAILED));
		printf("\t%.3f",(float)ffSteps/(cc-FAILED));
		printf("\t%.3f",(float)ffTotal/(cc-FAILED));		
	}
	//}
	//}	// excel loop
	return 0;
}


void createMaze(int unsigned maze[][16]) {
	int xc = 0, yc = 0;
	int xStack[256] = {0};
	int yStack[256] = {0};
	int stackNum = 0;
	int side = 16;
	for(int i = 0; i < side; i++){
		for(int j = 0; j < side; j++){
			maze[i][j] = 255;
		}
	}
	
	MakeMaze(maze, side, xc, yc, xStack, yStack, stackNum);
	
	int loopy=LOOPS;
	while(loopy > 0){
		
		int randx = rand()%(side-2) +1;
		int randy = rand()%(side-2) +1;
		int randdir = rand()%4;
		int exit = 0;
		
		do{	
			
			if(maze[randy][randx] & (3<<((randdir*2)%8))){
				if (randdir%4 == 0){
					maze[randy][randx] &= ~(3<<0);
					maze[randy-1][randx] &= ~(3<<4);
					exit = 1;
				}
				else if (randdir%4 == 1){
					maze[randy][randx] &= ~(3<<2);
					maze[randy][randx+1] &= ~(3<<6);
					exit = 1;
				}
				else if (randdir%4 == 2){
					maze[randy][randx] &= ~(3<<4);
					maze[randy+1][randx] &= ~(3<<0);				
					exit = 1;
				}
				else if (randdir%4 == 3){
					maze[randy][randx] &= ~(3<<6);
					maze[randy][randx-1] &= ~(3<<2);				
					exit = 1;
				}
			}
			else{
				if (randdir < 10)
					randdir += 1;
				else{
					exit = 1;
					loopy++;
				}
				
			}
		} while(exit == 0);
		loopy--;
	}
	
	maze[7][7] = 195;
	maze[6][7] |= (3<<4);
	maze[7][6] |= (3<<2);
	maze[7][8] = 15;
	maze[6][8] |= (3<<4);
	maze[7][9] |= (3<<6);
	maze[8][7] = 240;
	maze[8][6] |= (3<<2);
	maze[9][7] |= (3<<0);
	maze[8][8] = 60;
	maze[8][9] |= (3<<6);
	maze[9][8] |= (3<<0);
	
	int hole = rand()%8;
	
	if (hole == 0){
		maze[7][7] &= ~(3<<0);
		maze[6][7] &= ~(3<<4);
	}
	else if (hole == 1){
		maze[7][8] &= ~(3<<0);
		maze[6][8] &= ~(3<<4);
	}
	else if (hole == 2){
		maze[7][8] &= ~(3<<2);
		maze[7][9] &= ~(3<<6);
	}
	else if (hole == 3){
		maze[8][8] &= ~(3<<2);
		maze[8][9] &= ~(3<<6);
	}
	else if (hole == 4){
		maze[8][8] &= ~(3<<4);
		maze[9][8] &= ~(3<<0);
	}
	else if (hole == 5){
		maze[8][7] &= ~(3<<4);
		maze[9][7] &= ~(3<<0);
	}
	else if (hole == 6){
		maze[8][7] &= ~(3<<6);
		maze[8][6] &= ~(3<<2);
	}
	else if (hole == 7){
		maze[7][7] &= ~(3<<6);
		maze[7][6] &= ~(3<<2);
	}
	
}

void MakeMaze(int unsigned maze[][16], int side, int xCurrent, int yCurrent, int xStack[], int yStack[], int stackNum){ 
	
	maze[yCurrent][xCurrent] |= (1<<8);
	
	int i = 0, dir = 0;
	
	if (yCurrent - 1 >= 0){
		if((maze[yCurrent - 1][xCurrent] & 256) == 0){
			dir |= (1<<0);
			i++;
		}
	}
	if (yCurrent + 1 < side){
		if((maze[yCurrent + 1][xCurrent] & 256) == 0){
			dir |= (1<<2);
			i++;
		}
	}
	if (xCurrent - 1 >= 0){
		if((maze[yCurrent][xCurrent - 1] & 256) == 0){
			dir |= (1<<3);
			i++;
		}
	}
	if (xCurrent + 1 < side){
		if((maze[yCurrent][xCurrent + 1] & 256) == 0){
			dir |= (1<<1);
			i++;
		}
	}
	
	if (i > 0){	//there is an unvisited neighbor
		
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
		} while(exit == 0);
		
		if ( dir == (1<<0)){
			maze[yCurrent][xCurrent] &= ~(3<<0);//turn off wall
			maze[yCurrent - 1][xCurrent] &= ~(3<<4);//turn off wall
			yCurrent--;//set new cell position
		}
		if ( dir == (1<<1)){
			maze[yCurrent][xCurrent] &= ~(3<<2);
			maze[yCurrent][xCurrent + 1] &= ~(3<<6);
			xCurrent++;
		}
		if ( dir == (1<<2)){
			maze[yCurrent][xCurrent] &= ~(3<<4);
			maze[yCurrent + 1][xCurrent] &= ~(3<<0);
			yCurrent++;
		}
		if ( dir == (1<<3)){
			maze[yCurrent][xCurrent] &= ~(3<<6);
			maze[yCurrent][xCurrent - 1] &= ~(3<<2);
			xCurrent--;
		}		
		MakeMaze(maze, side, xCurrent, yCurrent, xStack, yStack, stackNum);
	} else {
		if (stackNum > 0){
			stackNum--;
			xCurrent = xStack[stackNum];
			yCurrent = yStack[stackNum];
			
			MakeMaze(maze, side, xCurrent, yCurrent, xStack, yStack, stackNum);
		}
		
	}
	
}

void outputMaze(int unsigned maze[][16], int NUM) {
	
	for (int i=0; i<NUM; i++) {	// loop through each row
		int r = 2;
		if(i==NUM-1)	// if we're in the last row, make sure to display the full cell
			r=3;
		
		for (int k=0;k<r;k++) {	// for each cell there are three rows of ascii to display
			for (int j=0; j<NUM; j++) {	// loop through each cell in the row
				if (k==0) {
					if((maze[i][j] & 3) == 3) {	// if there is a north wall
						if(j<NUM-1) {	// if we're NOT at the right edge
							printf("*--");
						} else {	// yeah.....
							printf("*--*");
						}
					} else {	// open north
						if(j<NUM-1) {
							printf("*  ");
						} else {
							printf("*  *");
						}
					}
				}
				if (k==1) {
					if ((maze[i][j] & 204) == 204) {	// if there are both east and west
						if(j<NUM-1) {
							printf("|  ");
						} else {
							printf("|  |");
						}
					} else if((maze[i][j] & 12) == 12) {	// only east
						if(j<NUM-1) {
							printf("   ");
						} else {
							printf("   |");
						}
					} else if((maze[i][j] & 192) == 192) {	// only west
						printf("|  ");
					} else {
						printf("   ");
					}
				}
				if (k==2) {
					if((maze[i][j] & 48) == 48) {	// south wall (this only matters in the last row)
						if(j<NUM-1) {
							printf("*--");
						} else {
							printf("*--*");
						}
					} else {
						if(j<NUM-1) {
							printf("*  ");
						} else {
							printf("*  *");
						}
					}
				}
			}
			printf("\n");
		}
	}
}

void floodFill(int unsigned maze[][16], int NUM, int endY, int endX) {	// endy, endx are bottom left corner of center
	int count;
	const int MAX=NUM*NUM-1;
	int current;
	for(int i=0;i<NUM;i++) {
		for(int j=0;j<NUM;j++) {
			current = MAX;
			current = current<<8;
			maze[i][j] |= current;
		}
	}
	
	int level = 0;
	int currentLevel[MAX][2];
	int nextLevel[MAX][2];
	currentLevel[0][0] = endY;
	currentLevel[0][1] = endX;
	currentLevel[1][0] = endY-1;
	currentLevel[1][1] = endX;
	currentLevel[2][0] = endY-1;
	currentLevel[2][1] = endX-1;
	currentLevel[3][0] = endY;
	currentLevel[3][1] = endX-1;
	
	int currentLevelSize = 4;
	int nextLevelSize = 0;
	do {
		count = 0;
		nextLevelSize=0;
		for(int i=0;i<currentLevelSize;i++) {
			if (((maze[currentLevel[i][0]][currentLevel[i][1]] & 65280) >> 8) == MAX) {
				current = level<<8;
				maze[currentLevel[i][0]][currentLevel[i][1]] &=255;
				maze[currentLevel[i][0]][currentLevel[i][1]] |= current;
				if((maze[currentLevel[i][0]][currentLevel[i][1]] & 3) != 3 && (currentLevel[i][0]!=0)) {
					nextLevel[count][0] = currentLevel[i][0] - 1;
					nextLevel[count][1] = currentLevel[i][1];
					count++;
					nextLevelSize++;
				}
				if((maze[currentLevel[i][0]][currentLevel[i][1]] & 12) != 12 && (currentLevel[i][1]!=15)) {
					nextLevel[count][0] = currentLevel[i][0];
					nextLevel[count][1] = currentLevel[i][1]+1;
					count++;
					nextLevelSize++;
				}
				if((maze[currentLevel[i][0]][currentLevel[i][1]] & 48) != 48 && (currentLevel[i][0]!=15)) {
					nextLevel[count][0] = currentLevel[i][0]+1;
					nextLevel[count][1] = currentLevel[i][1];
					count++;
					nextLevelSize++;
				}
				if((maze[currentLevel[i][0]][currentLevel[i][1]] & 192) != 192 && (currentLevel[i][1]!=0)) {
					nextLevel[count][0] = currentLevel[i][0];
					nextLevel[count][1] = currentLevel[i][1] - 1;
					count++;
					nextLevelSize++;
				}
			}
		}
		for(int i =0;i<nextLevelSize;i++) {
			currentLevel[i][0] = nextLevel[i][0];
			currentLevel[i][1] = nextLevel[i][1];
		}
		currentLevelSize=nextLevelSize;
		level++;
	} while (nextLevelSize != 0);
}

int tremaux(int unsigned maze[][16], int NUM, int tEndY, int tEndX,int unsigned map[][16]) {
	int xCurrent = 0;	// start position
	int yCurrent = 0;
	int dir = 1;
	int count = 1;
	
	for(int i=0;i<NUM;i++) {
		for(int j=0;j<NUM;j++);
	}
	do {
		if(awareT&&((yCurrent>NUM/2)&&((yCurrent-NUM/2)>abs((xCurrent-NUM/2))))&&((maze[yCurrent][xCurrent]&12)==0)) {
			maze[yCurrent][xCurrent] |= 4;	// mark that path as taken once
			xCurrent++;
			reveal(maze,map,yCurrent,xCurrent);
			if((maze[yCurrent][xCurrent] & 192) == 64) {
				maze[yCurrent][xCurrent] ^= 192;
			} else if ((maze[yCurrent][xCurrent] & 192) == 0) {
				maze[yCurrent][xCurrent] |= 64;
			}
			dir = 1;
		} else if(awareT&&((xCurrent<NUM/2)&&(abs(xCurrent-NUM/2)>abs((yCurrent-NUM/2))))&&((maze[yCurrent][xCurrent]&48)==0)) {
			maze[yCurrent][xCurrent] |= 16;
			yCurrent++;
			reveal(maze,map,yCurrent,xCurrent);
			if((maze[yCurrent][xCurrent] & 3) == 1) {
				maze[yCurrent][xCurrent] ^= 3;
			} else if ((maze[yCurrent][xCurrent] & 3) == 0) {
				maze[yCurrent][xCurrent] |= 1;
			}
			dir = 2;
		} else if(awareT&&((yCurrent<NUM/2)&&(abs(yCurrent-NUM/2)>abs((xCurrent-NUM/2))))&&((maze[yCurrent][xCurrent]&192)==0)) {
			maze[yCurrent][xCurrent] |= 64;
			xCurrent--;
			reveal(maze,map,yCurrent,xCurrent);
			if((maze[yCurrent][xCurrent] & 12) == 4) {
				maze[yCurrent][xCurrent] ^= 12;
			} else if ((maze[yCurrent][xCurrent] & 12) == 0) {
				maze[yCurrent][xCurrent] |= 4;
			}
			dir = 3;
		} else if(awareT&&((xCurrent>NUM/2)&&((xCurrent-NUM/2)>abs((yCurrent-NUM/2))))&&((maze[yCurrent][xCurrent]&3)==0)) {
			maze[yCurrent][xCurrent] |= 1;
			yCurrent--;
			reveal(maze,map,yCurrent,xCurrent);
			if((maze[yCurrent][xCurrent] & 48) == 16) {
				maze[yCurrent][xCurrent] ^= 48;
			} else if ((maze[yCurrent][xCurrent] & 48) == 0) {
				maze[yCurrent][xCurrent] |= 16;
			}
			dir = 0;
		} else if((maze[yCurrent][xCurrent] & 12) == 0) {	// if moving right is possible, do it
			maze[yCurrent][xCurrent] |= 4;	// mark that path as taken once
			xCurrent++;
			reveal(maze,map,yCurrent,xCurrent);
			if((maze[yCurrent][xCurrent] & 192) == 64) {
				maze[yCurrent][xCurrent] ^= 192;
			} else if ((maze[yCurrent][xCurrent] & 192) == 0) {
				maze[yCurrent][xCurrent] |= 64;
			}
			dir = 1;
		} else if((maze[yCurrent][xCurrent] & 48) == 0) {	// down
			maze[yCurrent][xCurrent] |= 16;
			yCurrent++;
			reveal(maze,map,yCurrent,xCurrent);
			if((maze[yCurrent][xCurrent] & 3) == 1) {
				maze[yCurrent][xCurrent] ^= 3;
			} else if ((maze[yCurrent][xCurrent] & 3) == 0) {
				maze[yCurrent][xCurrent] |= 1;
			}
			dir = 2;
		} else if((maze[yCurrent][xCurrent] & 192) == 0) {	// left
			maze[yCurrent][xCurrent] |= 64;
			xCurrent--;
			reveal(maze,map,yCurrent,xCurrent);
			if((maze[yCurrent][xCurrent] & 12) == 4) {
				maze[yCurrent][xCurrent] ^= 12;
			} else if ((maze[yCurrent][xCurrent] & 12) == 0) {
				maze[yCurrent][xCurrent] |= 4;
			}
			dir = 3;
		} else if((maze[yCurrent][xCurrent] & 3) == 0) {	// up
			maze[yCurrent][xCurrent] |= 1;
			yCurrent--;
			reveal(maze,map,yCurrent,xCurrent);
			if((maze[yCurrent][xCurrent] & 48) == 16) {
				maze[yCurrent][xCurrent] ^= 48;
			} else if ((maze[yCurrent][xCurrent] & 48) == 0) {
				maze[yCurrent][xCurrent] |= 16;
			}
			dir = 0;
		} else if((maze[yCurrent][xCurrent] & 85) == 85) {
			if(dir==3) {
				maze[yCurrent][xCurrent] ^= 12;	// mark that path as taken once
				xCurrent++;
				reveal(maze,map,yCurrent,xCurrent);
				if((maze[yCurrent][xCurrent] & 192) == 64) {
					maze[yCurrent][xCurrent] ^= 192;
				} else if ((maze[yCurrent][xCurrent] & 192) == 0) {
					maze[yCurrent][xCurrent] |= 64;
				}
				dir = 1;
			} else if(dir==0) {
				maze[yCurrent][xCurrent] ^= 48;
				yCurrent++;
				reveal(maze,map,yCurrent,xCurrent);
				if((maze[yCurrent][xCurrent] & 3) == 1) {
					maze[yCurrent][xCurrent] ^= 3;
				} else if ((maze[yCurrent][xCurrent] & 3) == 0) {
					maze[yCurrent][xCurrent] |= 1;
				}
				dir = 2;
			} else if(dir==1) {
				maze[yCurrent][xCurrent] ^= 192;
				xCurrent--;
				reveal(maze,map,yCurrent,xCurrent);
				if((maze[yCurrent][xCurrent] & 12) == 4) {
					maze[yCurrent][xCurrent] ^= 12;
				} else if ((maze[yCurrent][xCurrent] & 12) == 0) {
					maze[yCurrent][xCurrent] |= 4;
				}
				dir = 3;
			} else {
				maze[yCurrent][xCurrent] ^= 3;
				yCurrent--;
				reveal(maze,map,yCurrent,xCurrent);
				if((maze[yCurrent][xCurrent] & 48) == 16) {
					maze[yCurrent][xCurrent] ^= 48;
				} else if ((maze[yCurrent][xCurrent] & 48) == 0) {
					maze[yCurrent][xCurrent] |= 16;
				}
				dir = 0;
			}
		} else if(((maze[yCurrent][xCurrent] & 4) == 4) && !((maze[yCurrent][xCurrent] & 8) == 8)) {
			maze[yCurrent][xCurrent++] ^= 12;	// mark that path as taken once
			reveal(maze,map,yCurrent,xCurrent);
			if((maze[yCurrent][xCurrent] & 192) == 64) {
				maze[yCurrent][xCurrent] ^= 192;
			} else if ((maze[yCurrent][xCurrent] & 192) == 0) {
				maze[yCurrent][xCurrent] |= 64;
			}
			dir = 1;			
		} else if(((maze[yCurrent][xCurrent] & 16) == 16) && !((maze[yCurrent][xCurrent] & 32) == 32)) {
			maze[yCurrent++][xCurrent] ^= 48;
			reveal(maze,map,yCurrent,xCurrent);
			if((maze[yCurrent][xCurrent] & 3) == 1) {
				maze[yCurrent][xCurrent] ^= 3;
			} else if ((maze[yCurrent][xCurrent] & 3) == 0) {
				maze[yCurrent][xCurrent] |= 1;
			}
			dir = 2;
		} else if(((maze[yCurrent][xCurrent] & 64) == 64) && !((maze[yCurrent][xCurrent] & 128) == 128)) {
			maze[yCurrent][xCurrent--] ^= 192;
			reveal(maze,map,yCurrent,xCurrent);
			if((maze[yCurrent][xCurrent] & 12) == 4) {
				maze[yCurrent][xCurrent] ^= 12;
			} else if ((maze[yCurrent][xCurrent] & 12) == 0) {
				maze[yCurrent][xCurrent] |= 4;
			}
			dir = 3;
		} else if(((maze[yCurrent][xCurrent] & 1) == 1) && !((maze[yCurrent][xCurrent] & 2) == 2)) {
			maze[yCurrent--][xCurrent] ^= 3;
			reveal(maze,map,yCurrent,xCurrent);
			if((maze[yCurrent][xCurrent] & 48) == 16) {
				maze[yCurrent][xCurrent] ^= 48;
			} else if ((maze[yCurrent][xCurrent] & 48) == 0) {
				maze[yCurrent][xCurrent] |= 16;
			}
			dir = 0;
		}	
		else if(dir==3) {
			maze[yCurrent][xCurrent++] ^= 12;	// mark that path as taken once
			reveal(maze,map,yCurrent,xCurrent);
			if((maze[yCurrent][xCurrent] & 192) == 64) {
				maze[yCurrent][xCurrent] ^= 192;
			} else if ((maze[yCurrent][xCurrent] & 192) == 0) {
				maze[yCurrent][xCurrent] |= 64;
			}
			dir = 1;
		} else if(dir==0) {
			maze[yCurrent++][xCurrent] ^= 48;
			reveal(maze,map,yCurrent,xCurrent);
			if((maze[yCurrent][xCurrent] & 3) == 1) {
				maze[yCurrent][xCurrent] ^= 3;
			} else if ((maze[yCurrent][xCurrent] & 3) == 0) {
				maze[yCurrent][xCurrent] |= 1;
			}
			dir = 2;
		} else if(dir==1) {
			maze[yCurrent][xCurrent--] ^= 192;
			reveal(maze,map,yCurrent,xCurrent);
			if((maze[yCurrent][xCurrent] & 12) == 4) {
				maze[yCurrent][xCurrent] ^= 12;
			} else if ((maze[yCurrent][xCurrent] & 12) == 0) {
				maze[yCurrent][xCurrent] |= 4;
			}
			dir = 3;
		} else if(dir==2) {
			maze[yCurrent--][xCurrent] ^= 3;
			reveal(maze,map,yCurrent,xCurrent);
			if((maze[yCurrent][xCurrent] & 48) == 16) {
				maze[yCurrent][xCurrent] ^= 48;
			} else if ((maze[yCurrent][xCurrent] & 48) == 0) {
				maze[yCurrent][xCurrent] |= 16;
			}
			dir = 0;
		} else {
			break;
		}
		count++;
		if(count>(NUM*NUM+LOOPS)*2)
			break;
	} while ((xCurrent!=tEndX) || (yCurrent!=tEndY));
	return count;
}

void reveal(int unsigned maze[][16],int unsigned map[][16], int y, int x) {
	int c = maze[y][x];
	if(!(((c&3)==1)||((c&3)==2)||((c&12)==4)||((c&12)==8)||((c&48)==16)||((c&48)==32)||((c&192)==64)||((c&192)==128)))
		maze[y][x] = map[y][x];
	if((maze[y][x]&3)==3 && y!=0)
		maze[y-1][x]|=48;
	if((maze[y][x]&12)==12 && x!=15)
		maze[y][x+1]|=192;
	if((maze[y][x]&48)==48 && y!=15)
		maze[y+1][x]|=3;
	if((maze[y][x]&192)==192 && x!=0)
		maze[y][x-1]|=12;
}

int traverseFloodFill(int unsigned maze[][16],int NUM, int output, int unsigned map[][16], int endY, int endX) {
	int xCurrent,yCurrent,count,dir;
	xCurrent = yCurrent = count = 0;
	int bool,test;
	reveal(maze, map, yCurrent, xCurrent);
	reveal(maze, map, (endY-1), (endX-1));
	reveal(maze, map, (endY-1), endX);
	reveal(maze, map, endY, (endX-1));
	reveal(maze, map, endY, endX);
	floodFill(maze, NUM, endY, endX);
	int currentLowest = (maze[yCurrent][xCurrent] & 65280) >> 8;
	while (currentLowest!=0) {
		bool = 0;
		reveal(maze, map, yCurrent, xCurrent);
		floodFill(maze, NUM, endY, endX);
		currentLowest = NUM*NUM;
		if(yCurrent<0 || yCurrent>=NUM || xCurrent >= NUM || xCurrent < 0) {
			break;
		}		
		if((maze[yCurrent][xCurrent] & 3) != 3) {
			if(awareFF && ((yCurrent>NUM/2) && ((yCurrent-NUM/2)>abs((xCurrent-NUM/2))))) {
				test = ((maze[yCurrent-1][xCurrent] & 65280) >> 8) <= currentLowest;
			} else
				test = ((maze[yCurrent-1][xCurrent] & 65280) >> 8) < currentLowest;
			if (test) {
				currentLowest = (maze[yCurrent-1][xCurrent] & 65280) >> 8;
				dir=0;
			}
			bool = 1;
		}
		if((maze[yCurrent][xCurrent] & 12) != 12) {
			if(awareFF && ((xCurrent<NUM/2) && (abs(xCurrent-NUM/2)>abs((yCurrent-NUM/2))))) {
				test = ((maze[yCurrent][xCurrent+1] & 65280) >> 8) <= currentLowest;
			} else
				test = ((maze[yCurrent][xCurrent+1] & 65280) >> 8) < currentLowest;
			if (test) {
				currentLowest = (maze[yCurrent][xCurrent+1] & 65280) >> 8;
				dir=1;
			}
			bool = 1;
		}
		if((maze[yCurrent][xCurrent] & 48) != 48) {
			if(awareFF && ((yCurrent<NUM/2) && (abs(yCurrent-NUM/2)>abs((xCurrent-NUM/2))))) {
				test = ((maze[yCurrent+1][xCurrent] & 65280) >> 8) <= currentLowest;
			} else
				test = ((maze[yCurrent+1][xCurrent] & 65280) >> 8) < currentLowest;
			if (test) {
				currentLowest = (maze[yCurrent+1][xCurrent] & 65280) >> 8;
				dir=2;
			}
			bool = 1;
		}
		if((maze[yCurrent][xCurrent] & 192) != 192) {
			if(awareFF && ((xCurrent>NUM/2) && ((xCurrent-NUM/2)>abs((yCurrent-NUM/2))))) {
				test = ((maze[yCurrent][xCurrent-1] & 65280) >> 8) <= currentLowest;
			} else
				test = ((maze[yCurrent][xCurrent-1] & 65280) >> 8) < currentLowest;
			if (test) {
				currentLowest = (maze[yCurrent][xCurrent-1] & 65280) >> 8;
				dir=3;
				
			}
			bool = 1;
		}
		if(!bool) {
			if(dir==0)
				dir=2;
			if(dir==1)
				dir=3;
			if(dir==2)
				dir=0;
			if(dir==3)
				dir=1;
		}
		
		
		if(dir==0) {
			yCurrent--;
			if(output)
				printf("N ");
		}
		else if(dir==1) {
			xCurrent++;
			if(output)
				printf("E ");
		}
		else if(dir==2) {
			yCurrent++;
			if(output)
				printf("S ");
		}
		else if(dir==3) {
			xCurrent--;
			if(output)
				printf("W ");
		}
		count++;
	}
	return count;
}

int traverseFill(int unsigned maze[][16],int NUM, int output) {
	int xCurrent,yCurrent,count,dir;
	xCurrent = yCurrent = count = 0;
	int currentLowest = (maze[yCurrent][xCurrent] & 65280) >> 8;
	while (currentLowest!=0) {
		if(yCurrent<0 || yCurrent>=NUM || xCurrent >= NUM || xCurrent < 0) {
			break;
		}		
		if((maze[yCurrent][xCurrent] & 3) != 3) {
			if (((maze[yCurrent-1][xCurrent] & 65280) >> 8) < currentLowest) {
				currentLowest = (maze[yCurrent-1][xCurrent] & 65280) >> 8;
				dir=0;
			}
		}
		if((maze[yCurrent][xCurrent] & 12) != 12) {
			if (((maze[yCurrent][xCurrent+1] & 65280) >> 8) < currentLowest) {
				currentLowest = (maze[yCurrent][xCurrent+1] & 65280) >> 8;
				dir=1;
			}
			
		}
		if((maze[yCurrent][xCurrent] & 48) != 48) {
			if (((maze[yCurrent+1][xCurrent] & 65280) >> 8) < currentLowest) {
				currentLowest = (maze[yCurrent+1][xCurrent] & 65280) >> 8;
				dir=2;
			}
		}
		if((maze[yCurrent][xCurrent] & 192) != 192) {
			if (((maze[yCurrent][xCurrent-1] & 65280) >> 8) < currentLowest) {
				currentLowest = (maze[yCurrent][xCurrent-1] & 65280) >> 8;
				dir=3;
				
			}
		}
		
		
		if(dir==0) {
			yCurrent--;
			if(output)
				printf("N ");
		}
		else if(dir==1) {
			xCurrent++;
			if(output)
				printf("E ");
		}
		else if(dir==2) {
			yCurrent++;
			if(output)
				printf("S ");
		}
		else if(dir==3) {
			xCurrent--;
			if(output)
				printf("W ");
		}
		count++;
	}
	return count;
}

void outputFloodFill (int unsigned maze[][16], int NUM) {
	int current;
	for(int i=0;i<NUM;i++) {
		for(int j=0;j<NUM;j++) {
			current = (maze[i][j] & 65280) >> 8;
			if(current==255)
				printf("  X");
			else
				printf("%3i",current);
		}
		printf("\n");
	}	
	printf("\n");
}