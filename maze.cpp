#include<iostream>
#include<stdlib.h>

using namespace std;

void definemap(char city[][16]);
void outputmap(char city[][16], int side);
void buildmaze(char city[][16], int maze[][16], int side);
void drawmaze(int maze[][16], int side);

int main(void){

	char city[16][16];
	int  maze[16][16];
	int mouse[16][16];
	int side = 5;
	int start[2], end[2], current[2];
	int items[10];

start[0] = start[1] = 0;


definemap(city);
outputmap(city, side);
buildmaze(city, maze, side);
drawmaze(maze, side);



/*
cout<<city[0][0]<<maze[0][0]<<endl;

int testvar; 
testvar = maze[0][0];
if(testvar & (1<<3)){
cout<<(testvar &(1<<3))<<" "<<(1<<3)<<endl;
}
*/


int worthlessvar;//this just pauses the system
cin>>worthlessvar;//so you can look at it

}



void definemap(char city[][16]){

	/*
 

each char contains the wall information!
if the bit is on it is a wall, otherwise it's open.

maze[i1][i2] = 0000

MSB-> TOP LEFT BOTTOM RIGHT <-LSB

MSB = most significant bit
LSB = least significant bit


using that convention each cell can be assinged a letter.
this will allow us to create a large map that can be interperated
by the computer. from this we can start testing algoritms. 
someone needs to write the algoritms. the whole point of this code
is to make it quick to build a few test mazes.

**note that when using the map with your algorithm,
your algorithm should build its own map. it should refrence the
corosponding cell of the map to see where the walls are. this will eventually 
be replaced by the sensors.


below is a refrence for entering values for the computer.

a = 0000
b = 0001
c = 0010
d = 0011
e = 0100
f = 0101
g = 0110
h = 0111
i = 1000
j = 1001
k = 1010
l = 1011
m = 1100
n = 1101
o = 1110
p = 1111 probably won't be using this one much :)

*/

city[0][0] = 'n';
city[0][1] = 'm';
city[0][2] = 'i';
city[0][3] = 'i';
city[0][4] = 'j';

city[1][0] = 'e';
city[1][1] = 'd';
city[1][2] = 'f';
city[1][3] = 'h';
city[1][4] = 'f';

city[2][0] = 'e';
city[2][1] = 'k';
city[2][2] = 'd';
city[2][3] = 'm';
city[2][4] = 'b';

city[3][0] = 'f';
city[3][1] = 'n';
city[3][2] = 'm';
city[3][3] = 'b';
city[3][4] = 'h';

city[4][0] = 'g';
city[4][1] = 'd';
city[4][2] = 'h';
city[4][3] = 'g';
city[4][4] = 'l';

}

void outputmap(char city[][16], int side){

	/////////////ouput map/////////////
	for(int i1 = 0; i1 < side; i1++){
	for(int i2 = 0; i2 < side; i2++){
	cout<<city[i1][i2]<<" ";
	}
	cout<<endl;
	}

}

void buildmaze(char city[][16], int maze[][16], int side){

		for(int i1 = 0; i1 < side; i1++){
	for(int i2 = 0; i2 < side; i2++){
	
	switch(city[i1][i2]){
	
	case 'a':
	maze[i1][i2] = 0;
	break;
	case 'b':
	maze[i1][i2] = 1;
	break;
	case 'c':
	maze[i1][i2] = 2;
	break;
	case 'd':
	maze[i1][i2] = 3;
	break;
	case 'e':
	maze[i1][i2] = 4;
	break;
	case 'f':
	maze[i1][i2] = 5;
	break;
	case 'g':
	maze[i1][i2] = 6;
	break;
	case 'h':
	maze[i1][i2] = 7;
	break;
	case 'i':
	maze[i1][i2] = 8;
	break;
	case 'j':
	maze[i1][i2] = 9;
	break;
	case 'k':
	maze[i1][i2] = 10;
	break;
	case 'l':
	maze[i1][i2] = 11;
	break;
	case 'm':
	maze[i1][i2] = 12;
	break;
	case 'n':
	maze[i1][i2] = 13;
	break;
	case 'o':
	maze[i1][i2] = 14;
	break;
	case 'p':
	maze[i1][i2] = 15;
	break;

	}
	

}
}	



}

void drawmaze(int maze[][16], int side){

////////////////output what it should look like////////

char wall = '0', floors = '.';
	for(int i1 = 0; i1 < side; i1++){
	for(int row = 0; row < 3; row++){
	for(int i2 = 0; i2 < side; i2++){
	
        if(row == 0 ){

	  cout<<wall;

	  if ((maze[i1][i2] &  (1<<3)))
	    cout<<wall;
	  else
	    cout<<floors;
	  
	  cout<<wall;
	    }
	else if (row == 1){

	  if (maze[i1][i2] &  (1<<2))
	    cout<<wall;
	  else
	    cout<<floors;
	  
	  cout<<floors;

	  if (maze[i1][i2] &  (1<<0))
	    cout<<wall;
	  else
	    cout<<floors;
	    }

	else{
	  
	  cout<<wall;

	  if (maze[i1][i2] &  (1<<1))
	    cout<<wall;
	  else
	    cout<<floors;
	  
	  cout<<wall;
	    }
	
	}
	cout<<endl;
}	
}

}
