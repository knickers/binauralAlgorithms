#pragma once;

using namespace std;

struct point {
	float x,y,z;
};

class Interpolate {
protected:
	int  mSize;
	point* mCP;
	
	virtual void create(int size);
	virtual void destroy();
public:
	Interpolate();
	Interpolate(int numPoints);
	~Interpolate();
	virtual point Evaluate(float t)=0;
	
	bool AddPoint(point p);
	bool AddPoint(float x, float y, float z);
	bool SetPoint(int i, point p);
	bool SetPoint(int i, float x, float y, float z);
	bool SetPoints(point* p, int size);
	bool SetX(int i, float x);
	bool SetY(int i, float y);
	bool SetZ(int i, float z);
};

class Bezier : public Interpolate {
private:
	int* mPascal;
	point EvalCurve(float t, point* p, int size, int* pasc);
	
	virtual void create(int size);
	virtual void destroy();
public:
	Bezier();
	Bezier(int size);
	~Bezier();
	virtual point Evaluate(float t);
};
int* GetPascal(int width);
int  RecursePascal(int row, int col);
bool outputBezier(point start, point control, point end, int resolution);

class Linear : public Interpolate {
private:
	float* mLength;
	
	virtual void create(int size);
	virtual void destroy();
public:
	Linear();
	Linear(int size);
	~Linear();
	virtual point Evaluate(float t);
};
