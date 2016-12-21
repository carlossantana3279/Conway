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
#include "basicLibrary.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

///////////////////////////////////////////////
// Mac ID: santanjc
// Student #: 001411625
// 3GC3 Computer Graphics Assignment 1 Part B: Robot
////////////////////////////////////////

//Globals
float camPos[] = {0, 0, 3.42f};	//where the camera is

//Menu Ids
int main_id;					//menu id
int subMenuMove_id;				//sub menu for moving
int subMenuTurn_id;				//sub menu for turning
int subMenuGrid_id;				//sub menu for chaning the grid size

int gridWidth = 25;				//the Size of the Grid
int scaler = 600/gridWidth;		//the size of every squre in the grid

int sizeofArray = scaler*scaler;	//amount of pixels in each square
point2D squarePoints[60*60];		//keeps track of all the point of the Body, Square = Body

point2D headPoints[60*60];			//keeps track of all the point of the head		
int orientation = 0;				//starting orientation of the robot. 0 = norht, 1 = east, 2 = south, 3 = west

int startX = 0;						//starting x of the robot body
int startY = 0;						//starting y of the robot body

//the 2 points required for drawing the body
float bodyX0;						
float bodyY0;
float bodyX1;
float bodyY1;

//the 2 points required for drawing the head
float headX0;
float headY0;
float headX1;
float headY1;

//initializing function
void init(void)
{
	//greeting and instructions to user
	printf("--------------------------------------\n");
	printf("student #: 001411625\n"  );
	printf("student ID: santanjc \n"  );
	printf("Project by Juan Carlos Santana Penner \n");
	printf("--------------------------------------\n");
	printf("Welcome to the Robot Game! \n");
	printf("Controls: \n");
	printf(" Arrow Keys: move Robot \n" );
	printf(" 'z' key: rotate robot left \n");
	printf(" 'x' key: rotate robot right \n");
	printf(" 'r' key: reset position \n");
	printf(" 'p' key: randomize robot position \n");
	printf(" 'q' key: quit program \n" );
	printf(" You can also left click in the window to get a menu. \n" );
	printf("You can even change the grid size! \n");

}

//draws the vertical lines for grid
void vline(float x0, float y0, float y1){
	float height = y1 - y0;

	glBegin(GL_POINTS);
		for (int i = y0; i < y1; i++){
			glVertex2f(x0, i);
		}
	glEnd();
}

//draws the horizontal lines for grid
void hline(float x0, float y0, float x1){
	glBegin(GL_POINTS);
		for (int i = x0; i < x1; i++){
			glVertex2f(i, y0);
		}
	glEnd();
}

//make robot start in a random position
void randomPos(){
	srand((int) time(0));	//randomizer seed

	startX = rand() % gridWidth;		//random x
	startY = rand() % (gridWidth -1); 	//random y -1 ( -1 for the head)

	//printf(" startX %i \n",startX );
	//printf(" startY %i \n",startY );

	//the new positions of the two points for the body
	bodyX0 = startX*scaler ;
	bodyY0 = startY*scaler  ;
	bodyX1 = scaler + startX*scaler ;
	bodyY1 = scaler + startY*scaler;

	//the new positions of the two points for the head
	headX0 = bodyX0 ;
	headY0 = bodyY1;
	headX1 = bodyX1;
	headY1 = bodyY1 + scaler;

	orientation = 0;	//start with head on north of robot body
}

//reset the position at origin (0,0)
void resetPos(){

	startX = 0;	
	startY = 0;

	//the new positions of the two points for the body
	bodyX0 = startX*scaler ;
	bodyY0 = startY*scaler  ;
	bodyX1 = scaler + startX*scaler ;
	bodyY1 = scaler + startY*scaler;

	//the new positions of the two points for the head
	headX0 = bodyX0 ;
	headY0 = bodyY1;
	headX1 = bodyX1;
	headY1 = bodyY1 + scaler;

	orientation = 0;	//start with head on north of robot body
}

//draw the head of the robot
void drawHead(float x0, float y0, float x1, float y1){

		int i = 0;
		for (int j = headY0 ; j < headY1; j++){
			for (int k = headX0; k < headX1; k++){
				point2D p(k,j);	
				headPoints[i] = p;
				i++;
			}
			
		}	
		
		glColor3f(1,0,0);
		glBegin(GL_POINTS);
			for (int i = 0; i < sizeofArray; i++){
				glVertex2f(headPoints[i].x , headPoints[i].y);
			}
		glEnd();
		
	
}

//draw the head of the body
void drawSquare(float x0, float y0, float x1, float y1){

	int i = 0;
	for (int j = y0; j < y1; j++){
		for (int k = x0; k < x1; k++){
			point2D p(k,j);	
			squarePoints[i] = p;
			i++;
		}
		
	}	

	glColor3f(0,1,0);
	glBegin(GL_POINTS);
		for (int i = 0; i < sizeofArray; i++){
			glVertex2f(squarePoints[i].x , squarePoints[i].y);
		}


	glEnd();

}

//make robot move up
void moveUp(){
	if (bodyY1 < 600 &&  headY1 < 600){
		bodyY0 += scaler;
		bodyY1 += scaler;

		headY0 += scaler; 
		headY1 += scaler;
		/*
		printf(" headX0: %f headY0 %f \n", headX0, headY0 );	
		printf(" bodyX0: %f bodyY0 %f \n", bodyX0, bodyY0 );
		*/
	}
	
}

//make robot move right
void moveRight(){
	if (bodyX1 < 600 && headX1 < 600 ){
		bodyX0 += scaler;
		bodyX1 += scaler;

		headX0 += scaler;
		headX1 += scaler;	
	}

}

//make robot move left
void moveLeft(){
	if (bodyX0 > 0 && headX0 > 0 ){
		bodyX0 -= scaler;
		bodyX1 -= scaler;

		headX0 -= scaler;
		headX1 -= scaler;	

	}
}

//make robot move down
void moveDown(){
	if (bodyY0 > 0 && headY0 > 0){
		bodyY0 -= scaler;
		bodyY1 -= scaler;

		headY0 -= scaler; 
		headY1 -= scaler;
	
	}

}

//make robot turn right
void turnRight(){
	

	if (orientation == 0 && (headX1 + scaler) <= 600 ){
		//if robot is facing the north
		headX0 += scaler;
		headX1 += scaler;
		headY0 -= scaler;
		headY1 -= scaler;

		/*
		printf("tr headX0: %f headY0 %f \n", headX0, headY0 );	
		printf(" bodyX0: %f bodyY0 %f \n", bodyX0, bodyY0 );
		*/
		orientation++;

	}else if (orientation == 1 && (headY0 - scaler) >= 0)
	{
		//if robot is facing east
		headX0 -= scaler;
		headX1 -= scaler;
		headY0 -= scaler;
		headY1 -= scaler;

		orientation++;
	}else if (orientation == 2 && (headX0 -scaler) >= 0)
	{
		//if robot is facing south
		headX0 -= scaler;
		headX1 -= scaler;
		headY0 += scaler;
		headY1 += scaler;

		orientation++;
	}else if (orientation == 3 && (headY1 + scaler) <=  600 )
	{
		//if robot is facing west
		headX0 += scaler;
		headX1 += scaler;
		headY0 += scaler;
		headY1 += scaler;

		orientation = 0;
	}

}

//make robot trun left
void turnLeft(){
	
	if (orientation == 0 && (headX0 -scaler) >= 0){
		//if robot is facing the north
		headX0 -= scaler;
		headX1 -= scaler;
		headY0 -= scaler;
		headY1 -= scaler;

		/*
		printf("tl headX0: %f headY0 %f \n", headX0, headY0 );	
		printf(" headX1: %f headY1 %f \n", headX1 , headY1 );
		printf(" bodyX0: %f bodyY0 %f \n", bodyX0, bodyY0 );
		*/
		orientation = 3;
		//printf(" oreintation %f \n", (float) orientation );

	}else if (orientation == 1 && (headY1 + scaler) <= 600)
	{
		//if robot is facing east
		headX0 -= scaler;
		headX1 -= scaler;
		headY0 += scaler;
		headY1 += scaler;

		orientation--;
		//printf(" oreintation %f \n", (float) orientation );
	}else if (orientation == 2 && (headX1 + scaler) <= 600)
	{
		//if robot is facing south
		headX0 += scaler;
		headX1 += scaler;
		headY0 += scaler;
		headY1 += scaler;
		
		orientation--;
		//printf(" oreintation %f \n",(float) orientation );
	}else if (orientation == 3 && (headY0 -scaler)  >= 0 )
	{
		//if robot is facing west
		headX0 += scaler;
		headX1 += scaler;
		headY0 -= scaler;
		headY1 -= scaler;

		orientation--;
		//printf(" oreintation %f \n",(float) orientation );
	}
}

//draw the grid
void makeGrid(){

		glColor3f(1,1,1);	//white lines
		//verticla liens
		for (int i = 0; i < 600; i += scaler){
			vline(i,0,600);
			//printf("%f \n", (float) i );
		}
		//horizontal lines
		for (int i = 0; i < 600; i += scaler){
			hline(0,i,600);
		}	
}

/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT);		//clear screen for new frames
	makeGrid();							//draw the grid
	drawSquare(bodyX0,bodyY0,bodyX1,bodyY1);	//draw the body of robot
	drawHead(headX0, headY0, headX1, headY1);	//draw the head of the robot
	glFlush();	

}

//change the size of the grid. It resets the game.
void reset(int size){
	glClear(GL_COLOR_BUFFER_BIT);
	orientation = 0;				//resest orientation
	gridWidth = size;
	scaler = 600/gridWidth;
	sizeofArray = scaler*scaler;
	resetPos();
	
	drawSquare(bodyX0,bodyY0,bodyX1,bodyY1); 
	drawHead(headX0,headY0,headX1,headY1);

	//printf(" reset size: %f\n", (float) size );
}

//OpenGL functions
void keyboard(unsigned char key, int xIn, int yIn)
{
	switch (key)
	{
		case 'q':
		case 27:	//27 is the esc key
			exit(0);
			break;
		case 'x':
			//printf("pressed 'x' !\n");
			turnRight();
			break;
		case 'z':
			//printf("pressed 'z' !\n");
			turnLeft();
			break;
		case 'p':
			//printf("pressed 'z' !\n");
			randomPos();
			break;
		case 'r':
			//printf("pressed 'z' !\n");
			resetPos();
			break;
	}
}

//arrow key functions
void special(int key, int x, int y){
	switch (key){
	case GLUT_KEY_UP:
		//printf("Up Arrow was pressed! \n");
		moveUp();
		break;
	case GLUT_KEY_DOWN:
		//printf("Down Arrow was pressed! \n");
		moveDown();
		break;
	case GLUT_KEY_RIGHT:
		//printf("Right Arrow was pressed! \n");
		moveRight();
		break;
	case GLUT_KEY_LEFT:
		//printf("Left Arrow was pressed! \n");
		moveLeft();
		break;
	}
}

//the fps for the game
void FPS(int val){
	glutPostRedisplay();
	glutTimerFunc(17, FPS, 17); // 1sec = 1000, 60fps = 1000/60 = ~17
}

//takes care of the fps, display, and mouse
void callBackInit(){
	glutDisplayFunc(display);	//registers "display" as the display callback function
	
	glutSpecialFunc(special);	//special keyboard presses

	glutTimerFunc(0, FPS, 0);
}


/* menuProc handles the menu depending on which item was click */
void menuProc(int value){
	if(value == 1){
		printf("first item was clicked\n");
	}
	if(value == 2){
		printf("second item was clicked\n");
	}
	if(value == 3){
		//printf("Reset item was clicked\n");
		resetPos();
	}
	if(value == 4){
		//printf("Random Postion item was clicked\n");
		randomPos();
	}
	if(value == 5){
		printf("quit item was clicked\n");
		exit(0);
	}
	if(value == 6){
		printf("Grid Sizes item was clicked\n");
	}
}

//submenu
void subMenuMove(int value){
	if(value == 1) {
		printf("Sub Menu up item was clicked\n");
		moveUp();
	} else if(value == 2){
		printf("Sub Menu right item was clicked\n");
		moveRight();
	} else if(value == 3){
		printf("Sub Menu down item was clicked\n");
		moveDown();
	} else if(value == 4){
		printf("Sub Menu left item was clicked\n");
		moveLeft();
	}
}

//submenu
void subMenuTurn(int value){
	if(value == 1){
		printf("Sub Mene Turn right item was clicked\n");
		turnRight();
	}else if(value == 2){
		printf("Sub Menu Turn Left item was clicked\n");
		turnLeft();
	}
}

//submenu
void subMenuGrid(int value){
	if(value == 1) {
		printf("Sub Menu 10 X 10 item was clicked\n");
		reset(10);
	}
	if(value == 2){
		printf("Sub Menu 25 X 25 item was clicked\n");
		//moveRight();
		reset(25);
	}
	if(value == 3){
		printf("Sub Menu 50 X 50 item was clicked\n");
		//moveRight();
		reset(50);
	}
}


//takes care of all the menu and sub menus
void menuSetup(){
		//set up sub menus before main menu
	subMenuMove_id = glutCreateMenu(subMenuMove);
	glutAddMenuEntry("Up", 1);
	glutAddMenuEntry("Right", 2);
	glutAddMenuEntry("Down", 3);
	glutAddMenuEntry("Left", 4);

	subMenuTurn_id = glutCreateMenu(subMenuTurn);
	glutAddMenuEntry("Turn Right", 1);
	glutAddMenuEntry("Turn Left", 2);

	subMenuGrid_id = glutCreateMenu(subMenuGrid);
	glutAddMenuEntry("Small- 10 X 10", 1);
	glutAddMenuEntry("Medium- 25 X 25", 2);
	glutAddMenuEntry("Large- 50 X 50", 3);

	/* set up a simple menu, which will be handled by menuProc */
	main_id = glutCreateMenu(menuProc);
	
	glutAddSubMenu("Move ", subMenuMove_id);
	glutAddSubMenu("Turn ", subMenuTurn_id);
	glutAddMenuEntry("Reset", 3);
	glutAddMenuEntry("Random Postion", 4);
	glutAddSubMenu("Grid Sizes", subMenuGrid_id);  
	glutAddMenuEntry("Quit", 5);

	glutAttachMenu(GLUT_LEFT_BUTTON);
}

/* main function - program entry point */
int main(int argc, char** argv)
{

	resetPos();

	glutInit(&argc, argv);		//starts up GLUT

	glutInitDisplayMode(GLUT_RGBA);

	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("3GC3 Assignment 1 Part B: Robot");	//creates the window

	menuSetup();

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);

	callBackInit();
	init();
	
	gluOrtho2D(0, 600, 0, 600);

	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}
