#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;


void drawmaze(int maze[][16], int side);
void MakeMaze(int maze[][16], int side, int xCurrent, int yCurrent, int xStack[], int yStack[], int stackNum); 


int main (void) {

srand((unsigned)time(0));
//int random_integer = rand(); 

	// populate the maze using the lower half of the integer, bits (high -> low): WW SS EE NN
	//	(11 - wall, 10 - travelled twice, 01 - travelled once, 00 - open)

	int maze[16][16];

	int xCurrent = 0, yCurrent = 0;
	int xStack[256], yStack[256], stackNum = 0;
	int side = 16;
	int loopy = 5;
	
	for(int i = 0; i < side; i++){
		for(int j = 0; j < side; j++){
			maze[i][j] = 255;
		}
	}

MakeMaze(maze, side, xCurrent, yCurrent, xStack, yStack, stackNum);

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
	}while(exit == 0);
loopy -= 1;
}




///make one exit for the middle of the maze
maze[7][7] = 195;
maze[7][8] = 15;
maze[8][7] = 240;
maze[8][8] = 60;

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


drawmaze( maze, side);
	cout<<endl;

int worthlessvar;
cin>> worthlessvar;

}


void MakeMaze(int maze[][16], int side, int xCurrent, int yCurrent, int xStack[], int yStack[], int stackNum){ 

	maze[yCurrent][xCurrent] |= (1<<8);

	int i = 0, dir = 0;
	
	if (yCurrent - 1 >= 0){
		if((maze[yCurrent - 1][xCurrent] & 256) == 0){
			dir |= (1<<0);
			i+=1;
		}
	}
	if (yCurrent + 1 < side){
		if((maze[yCurrent + 1][xCurrent] & 256) == 0){
			dir |= (1<<2);
			i+=1;
		}
	}
	if (xCurrent - 1 >= 0){
		if((maze[yCurrent][xCurrent - 1] & 256) == 0){
			dir |= (1<<3);
			i+=1;
		}
	}
	if (xCurrent + 1 < side){
		if((maze[yCurrent][xCurrent + 1] & 256) == 0){
			dir |= (1<<1);
			i+=1;
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

		
		if ( dir == (1<<0)){
			maze[yCurrent][xCurrent] &= ~(3<<0);//turn off wall
			maze[yCurrent - 1][xCurrent] &= ~(3<<4);//turn off wall
			yCurrent -= 1;//set new cell position
		}
		if ( dir == (1<<1)){
			maze[yCurrent][xCurrent] &= ~(3<<2);
			maze[yCurrent][xCurrent + 1] &= ~(3<<6);
			xCurrent += 1;
		}
		if ( dir == (1<<2)){
			maze[yCurrent][xCurrent] &= ~(3<<4);
			maze[yCurrent + 1][xCurrent] &= ~(3<<0);
			yCurrent += 1;
		}
		if ( dir == (1<<3)){
			maze[yCurrent][xCurrent] &= ~(3<<6);
			maze[yCurrent][xCurrent - 1] &= ~(3<<2);
			xCurrent -= 1;
		}


	MakeMaze(maze, side, xCurrent, yCurrent, xStack, yStack, stackNum);
	}
	
	
	else{
		if (stackNum > 0){
		stackNum -=1;
		xCurrent = xStack[stackNum];
		yCurrent = yStack[stackNum];

		MakeMaze(maze, side, xCurrent, yCurrent, xStack, yStack, stackNum);
		}

	}

}

void drawmaze(int maze[][16], int side){

////////////////output what it should look like////////

char wall = 178, floors = ' ';
	for(int i1 = 0; i1 < side; i1++){
	for(int row = 0; row < 3; row++){
	for(int i2 = 0; i2 < side; i2++){
	
        if(row == 0 ){

	  cout<<wall;

	  if ((maze[i1][i2] &  (3<<0)) == 3)
	    cout<<wall;
	  else if ((maze[i1][i2] &  (3<<0)) == 1)
		  cout<<'1';
	  else if ((maze[i1][i2] &  (3<<0)) == 2)
		  cout<<'2';
	  else
	    cout<<floors;
	  
	  cout<<wall;
	    }
	else if (row == 1){

	  if ((maze[i1][i2] &  (3<<6)) == 192)
	    cout<<wall;
	  else if ((maze[i1][i2] &  (3<<6)) == 64)
		  cout<<'1';
	  else if ((maze[i1][i2] &  (3<<6)) == 128)
		  cout<<'2';
	  else
	    cout<<floors;
	  
	  cout<<floors;
	
	  if ((maze[i1][i2] &  (3<<2)) == 12)
	    cout<<wall;
	  else if ((maze[i1][i2] &  (3<<2)) == 4)
		  cout<<'1';
	  else if ((maze[i1][i2] &  (3<<2)) == 8)
		  cout<<'2';
	  else
	    cout<<floors;
	    }

	else{
	  
	  cout<<wall;

	  if ((maze[i1][i2] &  (3<<4)) == 48)
	    cout<<wall;
	  else if ((maze[i1][i2] &  (3<<4)) == 16)
		  cout<<'1';
	  else if ((maze[i1][i2] &  (3<<4)) == 32)
		  cout<<'2';
	  else
	    cout<<floors;
	  
	  cout<<wall;
	    }
	
	}
	cout<<endl;
}	
}

}