#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
#include "interpolate.h"

void Interpolate::create(unsigned int size) {
	//printf("Interpolate::create(%d)\n", size);
	// Create the array
	//printf("  Creating new array\n");
	mCP = new point[size];
	// Assign the default positions
	//printf("  Assigning default positions\n");
	for(unsigned i=0; i<size; i++) {
		mCP[i].x = mCP[i].y = mCP[i].z = i;
	}
	// Save the size
	mSize = size;
}

void Interpolate::destroy() {
	//printf("Interpolate::destroy()\n");
	if (mCP != NULL) {
		delete mCP;
		mCP = NULL;
	}
}

bool Interpolate::accessorHelper() {
	return true;
}

Interpolate::Interpolate() {
	//printf("Interpolate::Interpolate()\n");
	create(0);
}

Interpolate::Interpolate(unsigned numPoints) {
	//printf("Interpolate::Interpolate(int numPoints)\n");
	create(numPoints);
}

Interpolate::~Interpolate() {
	//printf("Interpolate::~Interpolate()\n");
	destroy();
}

bool Interpolate::addPoint(point p) {
	//printf("Interpolate::AddPoint(point) (%f, %f, %f)\n", p.x, p.y, p.z);
	//printf("  Saving old data\n");
	// Save the old data for later
	point* save = new point[mSize];
	for(unsigned i=0; i<mSize; i++) {
		save[i] = mCP[i];
	}
	//printf("  Resizing array\n");
	// Resize the points array
	destroy();
	create(mSize+1); // mSize gets reset to this new value
	//printf("  Replacing old data\n");
	// Copy over the old data
	for(unsigned i=0; i<mSize; i++) {
		mCP[i] = save[i];
	}
	// Cleanup
	delete save;
	//printf("  Assigning new point\n");
	// Assign the new point
	mCP[mSize-1] = p;
	return accessorHelper();
}

bool Interpolate::addPoint(double x, double y, double z) {
	//printf("Interpolate::AddPoint(double, double, double)\n");
	return addPoint((point){x,y,x});
}

bool Interpolate::setPoint(unsigned i, point p) {
	//printf("Interpolate::setPoint(i, point)\n");
	if (i < mSize) {
		mCP[i] = p;
		return accessorHelper();
	}
	return false;
}

bool Interpolate::setPoint(unsigned i, double x, double y, double z) {
	//printf("Interpolate::setPoint(i, x,y,z)\n");
	if (i < mSize) {
		mCP[i].x = x;
		mCP[i].y = y;
		mCP[i].z = z;
		return accessorHelper();
	}
	return false;
}

bool Interpolate::setPoints(point* p, unsigned size) {
	//printf("Interpolate::setPoints(points, size)\n");
	destroy();
	create(size);
	for(unsigned i=0; i<size; i++) {
		mCP[i] = p[i];
	}
	return accessorHelper();
}

bool Interpolate::setX(unsigned i, double x) {
	if (i < mSize) {
		mCP[i].x = x;
		return accessorHelper();
	}
	return false;
}

bool Interpolate::setY(unsigned i, double y) {
	if (i < mSize) {
		mCP[i].y = y;
		return accessorHelper();
	}
	return false;
}

bool Interpolate::setZ(unsigned i, double z) {
	if (i < mSize) {
		mCP[i].z = z;
		return accessorHelper();
	}
	return false;
}

void Interpolate::printPoints() {
	for (unsigned i=0; i<mSize; i++) {
		printf("p%d (%f, %f, %f)\n", i, mCP[i].x, mCP[i].y, mCP[i].z);
	}
}

//****************************************************************************//
//********************************** Bezier **********************************//
//****************************************************************************//

void Bezier::create(unsigned size) {
	//printf("Bezier::create(%d).\n", size);
	// Do all the stuff the parent does first
	Interpolate::create(size);
	//printf("Doing bezier stuff.\n");
	// Create the pascal coeficients
	mPascal = GetPascal(mSize);
}

void Bezier::destroy() {
	//printf("Bezier::destroy().\n");
	// Do all the stuff the parent does first
	Interpolate::destroy();
	// Delete the pascal coeficients
	if (mPascal != NULL) {
		delete mPascal;
		mPascal = NULL;
	}
}

Bezier::Bezier() {
	//printf("Bezier::Bezier().\n");
	create(0);
}

Bezier::Bezier(unsigned size) {
	//printf("Bezier::Bezier(%d).\n", size);
	create(size);
}

Bezier::~Bezier() {
	//printf("Bezier::~Bezier().\n");
	destroy();
}

point Bezier::Evaluate(double t) {
	//printf("Bezier::Evaluate(%f).", t);
	point result = {0,0,0};
	for(unsigned i=0; i<mSize; i++) {
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

void Linear::create(unsigned size) {
	// Do all the stuff the parent does first
	Interpolate::create(size);
	if (size > 0) {
		mLength = new double[size-1];
	} else {
		mLength = NULL;
	}
}

void Linear::destroy() {
	// Do all the stuff the parent does first
	Interpolate::destroy();
	if (mLength != NULL) {
		delete mLength;
		mLength = NULL;
	}
}

bool Linear::accessorHelper() {
	calcLengths();
	return true;
}

// Calculate the lengths between each set of points. Lengths are running total
// [0..1] = dist(0, 1)
// [1..2] = dist(0, 1) + dist(1, 2)
// [2..3] = dist(0, 1) + dist(1, 2) + dist(2, 3)
void Linear::calcLengths() {
	//printf("Linear::CalcLengths()\n");
	double total=0, length=0;
	for (unsigned i=0; i<mSize-1; i++) {
		length = dist(mCP[i], mCP[i+1]);
		total += length;
		mLength[i] = total;
		//printf("  %d) dist(%d,%d)=%f total=%f\n", i, i,i+1, length, total);
	}
}

Linear::Linear() {
	create(0);
}

Linear::Linear(unsigned size) {
	create(size);
}

Linear::~Linear() {
	destroy();
}

point Linear::Evaluate(double t) {
	//printf("Linear::Evaluate(%f).", t);
	unsigned i = 0;
	for (i=0; i<mSize-1; i++) {
		//printf("%f ", mLength[i]/mLength[mSize-2]);
		if (t < mLength[i]/mLength[mSize-2]) {
			break;
		}
	}
	//printf("%d",i);
	double a = 0;
	if (i > 0)
		a = mLength[i-1]/mLength[mSize-2]; // Percentage length to first point
	double b = mLength[i]/mLength[mSize-2]; // Percentage length to second point
	double s = (t-a) / (b-a); // Percentage of the length between the points
	point p;
	p.x = mCP[i].x + s*(mCP[i+1].x - mCP[i].x);
	p.y = mCP[i].y + s*(mCP[i+1].y - mCP[i].y);
	p.z = mCP[i].z + s*(mCP[i+1].z - mCP[i].z);
	return p;
}
