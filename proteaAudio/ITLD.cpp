#include <cmath>
#include <cfloat>
#include "ITLD.h"
#include "common.h"

// Calculates the Interaraul Time Delay and Interaural Level Difference for the
// given source point, the listener being at the origin.
// Return value: Delay in seconds
//  <0 = Source is on the right side, delay left side
//   0 = Source is in the middle, no delay
//  >0 = Source is on the left side, delay right side
ITLD TimeLevelDiff(point p) {
	return TimeLevelDiff(p.x,p.y,p.z);
}
ITLD TimeLevelDiff(double x, double y, double z) {
	// All lengths are in meters, all angles are in radians
	//static double INF = 1000;//DBL_MAX;
	static double S = 340.29; // Speed of sound at sea level in meters / second
	static double E = 0.16;   // Distance between the ears (average of 16 cm)
	static double H = E/2;    // Half the distance between the ears
	double L = 0, R = 0;      // Distance to the right and left ears
	double D = dist(0,0,0, x,y,z);// Distance to the sound source
	double A = acos(H/D);     // Angle from source vector to tangent intersectio
	double B = acos(x/D);     // Angle between source and x-axis (dot product)
	double V = sin(A)*D;      // Distance fron source to tangent intersection
	
	// Calculate distances to the ears
	if (x < -H) { // To the left of the left ear
		L = dist(-H,0,0, x,y,z);
		R = V + H*(B-A);
	} else if (x > H) { // To the right of the right ear
		L = V + H*(PI-B-A);
		R = dist(H,0,0, x,y,z);
	} else { // In between the ears
		L = V + H*(PI-B-A);
		R = V + H*(B-A);
	}
	
	ITLD diff;
	// The difference between the distances, converted to seconds
	diff.ITD = (R - L)/S;
	// Find some decent function
	diff.ILD.l = (L > R) ? 1 / ((D+L-R)/25+1) : 1 / (D/25+1);
	diff.ILD.r = (R > L) ? 1 / ((D+R-L)/25+1) : 1 / (D/25+1);
	return diff;
}
