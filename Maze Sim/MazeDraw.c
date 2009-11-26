#include "MazeDraw.h"

void DrawMaze(unsigned int maze[][16]){

////////////////output what it should look like////////

char wall = 178, floors = ' ';

int i1, i2, row;
	for(i1 = 0; i1 < SIDE; i1++){
	for(row = 0; row < 3; row++){
	for(i2 = 0; i2 < SIDE; i2++){

        if(row == 0 ){

	  printf("%c", wall);

	  if ((maze[i1][i2] &  NORTH) == NORTH)
	    printf("%c", wall);
	  else
	    printf("%c", floors);

	  printf("%c", wall);
	    }
	else if (row == 1){

	  if ((maze[i1][i2] &  WEST) == WEST)
	    printf("%c", wall);
	  else
	    printf("%c", floors);

	  printf("%c", floors);

	  if ((maze[i1][i2] &  EAST) == EAST)
	    printf("%c", wall);
	  else
	    printf("%c", floors);
	    }

	else{

	  printf("%c", wall);

	  if ((maze[i1][i2] &  SOUTH) == SOUTH)
	    printf("%c", wall);
	  else
	    printf("%c", floors);

	  printf("%c", wall);
	    }

	}
        printf("\n");
}
}

}
