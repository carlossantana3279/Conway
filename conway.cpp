#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

//#include "boilerplateClass.h"	//include our own class
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

//////////////////////////////////////////////
// Mac ID: santanjc
// Student #: 001411625
// 3GC3 Computer Graphics Assignment 1 Part C
////////////////////////////////////////

///////////////////////////////////////////////////
//Globals
float camPos[] = {0, 0, 3.42f};	//where the camera is

//Menu Ids
int main_id;
int subMenuSpeed_id;


int gridWidth = 40;				//the Size of the Grid
int scaler = 600/gridWidth;		//how many pixels each square takes up
vector< vector<bool> > grid;	//grid, true = alive cell, false = dead
int sizeofArray = scaler*scaler; // size of each square

int fpsSpeed = 400;				//fps, starts at 'normal' speed
bool paused = false;			//for pausing/resuming game
	
vector<int> deathX;				//holds the X's of all the cells that are going to be dead in the next state
vector<int> deathY;				//holds the Y's of all the cells that are going to be dead in the next state
vector<int> livesX;				//holds the X's of all the cells that are going to be alive in the next state
vector<int> livesY;				//holds the Y's of all the cells that are going to be alive in the next state


//draws vertical lines for grid
void vline(float x0, float y0, float y1){
	float height = y1 - y0;

	
	glBegin(GL_POINTS);
		for (int i = y0; i < y1; i++){
			glVertex2f(x0, i);
		}

	glEnd();
}

//draws horizontal lines for gird
void hline(float x0, float y0, float x1){
	glBegin(GL_POINTS);
		for (int i = x0; i < x1; i++){
			glVertex2f(i, y0);
		}
	glEnd();
}

//draws the cell, given a position x and y on the grid
void drawSquare(float x0, float y0){


	float x1 = x0*scaler;
	float y1 = y0*scaler;

	//translate into pixels
	x0 = x0*scaler;		
	y0 = y0*scaler;

	x1 += scaler;
	y1 += scaler;

	glColor3f(0,0,0);	//black
	
	//draw square
	glPointSize(1);
	glBegin(GL_POINTS);
		for (int j = y0 +1; j < y1; j++){
			for (int k = x0 +1; k < x1; k++){
				glVertex2f(k , j);
			}
		}	
	glEnd();

}

//draws the cell white. Used for killing cells. Given a position x and y on the grid
void drawSquareWhite(float x0, float y0){

	float x1 = x0*scaler;
	float y1 = y0*scaler;

	//translate into pixels
	x0 = x0*scaler;		
	y0 = y0*scaler;

	x1 += scaler;
	y1 += scaler;

	glColor3f(1,1,1);	//white

	//draw square
	glPointSize(1);
	glBegin(GL_POINTS);
		for (int j = y0 + 1; j < y1; j++){
			for (int k = x0 + 1; k < x1; k++){
				glVertex2f(k , j);
			}
		}	
	glEnd();

}

//initializes the grid, all cells are dead.
void makeGrid(){

	//make the size of the grid
	grid.resize(gridWidth);
	for (int i = 0; i < gridWidth; i++){
		grid[i].resize(gridWidth);
	}

	//set all the cells to be dead
	for (int i = 0; i < gridWidth; i++){
		for (int j = 0; j < gridWidth; j++){
			grid[i][j] = false;
		}
	}


	//Some Test cases
	/*
	//BLOCK- still life
	grid[2][2] = true;
	grid[2][3] = true;
	grid[3][2] = true;
	grid[3][3] = true;

	//BEEHIVE- still life
	grid[6][3] = true;
	grid[7][2] = true;
	grid[7][4] = true;
	grid[8][2] = true;
	grid[8][4] = true;
	grid[9][3] = true;

	//BLINKER -Oscillator
	grid[2][6] = true;
	grid[2][7] = true;
	grid[2][8] = true;

	//TOAD -Oscillator
	grid[13][4] = true;
	grid[14][4] = true;
	grid[15][4] = true;

	grid[14][5] = true;
	grid[15][5] = true;
	grid[16][5] = true;

	//BEACON- still life
	grid[2][15] = true;
	grid[2][16] = true;
	grid[3][15] = true;
	grid[3][16] = true;

	grid[4][13] = true;
	grid[4][14] = true;
	grid[5][13] = true;
	grid[5][14] = true;
	*/
}


//Draws the vertical and horizantal lines for the grid
void drawGrid(){
		glColor3f(0.5,0.5,0.5);		//grey-ish color
	
		glPointSize(1);
		
		//vertical lines
		for (int i = 0; i < 600; i += scaler){
			vline(i,0,600);
			//printf("%f \n", (float) i );
		}
		//horiantal lines
		for (int i = 0; i < 600; i += scaler){
			hline(0,i,600);
		}	
}

//randomizes grid. 
void randomizeGrid(){
	srand((int) time(0));	//randomizer seed
	
	//go through each cell in the grid
	for (int i = 1; i < gridWidth-1; i++){
		for (int j = 1; j < gridWidth-1; j++){

			int randNum = rand() % 2;	// Random number, 0 or 1
			//printf(" randNUM: %i \n", randNum);

			//make an alive cell
			if (randNum == 1){
				grid[i][j] = true;
			}		
		}
	}
}

//draws all the alive and dead cells in the grid
void fillGrid(){

	//go through each cell in the grid
	for (int i = 0; i < gridWidth; i++){
		for (int j = 0; j < gridWidth; j++){
			if (grid[i][j] == true){
				drawSquare( (float) i, (float) j);
			}
		}
	}
}

//clears the grid, (kills all cells)
void clearGrid(){
	for (int i = 0; i < gridWidth; i++){
		for (int j = 0; j < gridWidth; j++){
			grid[i][j] =false;
			fillGrid();			
		}
	}
}

//checks the amount of neighbours of cell x,y and returns the amount of neighbours. 
int checkNeighbours(int x, int y){

	int n =0;		//neighbours counter

	if (grid[x][y+1] == true){		
		//n above
		n++;
	}
	if (grid[x+1][y+1] == true){
		//n up right diag
		n++;
	}		
	if (grid[x+1][y] == true){ 		
		//right n	
		n++;
	}
	if (grid[x+1][y-1] == true){ 
		//n down right diag			
		n++;
	}
	if (grid[x][y-1] == true){ 	
		//n below		
		n++;
	}
	if (grid[x-1][y-1] == true){ 		
		// n left below	
		n++;
	}
	if (grid[x-1][y] == true){ 	
		//n left		
		n++;
	}
	if (grid[x-1][y+1] == true){
		//n left above 			
		n++;
	}

	if (n > 0){
		//printf("cell[%i][%i] has neighbours: %i \n", x,y,n );
	}
	
	return n;
}


//this function changes the states of the cells that have changes. Ei sets all the cells that died this "state" and sets all the ones that became alive this state
void changeState(){
	
	//kill all the cells that dies this state
	for (int i = deathX.size()  ; i > 0 ; i--){
		grid[deathX[deathX.size() -1 ]][deathY[deathX.size() -1 ]] = false;
		//printf("cell[%i][%i] dies.\n", deathX[deathX.size() -1 ],deathY[deathX.size() -1 ]);
		deathX.pop_back();
		deathY.pop_back();
	}

	//turn the cells on that became alive this state
	for (int i = livesX.size() ; i > 0 ; i--){
		grid[livesX[livesX.size() -1 ]][livesY[livesX.size() -1 ]] = true;
		//printf("cell[%i][%i] lives by reproduction.\n", livesX[livesX.size() -1 ],livesY[livesX.size() -1 ]);
		livesX.pop_back();
		livesY.pop_back();
	}
	
}

//Function holes the logic and rules for conways game of life.
void gridLogic(){
	for (int i = 1; i < gridWidth-1; i++){
		for (int j = 1; j < gridWidth - 1; j++){

			int n = 0;
			n = checkNeighbours(i,j);		//check the amount of neighbours

			//if cell i,j is alive
			if (grid[i][j] == true){

				//if the cell has less than 2 neighbours 
				if (n < 2){
					//printf("cell[%i][%i] dies by under-population.\n", i,j);
					
					deathX.push_back(i);
					deathY.push_back(j);
				}else if (n >3){
					//if the cell has more than 3 neighbours 

					//printf("cell[%i][%i] dies by overcrowding.\n", i,j);
					
					deathX.push_back(i);
					deathY.push_back(j);
				}

			}else if (n == 3  ){
				//if cell has exactly 3 neighbours and is dead it gets revived.
				if ( grid[i][j] == false){
					//printf("cell[%i][%i] lives by reproduction.\n", i,j);
					livesX.push_back(i);
					livesY.push_back(j);
				}
			}
		}
	}
}

//transitions the cells from the old state to the new state
void transition(){

	//check if the game is paused 
	if (paused == false){
		gridLogic();
		changeState();	
	}

}

//function that translates a click on the wndow to a window position and turns that cell off or on
void clickPos(int x, int y){

	int gridPosX;
	int gridPosY;

	gridPosX = (int) (x/scaler);		
	gridPosY = (int) (600 - y)/scaler;

	//printf(" grid x: %f \n" , (float) gridPosX);
	//printf(" grid y: %f \n" , (float) gridPosY);


	if (grid[gridPosX][gridPosY] == false){
		grid[gridPosX][gridPosY] = true;
		drawSquare(gridPosX,gridPosY);

	}else if (grid[gridPosX][gridPosY] == true){
		grid[gridPosX][gridPosY] = false;
		drawSquareWhite(gridPosX,gridPosY);
		//drawSquare(gridPosX,gridPosY);
	}
	
}

//takes care of the mouse presses
void mouse(int btn, int state, int x, int y){
	//printf("mouseFunc coords: %i,%i\n", x, y);

	if (btn == GLUT_LEFT_BUTTON){
		
		if (state == GLUT_DOWN){	//when the left button is clicked
			printf("Pressed\n");
			clickPos(x, y);
		}
	}
}

/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);		//clears screen (we want to start from fresh every frame)

	transition();						//transitions the grid from the 'old state' to the 'new state'
	fillGrid();							//draws the changes that just occured in transition();
	drawGrid();							//draws horizontal and vertical lines to draw the grid

	glFlush();							//flush

}


//OpenGL functions
void keyboard(unsigned char key, int xIn, int yIn)
{
	switch (key)
	{
		case 'q':	//if 'q' is presses 
		case 27:	//27 is the esc key
			exit(0);
			break;
		case 'r':
			//printf("pressed 'r' !\n");
			randomizeGrid();		//randomize the Grid
			break;
	}
}

//does the FPS 
void FPS(int val){
	glutPostRedisplay();
	glutTimerFunc(fpsSpeed, FPS, 0); // 1sec = 1000, 60fps = 1000/60 = ~17
}

//takes care of the fps, display, and mouse
void callBackInit(){
	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutMouseFunc(mouse);
	glutTimerFunc(10, FPS,0);
}

/* menuProc handles the menu depending on which item was click */
void menuProc(int value){
	if(value == 1){
		printf("Run/Puase was clicked\n");
		if (paused == false){
			paused = true;
		}else {
			paused = false;
		}
		
	}
	if(value == 2){
		printf("second item was clicked\n");
	}
	if(value == 3){
		printf("Clear Grid was clicked\n");
		//clearGrid();
		makeGrid();
		fillGrid();
	}
	if(value == 4){
		printf("Random Grid item was clicked\n");
		randomizeGrid();
	}
	if(value == 5){
		printf("quit item was clicked\n");
		exit(0);
	}
}

//submenu for the different speeds
void subMenuSpeed(int value){
	if(value == 1) {
		printf("Sub Menu Fast item was clicked\n");
		//moveUp();
		fpsSpeed = 100;
	} else if(value == 2){
		printf("Sub Menu Normal item was clicked\n");
		//moveRight();
		fpsSpeed = 400;
	} else if(value == 3){
		printf("Sub Menu Slow item was clicked\n");
		//moveDown();
		fpsSpeed = 1000;
	} else if(value == 4){
		printf("Sub Menu Very Slow item was clicked\n");
		//moveLeft();
		fpsSpeed = 3000;
	}else if(value == 5){
		printf("Sub Menu Super Fast item was clicked\n");
		//moveLeft();
		fpsSpeed = 50;
	}
}


//sets up all the menues'
void menuSetup(){
		//set up sub menus before main menu
	subMenuSpeed_id = glutCreateMenu(subMenuSpeed);
	glutAddMenuEntry("Super Fast", 5);
	glutAddMenuEntry("Fast", 1);
	glutAddMenuEntry("Normal", 2);
	glutAddMenuEntry("Slow", 3);
	glutAddMenuEntry("Very Slow", 4);

	/* set up a simple menu, which will be handled by menuProc */
	main_id = glutCreateMenu(menuProc);
	glutAddMenuEntry("Run/Pause", 1);
	glutAddSubMenu("Speed Control", subMenuSpeed_id);
	glutAddMenuEntry("Clear Grid", 3);
	glutAddMenuEntry("Randomize Grid", 4);
	glutAddMenuEntry("Quit", 5);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//initializes Game
void init(void)
{
	
	//greeting statement
	printf("--------------------------------------\n");
	printf("student #: 001411625\n"  );
	printf("student ID: santanjc \n"  );
	printf("Project by Juan Carlos Santana Penner \n");
	printf("--------------------------------------\n");
	printf("Welcome to Conways' Game of Life Game! \n");
	printf("The Black Cells represent alive cells, and white cells represent dead cells. \n");
	printf("Right Click to view the menu. \n");
	printf("Menu options: \n");
	printf("-Run/Pause Game \n");
	printf("-Speed Control -> Super Fast, Fast, Nomral, Slow, Very Slow \n");
	printf("-Clear the Grid\n");
	printf("-Randomize Grid \n");
	printf("-Quit the Game \n");	
	printf("You can Also Left click on cells to make them alive or dead. (Easier to do when game is paused) \n");

	glClearColor(1, 1, 1, 0);		//set background to white

	makeGrid();						//initialize the grid
	randomizeGrid();				//randomize grid
	fillGrid();						//draw grid
	
}

/* main function - program entry point */
int main(int argc, char** argv)
{

	glutInit(&argc, argv);		//starts up GLUT

	glutInitDisplayMode(GLUT_RGBA);

	glutInitWindowSize(600, 600);	
	glutInitWindowPosition(0, 0);

	glutCreateWindow("3GC3 Assignment 1 Part C: Conways Game of Life");	//creates the window

	menuSetup();

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);

	callBackInit();
	init();

	gluOrtho2D(0, 600, 0, 600);	//camera options

	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}
