#pragma once

using namespace std;
#include "common.h"

class Interpolate {
protected:
	int  mSize;
	point* mCP;
	
	virtual void create(unsigned int size);
	virtual void destroy();
	virtual bool accessorHelper();
public:
	Interpolate();
	Interpolate(unsigned int numPoints);
	virtual ~Interpolate();
	virtual point Evaluate(float t)=0;
	
	bool AddPoint(point p);
	bool AddPoint(float x, float y, float z);
	bool SetPoint(unsigned int i, point p);
	bool SetPoint(unsigned int i, float x, float y, float z);
	bool SetPoints(point* p, unsigned int size);
	bool SetX(unsigned int i, float x);
	bool SetY(unsigned int i, float y);
	bool SetZ(unsigned int i, float z);
	void PrintPoints();
};

class Bezier : public Interpolate {
private:
	int* mPascal;
	point EvalCurve(float t, point* p, int size, int* pasc);
	
	virtual void create(unsigned int size);
	virtual void destroy();
public:
	Bezier();
	Bezier(unsigned int size);
	virtual ~Bezier();
	virtual point Evaluate(float t);
};
int* GetPascal(int width);
int  RecursePascal(int row, int col);
bool outputBezier(point start, point control, point end, int resolution);

class Linear : public Interpolate {
private:
	float* mLength;
	
	virtual void create(unsigned int size);
	virtual void destroy();
	virtual bool accessorHelper();
	void calcLengths();
public:
	Linear();
	Linear(unsigned int size);
	~Linear();
	virtual point Evaluate(float t);
};
