#pragma once

struct point {
	float x,y,z;
};

float dist(float Lx, float Ly, float Lz, float Rx, float Ry, float Rz);
float dist(float Lx, float Ly, float Rx, float Ry);
float dist(point L, point R);
void swap(float& a, float& b);
void swap(point& a, point& b);
