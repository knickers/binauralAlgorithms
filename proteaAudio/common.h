#pragma once

const double PI = 3.141592653589793;

// Platform-dependent sleep routines.
#if defined(__WINDOWS_ASIO__) || defined(__WINDOWS_DS__)
	#include <windows.h>
	#define SLEEP(milliseconds) Sleep((DWORD)milliseconds)
#else // Unix variants
	#include <unistd.h>
	#define SLEEP(milliseconds) usleep((unsigned long)(milliseconds * 1000.0))
#endif

struct point {
	double x,y,z;
};

double dist(double Lx, double Ly, double Lz, double Rx, double Ry, double Rz);
double dist(double Lx, double Ly, double Rx, double Ry);
double dist(point L, point R);
void swap(double& a, double& b);
void swap(point& a, point& b);
