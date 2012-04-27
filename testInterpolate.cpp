#include <iostream>
#include <stdio.h>
using namespace std;
#include "interpolate.h"
#include "common.h"

int main() {
	cout << "\n\tWelcome to Nick's Line-Interpolation classes.\n";
	Bezier b;
	Linear l;
	point p = {0,0,0};
	b.AddPoint(p);
	l.AddPoint(p);
	p.x=1; p.y=1;
	b.AddPoint(p);
	l.AddPoint(p);
	p.x=2; p.y=1;
	b.AddPoint(p);
	l.AddPoint(p);
	p.x=3; p.y=0;
	b.AddPoint(p);
	l.AddPoint(p);
	
	cout << endl;
	b.PrintPoints();
	cout << endl;
	
	float res = 10.0;
	for (int i=0; i<=res; i++) {
		point q = b.Evaluate(i/res);
		printf("Bezier(%f) (%f, %f, %f)\n", i/res, q.x,q.y,q.z);
	}
	cout << endl;
	for (int i=0; i<=res; i++) {
		point q = l.Evaluate(i/res);
		printf("Linear(%f) (%f, %f, %f)\n", i/res, q.x,q.y,q.z);
	}
	return 0;
}
