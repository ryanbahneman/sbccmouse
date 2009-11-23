#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;


void drawmaze(int maze[][16], int side, int yCurrent, int xCurrent);


int main (int argc, const char * argv[]) {


	// populate the maze using the lower half of the integer, bits (high -> low): WW SS EE NN
	//	(11 - wall, 10 - travelled twice, 01 - travelled once, 00 - open)
	int maze2[16][16] = {	{243, 51,  3, 15,207},
						{195, 63,204,240, 12},
						{204,195, 48, 15,204},
						{204,240,  3, 60,252},
						{240, 51, 48, 51, 63}};
	int maze[16][16] = {	{243,3,3,3,15},
						{195,0,0,0,12},
						{192,0,0,0,12},
						{192,0,0,0,12},
						{240,48,48,48,60}};
	int maze3[16][16] = {	{243,3,3,3,15},
						{195,0,0,0,12},
						{192,0,0,0,12},
						{192,0,0,0,12},
						{240,48,48,48,60}};
	const int NUM = sizeof(maze[0])/sizeof(int);
	
	/*for(int i=0;i<NUM;i++) {
		for(int j=0;j<NUM;j++)
			printf("%i ",maze[i][j]);
		printf("\n");
	}*/
		
	int xCurrent = 0;	// start position
	int yCurrent = 0;
	int dir = 0;
	int steps = 0;
	
	do {
		
		system("clear");
		drawmaze(maze, 5, yCurrent, xCurrent);
		for (time_t t = time(NULL) + 1; time(NULL) < t; ) {}

		//printf("%i %i  %i  %i\n",yCurrent,xCurrent,maze[yCurrent][xCurrent], dir);
		if((maze[yCurrent][xCurrent] & 12) == 0) {	// if moving right is possible, do it
			maze[yCurrent][xCurrent] |= 4;	// mark that path as taken once
			xCurrent++;
			if(maze[yCurrent][xCurrent] == maze3[yCurrent][xCurrent]) {
				maze[yCurrent][xCurrent] = maze2[yCurrent][xCurrent];
			}
			if((maze[yCurrent][xCurrent] & 192) == 64) {
				maze[yCurrent][xCurrent] ^= 192;
			} else if ((maze[yCurrent][xCurrent] & 192) == 0) {
				maze[yCurrent][xCurrent] |= 64;
			}
			dir = 1;
		} else if((maze[yCurrent][xCurrent] & 48) == 0) {	// down
			maze[yCurrent][xCurrent] |= 16;
			yCurrent++;
			if(maze[yCurrent][xCurrent] == maze3[yCurrent][xCurrent]) {
				maze[yCurrent][xCurrent] = maze2[yCurrent][xCurrent];
			}
			if((maze[yCurrent][xCurrent] & 3) == 1) {
				maze[yCurrent][xCurrent] ^= 3;
			} else if ((maze[yCurrent][xCurrent] & 3) == 0) {
				maze[yCurrent][xCurrent] |= 1;
			}
			dir = 2;
		} else if((maze[yCurrent][xCurrent] & 192) == 0) {	// left
			maze[yCurrent][xCurrent] |= 64;
			xCurrent--;
			if(maze[yCurrent][xCurrent] == maze3[yCurrent][xCurrent]) {
				maze[yCurrent][xCurrent] = maze2[yCurrent][xCurrent];
			}
			if((maze[yCurrent][xCurrent] & 12) == 4) {
				maze[yCurrent][xCurrent] ^= 12;
			} else if ((maze[yCurrent][xCurrent] & 12) == 0) {
				maze[yCurrent][xCurrent] |= 4;
			}
			dir = 3;
		} else if((maze[yCurrent][xCurrent] & 3) == 0) {	// up
			maze[yCurrent][xCurrent] |= 1;
			yCurrent--;
			if(maze[yCurrent][xCurrent] == maze3[yCurrent][xCurrent]) {
				maze[yCurrent][xCurrent] = maze2[yCurrent][xCurrent];
			}
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
				if(maze[yCurrent][xCurrent] == maze3[yCurrent][xCurrent]) {
					maze[yCurrent][xCurrent] = maze2[yCurrent][xCurrent];
				}
				if((maze[yCurrent][xCurrent] & 192) == 64) {
					maze[yCurrent][xCurrent] ^= 192;
				} else if ((maze[yCurrent][xCurrent] & 192) == 0) {
					maze[yCurrent][xCurrent] |= 64;
				}
				dir = 1;
			} else if(dir==0) {
				maze[yCurrent][xCurrent] ^= 48;
				yCurrent++;
				if(maze[yCurrent][xCurrent] == maze3[yCurrent][xCurrent]) {
					maze[yCurrent][xCurrent] = maze2[yCurrent][xCurrent];
				}
				if((maze[yCurrent][xCurrent] & 3) == 1) {
					maze[yCurrent][xCurrent] ^= 3;
				} else if ((maze[yCurrent][xCurrent] & 3) == 0) {
					maze[yCurrent][xCurrent] |= 1;
				}
				dir = 2;
			} else if(dir==1) {
				maze[yCurrent][xCurrent] ^= 192;
				xCurrent--;
				if((maze[yCurrent][xCurrent] & 12) == 4) {
					maze[yCurrent][xCurrent] ^= 12;
				} else if ((maze[yCurrent][xCurrent] & 12) == 0) {
					maze[yCurrent][xCurrent] |= 4;
				}
				dir = 3;
			} else {
				maze[yCurrent][xCurrent] ^= 3;
				yCurrent--;
				if(maze[yCurrent][xCurrent] == maze3[yCurrent][xCurrent]) {
					maze[yCurrent][xCurrent] = maze2[yCurrent][xCurrent];
				}
				if((maze[yCurrent][xCurrent] & 48) == 16) {
					maze[yCurrent][xCurrent] ^= 48;
				} else if ((maze[yCurrent][xCurrent] & 48) == 0) {
					maze[yCurrent][xCurrent] |= 16;
				}
				dir = 0;
			}
		} else if(((maze[yCurrent][xCurrent] & 4) == 4) && !((maze[yCurrent][xCurrent] & 8) == 8)) {
			maze[yCurrent][xCurrent++] ^= 12;	// mark that path as taken once
			if((maze[yCurrent][xCurrent] & 192) == 64) {
				maze[yCurrent][xCurrent] ^= 192;
			} else if ((maze[yCurrent][xCurrent] & 192) == 0) {
				maze[yCurrent][xCurrent] |= 64;
			}
			dir = 1;			
		} else if(((maze[yCurrent][xCurrent] & 16) == 16) && !((maze[yCurrent][xCurrent] & 32) == 32)) {
			maze[yCurrent++][xCurrent] ^= 48;
			if(maze[yCurrent][xCurrent] == maze3[yCurrent][xCurrent]) {
				maze[yCurrent][xCurrent] = maze2[yCurrent][xCurrent];
			}
			if((maze[yCurrent][xCurrent] & 3) == 1) {
				maze[yCurrent][xCurrent] ^= 3;
			} else if ((maze[yCurrent][xCurrent] & 3) == 0) {
				maze[yCurrent][xCurrent] |= 1;
			}
			dir = 2;
		} else if(((maze[yCurrent][xCurrent] & 64) == 64) && !((maze[yCurrent][xCurrent] & 128) == 128)) {
			maze[yCurrent][xCurrent--] ^= 192;
			if(maze[yCurrent][xCurrent] == maze3[yCurrent][xCurrent]) {
				maze[yCurrent][xCurrent] = maze2[yCurrent][xCurrent];
			}
			if((maze[yCurrent][xCurrent] & 12) == 4) {
				maze[yCurrent][xCurrent] ^= 12;
			} else if ((maze[yCurrent][xCurrent] & 12) == 0) {
				maze[yCurrent][xCurrent] |= 4;
			}
			dir = 3;
		} else if(((maze[yCurrent][xCurrent] & 1) == 1) && !((maze[yCurrent][xCurrent] & 2) == 2)) {
			maze[yCurrent--][xCurrent] ^= 3;
			if(maze[yCurrent][xCurrent] == maze3[yCurrent][xCurrent]) {
				maze[yCurrent][xCurrent] = maze2[yCurrent][xCurrent];
			}
			if((maze[yCurrent][xCurrent] & 48) == 16) {
				maze[yCurrent][xCurrent] ^= 48;
			} else if ((maze[yCurrent][xCurrent] & 48) == 0) {
				maze[yCurrent][xCurrent] |= 16;
			}
			dir = 0;
		}	
		else if(dir==3) {
			maze[yCurrent][xCurrent++] ^= 12;	// mark that path as taken once
			if(maze[yCurrent][xCurrent] == maze3[yCurrent][xCurrent]) {
				maze[yCurrent][xCurrent] = maze2[yCurrent][xCurrent];
			}
			if((maze[yCurrent][xCurrent] & 192) == 64) {
				maze[yCurrent][xCurrent] ^= 192;
			} else if ((maze[yCurrent][xCurrent] & 192) == 0) {
				maze[yCurrent][xCurrent] |= 64;
			}
			dir = 1;
		} else if(dir==0) {
			maze[yCurrent++][xCurrent] ^= 48;
			if(maze[yCurrent][xCurrent] == maze3[yCurrent][xCurrent]) {
				maze[yCurrent][xCurrent] = maze2[yCurrent][xCurrent];
			}
			if((maze[yCurrent][xCurrent] & 3) == 1) {
				maze[yCurrent][xCurrent] ^= 3;
			} else if ((maze[yCurrent][xCurrent] & 3) == 0) {
				maze[yCurrent][xCurrent] |= 1;
			}
			dir = 2;
		} else if(dir==1) {
			maze[yCurrent][xCurrent--] ^= 192;
			if(maze[yCurrent][xCurrent] == maze3[yCurrent][xCurrent]) {
				maze[yCurrent][xCurrent] = maze2[yCurrent][xCurrent];
			}
			if((maze[yCurrent][xCurrent] & 12) == 4) {
				maze[yCurrent][xCurrent] ^= 12;
			} else if ((maze[yCurrent][xCurrent] & 12) == 0) {
				maze[yCurrent][xCurrent] |= 4;
			}
			dir = 3;
		} else if(dir==2) {
			maze[yCurrent--][xCurrent] ^= 3;
			if(maze[yCurrent][xCurrent] == maze3[yCurrent][xCurrent]) {
				maze[yCurrent][xCurrent] = maze2[yCurrent][xCurrent];
			}
			if((maze[yCurrent][xCurrent] & 48) == 16) {
				maze[yCurrent][xCurrent] ^= 48;
			} else if ((maze[yCurrent][xCurrent] & 48) == 0) {
				maze[yCurrent][xCurrent] |= 16;
			}
			dir = 0;
		} else {
			break;
		}
		
		

		//printf("y: %i, x: %i\n",yCurrent,xCurrent);
		steps +=1;
	} while ((xCurrent!=0) || (yCurrent!=0));
		
	
	
printf("%d \n", steps);
drawmaze(maze2, 5, yCurrent, xCurrent);
int worthlessvar;//this just pauses the system
cin>>worthlessvar;//so you can look at it


	return 0;
}

void drawmaze(int maze[][16], int side, int yCurrent, int xCurrent){

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
	  if(i1 == yCurrent && i2 == xCurrent)
		  cout<<'M';	 
	else
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
