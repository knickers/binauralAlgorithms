#pragma once

using namespace std;
#include "common.h"

class Interpolate {
protected:
	unsigned int mSize;
	point* mCP;
	
	virtual void create(unsigned int size);
	virtual void destroy();
	virtual bool accessorHelper();
public:
	Interpolate();
	Interpolate(unsigned int numPoints);
	virtual ~Interpolate();
	virtual point Evaluate(double t)=0;
	
	bool addPoint(point p);
	bool addPoint(double x, double y, double z);
	bool setPoint(unsigned int i, point p);
	bool setPoint(unsigned int i, double x, double y, double z);
	bool setPoints(point* p, unsigned int size);
	bool setX(unsigned int i, double x);
	bool setY(unsigned int i, double y);
	bool setZ(unsigned int i, double z);
	void printPoints();
};

class Bezier : public Interpolate {
private:
	int* mPascal;
	point EvalCurve(double t, point* p, int size, int* pasc);
	
	virtual void create(unsigned int size);
	virtual void destroy();
public:
	Bezier();
	Bezier(unsigned int size);
	virtual ~Bezier();
	virtual point Evaluate(double t);
};
int* GetPascal(int width);
int  RecursePascal(int row, int col);
bool outputBezier(point start, point control, point end, int resolution);

class Linear : public Interpolate {
private:
	double* mLength;
	
	virtual void create(unsigned int size);
	virtual void destroy();
	virtual bool accessorHelper();
	void calcLengths();
public:
	Linear();
	Linear(unsigned int size);
	~Linear();
	virtual point Evaluate(double t);
};
