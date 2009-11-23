#include <iostream>
#include <cstdlib> 
#include <time.h>

//11 11 11 11 closed
//WW SS EE NN

class mazeNode{
  public:
	mazeNode();
	
	bool North;
	bool East;
	bool South;
	bool West;
};

class maze{
  public:
	maze();
	maze(int sizeX, int sizeY);
	~maze(){//delete myMaze;
	};
	
	int xDim;
	int yDim;
	
	mazeNode* myMaze;
	
	int startX;
	int startY;
	int endX;
	int endY;
};

void printMaze(maze printMe);

void wallKiller(maze thisMaze);

int pickWall();


int main()
{
	srand(time(0));
	maze *newMaze = new maze();
	wallKiller(*newMaze);
	printMaze(*newMaze);
	//delete [] newMaze;
	return 0;
}







maze::maze(){
	myMaze = new mazeNode[256];
	xDim = 16;
	yDim = 16;
	startX = 0;
	startY = 0;
	endX = rand() % 16;
	endY = rand() % 16;
}

maze::maze(int sizeX, int sizeY){
	myMaze = new mazeNode[sizeX*sizeY];
	xDim = sizeX;
	yDim = sizeY;
	startX = 0;
	startY = 0;
	endX = rand() % sizeX;
	endY = rand() % sizeY;
	printf("%i ", endX);
	printf("%i \n", endY);
}

mazeNode::mazeNode(){
	North = true;
	East = true;
	South = true;
	West = true;
}

void printMaze(maze printMe){
	for (int i = -1; i < (2*printMe.xDim); i++){
		printf("_");
	}
	printf("\n");
	
	for (int i = 0; i < printMe.yDim; i++){ 
		printf("|");
		for (int j = 0; j < printMe.xDim; j++){
			if ((j == printMe.startX) && (i == printMe.startY)){
				if (printMe.myMaze[(i * printMe.yDim) + j].South && printMe.myMaze[(i * printMe.yDim) + j].East)
					printf("O|");
				else if (printMe.myMaze[(i * printMe.yDim) + j].South)
					printf("_o");
				else if (printMe.myMaze[(i * printMe.yDim) + j].East)
					printf("o|");
				else
					printf("o ");
			}else if ((j == printMe.endX) && (i == printMe.endY)){
				if (printMe.myMaze[(i * printMe.yDim) + j].South && printMe.myMaze[(i * printMe.yDim) + j].East)
					printf("X|");
				else if (printMe.myMaze[(i * printMe.yDim) + j].South)
					printf("_x");
				else if (printMe.myMaze[(i * printMe.yDim) + j].East)
					printf("x|");
				else
					printf("x ");
			}else{
				if (printMe.myMaze[(i * printMe.yDim) + j].South && printMe.myMaze[(i * printMe.yDim) + j].East)
					printf("_|");
				else if (printMe.myMaze[(i * printMe.yDim) + j].South)
					printf("__");
				else if (printMe.myMaze[(i * printMe.yDim) + j].East)
					printf(" |");
				else
					printf("  ");
			}
		}
		printf("\n");
	}
}

void wallKiller(maze thisMaze){
	int xMax = thisMaze.xDim;
	int yMax = thisMaze.yDim;
	
	int curX = thisMaze.startX;
	int curY = thisMaze.startY;
	while( !((curX == thisMaze.endX) & (curY == thisMaze.endY)) ){
		switch (pickWall())
		{
         case 0://North killed
            if (curY > 0){
				thisMaze.myMaze[((curY-1)*xMax)+curX].South = false;
				thisMaze.myMaze[(curY*xMax)+curX].North = false;
				curY = curY - 1;
			}
            break;
         case 1://East killed
			if (curX < (xMax-1)){
				thisMaze.myMaze[(curY*xMax)+curX].East = false;
				thisMaze.myMaze[((curY*xMax)+curX)+1].West = false;
				curX = curX + 1;
			}
			break;
         case 2://South killed
            if (curY < (yMax-1)){
				thisMaze.myMaze[(curY*xMax)+curX].South = false;
				thisMaze.myMaze[((curY+1)*xMax)+curX].North = false;
				curY = curY + 1;
			}
            break;
         case 3://West killed
            if (curX > 0){
				thisMaze.myMaze[(curY*xMax)+curX].West = false;
				thisMaze.myMaze[((curY*xMax)+curX) - 1].East = false;
				curX = curX - 1;
			}
            break;
		}

		
	}
}

int pickWall(){
	return random() % 4;
}
