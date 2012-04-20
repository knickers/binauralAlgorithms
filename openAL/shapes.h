#ifndef SHAPES_H
#define SHAPES_H
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;
#include "graphics.h"
#include "LinAlg.h"
#include "io.h"

struct point2d {double x, y;};
struct point3d {double x, y, z;};
point3d operator + (const point3d & lhs, const point3d & rhs);
point3d operator - (const point3d & lhs, const point3d & rhs);

void DrawAxis(double length, float xColor[], float yColor[], float zColor[]);
void FindTriangleNormal(double x[], double y[], double z[], double n[]);
void FindTriangleNormal2(double cp[], double p1[], double p2[], double n[]);
point3d FindTriangleNormal(point3d cp, point3d p1, point3d p2);
//Vector FindTriangleNormal(point cp, point p1, point p2);
void SpherePoint(double radius, double upAngle, double panAngle, double point_out[3]);
point3d SpherePoint(double radius, double upAngle, double panAngle);
double rtod(double radian);
double dtor(double degree);

// 2d Shapes
void DrawPoint(double x, double y);
void DrawLine(double x1, double y1, double x2, double y2);
void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3);
void DrawRectangle(double x1, double y1, double x2, double y2, bool hollow);
void FadeRectangle(double x1, double y1, double x2, double y2, float color[], bool vert);
void RotateRectangle(double x1, double y1, double x2, double y2, double width);
void RotateRectangle2(double x1, double y1, double x2, double y2, double width);
point2d RotateRectangle3(double x, double y, double length, double width, double radAngle);
void DrawCircle(double x, double y, double radius, bool hollow);
void DrawCircle(double x, double y, double radius, float inColor[], float outColor[]);
void DrawCircle(double x, double y, double xR, double yR, float inColor[], float outColor[]);
void DrawCircle(double x, double y, double xR, double yR, double xOff, double yOff, float inColor[], float outColor[]);

// 3d Shapes
void DrawLine3d(double x1, double y1, double z1, double x2, double y2, double z2);
void DrawRectangle3d(point3d p1, point3d p2);
void DrawWireBox(double X_length, double Y_width, double Z_height);
void DrawSolidBox(double X_length, double Y_width, double Z_height);
void DrawTextureBox(double X_length, double Y_width, double Z_height, GLuint TexNum);
void DrawCurveBox(double width, double depth, double radius, double degreeAngle, double slices);
void DrawWireCylinder(double length, double radius, int slices, bool hollow);
void DrawSolidCylinder(double length, double radius, double slices, bool hollow);
void DrawPartialCylinder(double length, double radius, double angle, double slices, bool hollow);
void DrawTaperCylinder(double length, double bottomRadius, double topRadius, int slices, bool hollow);
void DrawCurveCylinder(double innerRadius, double outerRadius, double angle, int stacks, int slices, bool hollow);
void DrawSolidSphere(double radius, double begPan, double endPan, double resPan, double begUp, double endUp, double resUp);
void DrawCoilSpring(double innerRadius, double outerRadius, double length, double wraps, int stacks, int slices, bool hollow);
void DrawPartialToroid(double RingRadius, double TubeRadius, double startAngle, double endAngle, int stacks, int slices);
bool RotatePolygon(char file[], double radAngle, int slices, bool smoothVert, bool smoothHor);
bool RotatePolygon(vector<point2d> outline, double radAngle, int slices, bool smoothVert, bool smoothHor);

#endif;