#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
#include "bezier.h"

void Interpolate::create(int size) {
	// Create the array
	mCP = new point[size];
	// Assign the default positions
	for(int i=0; i<size; i++) {
		mCP[i].x = mCP[i].y = mCP[i].z = i;
	}
	// Save the size
	mSize = size;
}

void Interpolate::destroy() {
	delete mCP;
	delete mPascal;
}

Interpolate::Interpolate() {
	create(0);
}

Interpolate::Interpolate(int numPoints) {
	create(numPoints);
}

Interpolate::~Interpolate() {
	destroy();
}

bool Interpolate::AddPoint(point p) {
	// Save the old data for later
	point* save = new point[mSize];
	for(int i=0; i<mSize; i++) {
		save[i] = mCP[i];
	}
	// Resize the points array
	destroy();
	create(mSize+1);
	// Copy over the old data
	for(int i=0; i<mSize; i++) {
		mCP[i] = save[i];
	}
	// Assign the new point
	mCP[mSize++] = p;
	return true;
}

bool Interpolate::AddPoint(float x, float y, float z) {
	return AddPoint((point){x,y,x});
}

bool Interpolate::SetPoint(int i, point p) {
	mCP[i] = p;
	return true;
}

bool Interpolate::SetPoint(int i, float x, float y, float z) {
	mCP[i].x = x;
	mCP[i].y = y;
	mCP[i].z = z;
	return true;
}

bool Interpolate::SetPoints(point* p, int size) {
	destroy();
	create(size);
	for(int i=0; i<size; i++) {
		mCP[i] = p[i];
	}
	return true;
}

bool Interpolate::SetX(int i, float x) {
	mCP[i].x = x;
	return true;
}

bool Interpolate::SetY(int i, float y) {
	mCP[i].y = y;
	return true;
}

bool Interpolate::SetZ(int i, float z) {
	mCP[i].z = z;
	return true;
}

//****************************************************************************//
//********************************** Bezier **********************************//
//****************************************************************************//

void Bezier::create(int size) : create(size) {
	// Create the pascal coeficients
	mPascal = GetPascal(mSize);
}

void Bezier::destroy() : destroy() {
	delete mPascal;
}

Bezier::Bezier() {
	create(0);
}

Bezier::Bezier(int size) {
	create(size);
}

Bezier::~Bezier() {
	destroy();
}

point Bezier::Evaluate(float t) {
	point result = {0,0,0};
	for(int i=0; i<mSize; i++) {
		result.x += mPascal[i] * mCP[i].x * pow(1-t, mSize-1-i) * pow(t, i);
		result.y += mPascal[i] * mCP[i].y * pow(1-t, mSize-1-i) * pow(t, i);
		result.z += mPascal[i] * mCP[i].z * pow(1-t, mSize-1-i) * pow(t, i);
	}
	return result;
}

int* GetPascal(int width) {
	int* v = new int[width];
	for(int i=0; i<width; i++)
		v[i] = RecursePascal(width-1,i);
	return v;
}

int RecursePascal(int row, int col) {
	if (row == 0 || row == 1 || col == 0 || col == row)
		return 1;
	else
		return RecursePascal(row-1, col-1) + RecursePascal(row-1, col);
}

bool outputBezier(point start, point control, point end, int resolution) {
	ofstream fout("Bezier.txt");
	fout.setf(ios::fixed);
	point p;
	for(int i=0; i<=resolution; i++) {
		double t = (double)i/(double)resolution;
		p.x = start.x*(1-t)*(1-t) + 2*control.x*(1-t)*t + end.x*t*t;
		p.y = start.y*(1-t)*(1-t) + 2*control.y*(1-t)*t + end.y*t*t;
		p.z = start.z*(1-t)*(1-t) + 2*control.z*(1-t)*t + end.z*t*t;
		fout << p.x << " " << p.y << " " << p.z << endl;
	}
	return true;
}

//****************************************************************************//
//********************************** Linear **********************************//
//****************************************************************************//

void Linear::create(int size) : create(size) {
	// Create the lengths between each set of points. Last length is the total
	mLength = new float[size];
	mLength[size-1] = 0;
	for (int i=0; i<size-1; i++) {
		mLength[i] = dist(mCP[i], mCP[i+1]);
		mLength[size-1] += mLength[i];
	}
}

void Linear::destroy() : destroy() {
	delete mLength;
}

Linear::Linear() {
	create(0);
}

Linear::Linear(int size) {
	create(size);
}

Linear::~Linear() {
	destroy();
}

point Linear::Evaluate(float t) {
	return (point){0,0,0};
}
