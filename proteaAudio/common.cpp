#include <cmath>
using namespace std;
#include "common.h"

double dist(double Lx, double Ly, double Lz, double Rx, double Ry, double Rz) {
	double x = Rx - Lx;
	double y = Ry - Ly;
	double z = Rz - Lz;
	return sqrt(x*x + y*y + z*z);
}

double dist(double Lx, double Ly, double Rx, double Ry) {
	return dist(Lx,Ly,0, Rx,Ry,0);
}

double dist(point L, point R) {
	return dist(L.x,L.y,L.z, R.x,R.y,R.z);
}

void swap(double& a, double& b) {
	double t = a;
	a = b;
	b = t;
}

void swap(point& a, point& b) {
	point t = a;
	a = b;
	b = t;
}
