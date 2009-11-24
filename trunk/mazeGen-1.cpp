#include <iostream>
#include <cstdlib> 
#include <time.h>

//11 11 11 11 closed
//WW SS EE NN

class mazeNode{
  public:
	mazeNode();
	
	bool hasTwoOpen();
	
	bool North;
	bool East;
	bool South;
	bool West;
};

class maze{
  public:
	maze();
	maze(int sizeX, int sizeY);

	int xDim;
	int yDim;
	
	mazeNode* myMaze;
	
	int startX;
	int startY;
	int endX;
	int endY;
};

void printMaze(maze printMe);

void wallKiller(maze thisMaze, int curX, int curY);

void populateMaze(maze m);

int pickWall(int outOf);


int main()
{
	srand(time(0));
	maze *newMaze = new maze();
	
	populateMaze(*newMaze);
	
	printMaze(*newMaze);
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

bool mazeNode::hasTwoOpen(){
	int count = 0;
	if (!North)
		count++;
	if (!East)
		count++;
	if (!South)
		count++;
	if (!West)
		count++;
	if (count < 2)
		return false;
	else
		return true;
}

void printMaze(maze printMe){
	for (int i = 0; i < printMe.xDim; i++){
		printf(" _");
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

void wallKiller(maze thisMaze, int curX, int curY){
	int xMax = thisMaze.xDim;
	int yMax = thisMaze.yDim;
	
	if ((curX == -1) && (curY == -1))
		curX = thisMaze.startX;
		curY = thisMaze.startY;	
	int x=0;
	
	while( !((curX == thisMaze.endX) & (curY == thisMaze.endY)) & (x < 100000) ){
		x++;
		int n = pickWall(4);
	/*	if ((thisMaze.myMaze[(curY*xMax)+curX].North & thisMaze.myMaze[(curY*xMax)+curX].East & thisMaze.myMaze[(curY*xMax)+curX].South) | 
		  (thisMaze.myMaze[(curY*xMax)+curX].East & thisMaze.myMaze[(curY*xMax)+curX].South & thisMaze.myMaze[(curY*xMax)+curX].West) |
		  (thisMaze.myMaze[(curY*xMax)+curX].South & thisMaze.myMaze[(curY*xMax)+curX].West & thisMaze.myMaze[(curY*xMax)+curX].North) |
		  (thisMaze.myMaze[(curY*xMax)+curX].West & thisMaze.myMaze[(curY*xMax)+curX].North & thisMaze.myMaze[(curY*xMax)+curX].East) )
		{*/
		
		
		/*
		 * if( ((!thisMaze.myMaze[((curY-1)*xMax)+curX].West && !thisMaze.myMaze[(curY*xMax)+curX].West) && thisMaze.myMaze[(curY*xMax)+curX+1].North) |
								(!thisMaze.myMaze[((curY-1)*xMax)+curX].East && !thisMaze.myMaze[(curY*xMax)+curX].East))
							{
							}else{
		*/
			
			switch (n)
			{
			 case 0://North killed
				if (curY > 0){
					if (thisMaze.myMaze[((curY)*xMax)+curX].North)
					{
						if (!thisMaze.myMaze[((curY-1)*xMax)+curX].hasTwoOpen()){							
							thisMaze.myMaze[((curY-1)*xMax)+curX].South = false;
							thisMaze.myMaze[(curY*xMax)+curX].North = false;
							curY = curY - 1;
					
						}
					}else {
						curY = curY-1;
					}
				}
				break;
			 case 1://East killed
				if (curX < (xMax-1)){
					if (thisMaze.myMaze[(curY*xMax)+curX].East)
					{
						if (!thisMaze.myMaze[(curY*xMax)+curX+1].hasTwoOpen()){
							thisMaze.myMaze[(curY*xMax)+curX].East = false;
							thisMaze.myMaze[((curY*xMax)+curX)+1].West = false;
							curX = curX + 1;
						}
					}else {
						curX = curX + 1;
					}
				}
				break;
			 case 2://South killed
				if (curY < (yMax-1)){
					if (thisMaze.myMaze[(curY*xMax)+curX].South)
					{
						if (!thisMaze.myMaze[((curY+1)*xMax)+curX].hasTwoOpen()){
							thisMaze.myMaze[(curY*xMax)+curX].South = false;
							thisMaze.myMaze[((curY+1)*xMax)+curX].North = false;
							curY = curY + 1;
						}
					}else {
						curY = curY + 1;
					}
				}
				break;
			 case 3://West killed
				if (curX > 0){
					if (thisMaze.myMaze[(curY*xMax)+curX].West)
					{
						if (!thisMaze.myMaze[(curY*xMax)+curX-1].hasTwoOpen()){
							thisMaze.myMaze[(curY*xMax)+curX].West = false;
							thisMaze.myMaze[((curY*xMax)+curX) - 1].East = false;
							curX = curX - 1;
						}
					}else {
						curX = curX - 1;
					}
				}
				break;
			}
			
		
		/*printMaze(thisMaze);
		printf("Progression: %i   ", x);
		printf("Wall %i killed\n", n);*/
	}
	
	/*
	
	for (int i=0;i<yMax;i++){
			for (int j=0;j<xMax;j++){
				if (thisMaze.myMaze[(i*xMax)+j].North && thisMaze.myMaze[(i*xMax)+j].East 
				  && thisMaze.myMaze[(i*xMax)+j].South && thisMaze.myMaze[(i*xMax)+j].West){
					if (i == 0){ //north must stay
						if (j == 0){ //west must stay
							switch(pickWall(2))
							{
								case 0:
									thisMaze.myMaze[(i*xMax)+j].East = false;
									thisMaze.myMaze[(i*xMax)+j+1].West = false;
									break;
								
								case 1:
									thisMaze.myMaze[(i*xMax)+j].South = false;
									thisMaze.myMaze[((i+1)*xMax)+j].North = false;
									break;
							}
						}else if (j == xMax-1){ //east must stay
							switch(pickWall(2))
							{
								case 0:
									thisMaze.myMaze[(i*xMax)+j].West = false;
									thisMaze.myMaze[(i*xMax)+j-1].East = false;
									break;
								
								case 1:
									thisMaze.myMaze[(i*xMax)+j].South = false;
									thisMaze.myMaze[((i+1)*xMax)+j].North = false;
									break;
							}
						}else{ //east and west killable
							switch(pickWall(3))
							{
								case 0:
									thisMaze.myMaze[(i*xMax)+j].East = false;
									thisMaze.myMaze[(i*xMax)+j+1].West = false;
									break;
								
								case 1:
									thisMaze.myMaze[(i*xMax)+j].South = false;
									thisMaze.myMaze[((i+1)*xMax)+j].North = false;
									break;
									
								case 2:
									thisMaze.myMaze[(i*xMax)+j].West = false;
									thisMaze.myMaze[(i*xMax)+j-1].East = false;
									break;
							}
						}
					}else if (i == yMax-1){ //south must stay
						if (j == 0){ //west must stay
							switch(pickWall(2))
							{
								case 0:
									thisMaze.myMaze[(i*xMax)+j].North = false;
									thisMaze.myMaze[((i-1)*xMax)+j].South = false;
									break;
								
								case 1:
									thisMaze.myMaze[(i*xMax)+j].East = false;
									thisMaze.myMaze[(i*xMax)+j+1].West = false;
									break;
							}
							
						}else if (j == xMax-1){ //east must stay
							switch(pickWall(2))
							{
								case 0:
									thisMaze.myMaze[(i*xMax)+j].West = false;
									thisMaze.myMaze[(i*xMax)+j-1].East = false;
									break;
								
								case 1:
									thisMaze.myMaze[(i*xMax)+j].North = false;
									thisMaze.myMaze[((i-1)*xMax)+j].South = false;
									break;
							}
						}else{ //east and west killable
							switch(pickWall(3))
							{
								case 0:
									thisMaze.myMaze[(i*xMax)+j].East = false;
									thisMaze.myMaze[(i*xMax)+j+1].West = false;
									break;
								
								case 1:
									thisMaze.myMaze[(i*xMax)+j].West = false;
									thisMaze.myMaze[(i*xMax)+j-1].East = false;
									break;
									
								case 2:
									thisMaze.myMaze[(i*xMax)+j].North = false;
									thisMaze.myMaze[((i-1)*xMax)+j].South = false;
									break;
							}
						}
					}else{ //north and south killable
						if (j == 0){ //west must stay
							switch(pickWall(3))
							{
								case 0:
									thisMaze.myMaze[(i*xMax)+j].East = false;
									thisMaze.myMaze[(i*xMax)+j+1].West = false;
									break;
								
								case 1:
									thisMaze.myMaze[(i*xMax)+j].South = false;
									thisMaze.myMaze[((i+1)*xMax)+j].North = false;
									break;
									
								case 2:
									thisMaze.myMaze[(i*xMax)+j].North = false;
									thisMaze.myMaze[((i-1)*xMax)+j].South = false;
									break;
							}
						}else if (j == xMax-1){ //east must stay
							switch(pickWall(3))
							{
								case 0:
									thisMaze.myMaze[(i*xMax)+j].South = false;
									thisMaze.myMaze[((i+1)*xMax)+j].North = false;
									break;
								
								case 1:
									thisMaze.myMaze[(i*xMax)+j].West = false;
									thisMaze.myMaze[(i*xMax)+j-1].East = false;
									break;
									
								case 2:
									thisMaze.myMaze[(i*xMax)+j].North = false;
									thisMaze.myMaze[((i-1)*xMax)+j].South = false;
									break;
							}
						}else{ //east and west killable
							switch(pickWall(4))
							{
								case 0:
									thisMaze.myMaze[(i*xMax)+j].East = false;
									thisMaze.myMaze[(i*xMax)+j+1].West = false;
									break;
								
								case 1:
									thisMaze.myMaze[(i*xMax)+j].South = false;
									thisMaze.myMaze[((i+1)*xMax)+j].North = false;
									break;
									
								case 2:
									thisMaze.myMaze[(i*xMax)+j].West = false;
									thisMaze.myMaze[(i*xMax)+j-1].East = false;
									break;
									
								case 3:
									thisMaze.myMaze[(i*xMax)+j].North = false;
									thisMaze.myMaze[((i-1)*xMax)+j].South = false;
									break;
							}
						}
					}
				}
			}
		}
		*/
}

void populateMaze(maze m){
	wallKiller(m, -1, -1);
	
	int xMax = m.xDim;
	int yMax = m.yDim;
	
	for (int i=0;i<yMax;i++){
			for (int j=0;j<xMax;j++){
				if (m.myMaze[(i*xMax)+j].North && m.myMaze[(i*xMax)+j].East 
				  && m.myMaze[(i*xMax)+j].South && m.myMaze[(i*xMax)+j].West){
					  wallKiller(m, j, i);
			}
		}
	}
	
	for (int i=0;i<yMax-1;i++){
		for (int j=0;j<xMax-1;j++){
			if (!m.myMaze[(i*xMax)+j].East && !m.myMaze[(i*xMax)+j+1].West 
			  && !m.myMaze[(i*xMax)+j+1].South && !m.myMaze[((i+1)*xMax)+j+1].North
			  && !m.myMaze[((i+1)*xMax)+j+1].West && !m.myMaze[((i+1)*xMax)+j].East
			  && !m.myMaze[((i+1)*xMax)+j].North && !m.myMaze[(i*xMax)+j].South){
				  switch(random() % 2){
					case 0:
						m.myMaze[(i*xMax)+j].East = true;
						m.myMaze[(i*xMax)+j+1].West = true;
						break;
					case 1:
						m.myMaze[(i*xMax)+j].South = true;
						m.myMaze[((i+1)*xMax)+j].North = true;
						break;
					
				  }
			}
		}
	}
}

int pickWall(int outOf){
	return random() % outOf;
}
