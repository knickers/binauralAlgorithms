#include <cmath>
using namespace std;
#include "common.h"

#define PI = 3.141592653589793;

// Platform-dependent sleep routines.
#if defined(__WINDOWS_ASIO__) || defined(__WINDOWS_DS__)
	#include <windows.h>
	#define SLEEP(milliseconds) Sleep((DWORD)milliseconds)
#else // Unix variants
	#include <unistd.h>
	#define SLEEP(milliseconds) usleep((unsigned long)(milliseconds * 1000.0))
#endif

float dist(float Lx, float Ly, float Lz, float Rx, float Ry, float Rz) {
	float x = Rx - Lx;
	float y = Ry - Ly;
	float z = Rz - Lz;
	return sqrt(x*x + y*y + z*z);
}

float dist(float Lx, float Ly, float Rx, float Ry) {
	return dist(Lx,Ly,0, Rx,Ry,0);
}

float dist(point L, point R) {
	return dist(L.x,L.y,L.z, R.x,R.y,R.z);
}

void swap(float& a, float& b) {
	float t = a;
	a = b;
	b = t;
}

void swap(point& a, point& b) {
	point t = a;
	a = b;
	b = t;
}
