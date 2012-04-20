#include <string>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
#include "graphics.h"
#include "io.h"

void systemPause() {
	printf("Press any key to continue...");
	getchar();
}

void endWithError(const char* msg) {
	// Display error message in console
	cout << msg << "\n";
	exit(0);
}

// Outputs a string of text at the specified location.
void text_output(double x, double y, char *string) {
	void *font = GLUT_BITMAP_9_BY_15;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	int len, i;
	glRasterPos2d(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
		glutBitmapCharacter(font, string[i]);

	glDisable(GL_BLEND);
}

// Outputs text to the screen in 'stroke' format
void stroke_text(double x, double y, int scale, int rotate, string string) {
	void *font = GLUT_STROKE_ROMAN;
	int length = (int)string.size();
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(screen_x/1024*(scale/100.0),screen_y/786*(scale/100.0),1);
	glRotatef(rotate,0,0,1);
	for (int i=0; i<length; i++)
		glutStrokeCharacter(font, string[i]);
	glPopMatrix();
}

// Outputs a number to the screen at the specified location
void number_output(double x, double y, double num) {
	void *font = GLUT_BITMAP_9_BY_15;
	string temp;
	stringstream out;
	out << num;
	temp = out.str();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	int len, i;
	glRasterPos2d(x, y);
	len = (int)temp.length();
	for (i = 0; i < len; i++)
		glutBitmapCharacter(font, temp[i]);
	glDisable(GL_BLEND);
}

// Outputs a number in 'stroke' text format
void stroke_number(double x, double y, int scale, int rotate, double num) {
	void *font = GLUT_STROKE_ROMAN;
	string temp;
	stringstream out;
	out << num;
	temp = out.str();

	int length = (int)temp.size();
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(screen_x/1024*((double)scale/100),screen_y/786*((double)scale/100),1);
	glRotatef(rotate,0,0,1);
	for (int i=0; i<length; i++)
		glutStrokeCharacter(font, temp[i]);
	glPopMatrix();
}
