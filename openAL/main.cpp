//
// 3D Modeling environment
// Nick Cox
// September 2010
//
// Glut32 Start-Up Template
// Created by Bart Stander
// Modified and enhanced by Nick Cox
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
#include "graphics.h"
#include "audio.h"
#include "camera.h"
#include "shapes.h"
#include "colors.h"
#include "slider.h"
#include "save.h"
#include "io.h"

double screen_x = 1000;
double screen_y = 700;
bool axis = 0;
bool gPan = 0;
// Global Variable for Camera
camera gCam;
// Globals for audio
audio gSrc;

// Functions difinitions
//**** Programmer code ****
void display(void);
void keyboard(unsigned char c, int x, int y);
void specialKeys(int key, int x, int y);
void mouseClick(int mouse_button, int state, int x, int y);
void mouseDrag(int x, int y);
void mouseMove(int x, int y);
void idle(void);
void InitializeMyStuff();
//**** Environment code ****
int  random(int low, int high);
double random(double low, double high);
double GetFramesPerSecond();
void reshape(int w, int h);
void Set2DView(int w, int h);
void Set3DView(int w, int h);

int main(int argc, char **argv) {
	srand(time(0));
	InitializeMyStuff();

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screen_x, screen_y);
	glutInitWindowPosition(50, 0);

	int fullscreen = 0;
	if (fullscreen) {
		glutGameModeString("1024x720:32");//1280x1024:32
		glutEnterGameMode();
	} else {
		glutCreateWindow("Knickers Playground"); // Title of the window
	}

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	//glutSpecialFunc(specialKeys);
	//glutMouseFunc(mouseClick);
	//glutMotionFunc(mouseDrag);
	//glutPassiveMotionFunc(mouseMove);
	//glutIdleFunc(idle);
	// Background Color
	glClearColor(1, 1, 1, 0);

	glutMainLoop();
	// This point never reached
	return 0;
}

//************************************************************************//
//**************************** Programmer Code ***************************//
//************************************************************************//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//****************************************************************//
	Set3DView(screen_x, screen_y);//*********  3D World  *************//
	//****************************************************************//
	if(gPan)
		gCam.pan();
	if(axis)
		DrawAxis(10,red,green,blue);

	//****************************************************************//
	Set2DView(screen_x, screen_y);//*********  2D World  *************//
	//****************************************************************//

	glColor3fv(ivery);
	DrawCircle(screen_x/2, screen_y/2, 20, 0);
	
	static float rX = 3;
	static float rY = 2;
	static float t = 0;
	float x = rX*cos(t);
	float y = rY*sin(t);
	
	glColor3fv(blue);
	DrawCircle(screen_x+x*20, screen_y+y*20, 10, 0);
	gSrc.move(x, y);

	t += .00004;
	if (t > 6.28)
		t = 0;
	printf("Angle: %f  \r", t*180/PI);
	
	// Display Image and Loop
	glutSwapBuffers();
	glutPostRedisplay();
}

// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y) {
	//int mod = glutGetModifiers();
	switch (c) {
		case 27: // escape character to quit the program
			exit(0);
			break;
		case 9: // tab
			break;
		case 13: // return
			break;
		case 32: // space
			gSrc.play();
			break;
		case 'a':
			axis = !axis;
			break;
		case 'p':
			gPan = !gPan;
			break;
		case 's':
			Save((char*)"ppm");
			break;
		case '-': // -
			gCam.moveOut();
			break;
		case'+': // +
			gCam.moveIn();
			break;
		default:
			return; // if we don't care, return without glutPostRedisplay()
	}
	glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
	int mod = glutGetModifiers();
	switch(key) {
		case GLUT_KEY_LEFT:
			gCam.moveLeft();
			break;
		case GLUT_KEY_DOWN:
			gCam.moveDown();
			break;
		case GLUT_KEY_RIGHT:
			gCam.moveRight();
			break;
		case GLUT_KEY_UP:
			gCam.moveUp();
			break;
		case GLUT_KEY_F4:
			if(mod)
				exit(0);
			break;
		default:
			return;
	}
	glutPostRedisplay();
}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouseClick(int mouse_button, int state, int x, int y) {
	y = screen_y - y;

	/*double ratio = x/screen_x;
	double X = (double)-MARGIN+(ratio*(double)(gWidth+MARGIN+MARGIN));
	ratio = y/screen_y;
	double Y = (double)-MARGIN+(ratio*(double)(gHeight+MARGIN+MARGIN));*/

	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		gCam.click(x, y);
	} else if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
	} else if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
	} else if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
	}
	glutPostRedisplay();
}

// This callback function gets called by the Glut
// system whenever any mouse button is drug.
void mouseDrag(int x, int y) {
	y = screen_y - y;

	gCam.drag(x, y);

	glutPostRedisplay();
}

// This callback function gets called by the Glut
// system whenever the mouse is moved.
void mouseMove(int x, int y) {
	y = screen_y - y;

	glutPostRedisplay();
}

// This callback function gets called by the Glut
// system whenever the re-display queue is empty.
void idle(void) {
}

// Initialization code goes here.
void InitializeMyStuff() {
	// set material's specular properties
	float mat_specular[]  = {.3, .3, .3, 1};
	float mat_shininess[] = {20};
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	// set light properties
	float light_pos[]    = { 0, 80, 40, 1};
	float light_color[]  = { 1,  1,  1, 1};
	float light_bounce[] = {.6, .6, .6, 1};
	glLightfv(GL_LIGHT0,GL_POSITION,light_pos);   // First light's position
	glLightfv(GL_LIGHT0,GL_DIFFUSE, light_color); // First light's color
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_bounce);// First light's reflection
}

//************************************************************************//
//************************************************************************//
//**************************** Environment Code **************************//
//************************************************************************//
//************************************************************************//

// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h) {
	// Reset our global variables to the new width and height.
	screen_x = w;
	screen_y = h;
	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, w, h);
}

void Set2DView(int w, int h) {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the world coordinates.
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Set3DView(int w, int h) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspectRatio = (double)w / (double)h;
	gluPerspective(gCam.zoom(), aspectRatio, gCam.near(), gCam.far());
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(gCam.EYE(0), gCam.EYE(1), gCam.EYE(2),
			  gCam.AT(0) , gCam.AT(1) , gCam.AT(2),
			  gCam.UP(0) , gCam.UP(1) , gCam.UP(2));
}

// Return a random number between a low and a high
int random(int low, int high) {
	return rand() % (high-low+1) + low;
}

// Return a random number between low and high
double random(double low, double high) {
	double x = (double)rand() / (double)RAND_MAX; // 0 to 1
	double scale = high-low;
	x *= scale;     // 0 to scale
	return x + low; // low to high;
}

// Returns the number of frames used devided by the time passed
double GetFramesPerSecond() {
	static int frames = 0;
	static clock_t startTime = clock();
	frames++;
	clock_t currentTime = clock();
	double elapsedTime = currentTime - startTime;
	return frames/elapsedTime*CLOCKS_PER_SEC;
}
