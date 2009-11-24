#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;


void drawmaze(unsigned int maze[][16], int side);
void floodfill(unsigned int maze[][16], int side);
char Distance(int dist);
 


int main (void) {

srand((unsigned)time(0));

unsigned int maze[16][16] = {
{499, 271, 451, 307, 307, 271, 451, 271, 499, 259, 307, 307, 271, 451, 307, 271}, 
{463, 496, 316, 463, 451, 316, 460, 460, 451, 316, 463, 451, 316, 460, 451, 268}, 
{448, 307, 307, 268, 460, 451, 316, 496, 268, 451, 268, 496, 271, 460, 460, 460}, 
{508, 451, 259, 316, 460, 460, 451, 307, 256, 256, 304, 319, 460, 460, 460, 460}, 
{451, 316, 460, 451, 304, 304, 268, 451, 268, 496, 307, 307, 304, 268, 460, 508}, 
{460, 451, 316, 448, 259, 271, 508, 460, 508, 451, 271, 451, 307, 268, 496, 271}, 
{460, 496, 271, 496, 316, 496, 271, 496, 307, 316, 496, 304, 259, 316, 451, 268}, 
{496, 271, 496, 307, 307, 319, 460, 195,   3, 259, 271, 451, 304, 307, 316, 460}, 
{451, 268, 451, 307, 307, 307, 268, 240,  60, 460, 460, 460, 451, 259, 319, 460}, 
{460, 460, 460, 499, 259, 271, 496, 307, 319, 460, 496, 316, 460, 496, 259, 316}, 
{460, 460, 496, 271, 496, 256, 259, 307, 271, 448, 271, 499, 268, 499, 256, 271}, 
{460, 496, 271, 496, 307, 316, 496, 271, 496, 316, 448, 271, 448, 307, 304, 268}, 
{496, 307, 304, 307, 259, 259, 319, 460, 451, 271, 508, 460, 496, 271, 451, 316}, 
{451, 307, 271, 451, 316, 508, 451, 316, 460, 496, 271, 460, 451, 268, 460, 463}, 
{448, 271, 496, 316, 451, 307, 316, 499, 268, 451, 316, 460, 460, 508, 496, 268}, 
{508, 496, 307, 307, 304, 307, 307, 307, 316, 496, 307, 316, 496, 307, 307, 316}, 
};
unsigned int map[16][16] = {{195,3,3,3,3,3,3,3,3,3,3,3,3,3,3,15},
							{192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12},
							{192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12},
							{192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12},
							{192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12},
							{192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12},
							{192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12},
							{192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12},
							{192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12},
							{192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12},
							{192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12},
							{192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12},
							{192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12},
							{192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12},
							{192,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12},
							{240,48,48,48,48,48,48,48,48,48,48,48,48,48,48,60}};

int side = 16;


//drawmaze( maze, side);

int steps[10];
int yCurrent = 0, xCurrent = 0;
int dir;
unsigned int neighbor[4];

floodfill(map, side);	

for(int z = 0; z < 3; z++){

	int yCurrent = 0, xCurrent = 0;
	steps[z] = 0;

while(yCurrent != 7 || xCurrent != 7){
	
//(1) Update the wall map

	if (yCurrent > 0){
		if ((maze[yCurrent][xCurrent] & (3<<0)) != 0){
			map[yCurrent][xCurrent] |= (3<<0);
			map[yCurrent - 1][xCurrent] |= (3<<4);
		}
	}
	else
		map[yCurrent][xCurrent] |= (3<<0);



	if (xCurrent < (side - 1)){
		if ((maze[yCurrent][xCurrent] & (3<<2)) != 0){
			map[yCurrent][xCurrent] |= (3<<2);
			map[yCurrent][xCurrent + 1] |= (3<<6);
		}
	}
	else
		map[yCurrent][xCurrent] |= (3<<2);



	if (yCurrent < (side - 1)){
		if ((maze[yCurrent][xCurrent] & (3<<4)) != 0){
			map[yCurrent][xCurrent] |= (3<<4);
			map[yCurrent + 1][xCurrent] |= (3<<0);
		}
	}
	else
		map[yCurrent][xCurrent] |= (3<<4);



	if (xCurrent > 0){
		if ((maze[yCurrent][xCurrent] & (3<<6)) != 0){
			map[yCurrent][xCurrent] |= (3<<6);
			map[yCurrent][xCurrent - 1] |= (3<<2);
		}
	}
	else
		map[yCurrent][xCurrent] |= (3<<6);

	
//(2) Flood the maze with new distance values
	floodfill(map, side);	


//(3) Decide which neighboring cell has the lowest distance value

	if (yCurrent > 0){
		if ((map[yCurrent][xCurrent] & (3<<0)) == 0)
			neighbor[0] = ((map[yCurrent - 1][xCurrent]& 65280) >> 8);
		else
			neighbor[0] = 255;
	}
	else
			neighbor[0] = 255;

	if (xCurrent < (side - 1)){
		if ((map[yCurrent][xCurrent] & (3<<2)) == 0)
			neighbor[1] = ((map[yCurrent][xCurrent + 1] & 65280) >> 8);
		else
			neighbor[1] = 255;
	}
	else
			neighbor[1] = 255;

	if (yCurrent < (side - 1)){
		if ((map[yCurrent][xCurrent] & (3<<4)) == 0)
			neighbor[2] = ((map[yCurrent + 1][xCurrent] & 65280) >> 8);
		else
			neighbor[2] = 255;
	}
	else
			neighbor[2] = 255;

	if (xCurrent > 0){
		if ((map[yCurrent][xCurrent] & (3<<6)) == 0)
			neighbor[3] = ((map[yCurrent][xCurrent - 1] & 65280) >> 8);
		else
			neighbor[3] = 255;
	}
	else
			neighbor[3] = 255;

int max = 255;
	for(int i = 0; i < 4; i++){
		if (neighbor[i] < max){
			dir = i;
			max = neighbor[i];
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
			

steps[z] +=1;

};

floodfill(maze, side);
drawmaze( maze, side);
cout<<endl<<endl;
drawmaze(map, side);
/*		 
for(int i = 0; i < side; i++){
		for(int j = 0; j < side; j++){
			cout<<((map[i][j] & 65280) >> 8);
			if (((map[i][j] & 65280) >> 8) < 10)
				cout<<"   ";
			else if (((map[i][j] & 65280) >> 8) < 100)
				cout<<"  ";
			else
				cout<<" ";
		}
		cout<<endl;
	}
*/

	cout<<endl<<endl;
	cout<<"Shortest Route Found: "<<((map[0][0] & 65280) >> 8)<<endl;
	cout<<"Number of Steps: "<<steps[z]<<endl;
	
	cout<<"Shortest Route: "<<((maze[0][0] & 65280) >> 8)<<endl;
}
	int worthlessvar;
cin>> worthlessvar;


}

void drawmaze(unsigned int maze[][16], int side){

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
	  
	  cout<<Distance(((maze[i1][i2] & 65280) >> 8));
	
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

void floodfill(unsigned int maze[][16], int side){

	for(int i = 0; i < side; i++){
		for(int j = 0; j < side; j++){
			maze[i][j] |= 65280;
		}
	}
	int level = 0;
		const int MAX = 16*16-1;
		int currentLevel[MAX][2];
		int nextLevel[MAX][2];
		int count;
		int endY = 7;
		int endX = 7;
		int current;
		currentLevel[0][0] = endY;
		currentLevel[0][1] = endX;
		int currentLevelSize = 1;
		int nextLevelSize = 0;
		   do {
               count = 0;
               nextLevelSize=0;
               for(int i=0;i<currentLevelSize;i++) {
                        if (((maze[currentLevel[i][0]][currentLevel[i][1]] & 65280) >> 8) == MAX) {
                               current = level<<8;
                               maze[currentLevel[i][0]][currentLevel[i][1]] &=255;
                               maze[currentLevel[i][0]][currentLevel[i][1]] |= current;
                               if((maze[currentLevel[i][0]][currentLevel[i][1]] & 3) != 3) {
                                       nextLevel[count][0] = currentLevel[i][0] - 1;
                                       nextLevel[count][1] = currentLevel[i][1];
                                       count++;
                                       nextLevelSize++;
                               }
                               if((maze[currentLevel[i][0]][currentLevel[i][1]] & 12) != 12) {
                                       nextLevel[count][0] = currentLevel[i][0];
                                       nextLevel[count][1] = currentLevel[i][1]+1;
                                       count++;
                                       nextLevelSize++;
                               }
                               if((maze[currentLevel[i][0]][currentLevel[i][1]] & 48) != 48) {
                                       nextLevel[count][0] = currentLevel[i][0]+1;
                                       nextLevel[count][1] = currentLevel[i][1];
                                       count++;
                                       nextLevelSize++;
                               }
                               if((maze[currentLevel[i][0]][currentLevel[i][1]] & 192) != 192) {
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

char Distance(int dist){

if (dist == 0)
	return '0';
else if (dist ==1)
	return '1';
else if (dist ==2)
	return '2';
else if (dist ==3)
	return '3';
else if (dist ==4)
	return '4';
else if (dist ==5)
	return '5';
else if (dist ==6)
	return '6';
else if (dist ==7)
	return '7';
else if (dist ==8)
	return '8';
else if (dist ==9)
	return '9';
else if (dist ==10)
	return 'a';
else if (dist ==11)
	return 'b';
else if (dist ==12)
	return 'c';
else if (dist ==13)
	return 'd';
else if (dist ==14)
	return 'e';
else if (dist ==15)
	return 'f';
else if (dist ==16)
	return 'g';
else if (dist ==17)
	return 'h';
else if (dist ==18)
	return 'i';
else if (dist ==19)
	return 'j';
else if (dist ==20)
	return 'k';
else if (dist ==21)
	return 'l';
else if (dist ==22)
	return 'm';
else if (dist ==23)
	return 'n';
else if (dist ==24)
	return 'o';
else if (dist ==25)
	return 'p';
else if (dist ==26)
	return 'q';
else if (dist ==27)
	return 'r';
else if (dist ==28)
	return 's';
else if (dist ==29)
	return 't';
else if (dist ==30)
	return 'u';
else if (dist ==31)
	return 'v';
else if (dist ==32)
	return 'w';
else if (dist ==33)
	return 'x';
else if (dist ==34)
	return 'y';
else
	return 'z';

}
