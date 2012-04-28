#include <cmath>
#include "common.h"

// Interaural Time/Level Difference
struct ITLD {
	float ITD, ILD;
};

// Calculates the Interaraul Time Delay and Interaural Level Difference for the
// given source point, the listener being at the origin.
// Return value: Delay in seconds
//  <0 = Source is on the right side, delay left side
//   0 = Source is in the middle, no delay
//  >0 = Source is on the left side, delay right side
ITLD TimeLevelDiff(float x, float y) {
	// All lengths are in meters, all angles are in radians
	static float S = 340.29;  // Speed of sound at sea level in meters / second
	static float E = 0.16;    // Distance between the ears (average of 16 cm)
	static float H = E/2;     // Half the distance between the ears
	float L = 0, R = 0;       // Distance to the right and left ears
	float D = dist(0,0, x,y); // Distance to the sound source
	float A = acos(H/D);      // Angle from source vector to tangent intersectio
	
	// Calculate distances to the ears
	if (x < -H) { // To the left of the left ear
		L = dist(-H,0, x,y);
		R = sin(A)*D + H*(atan2(y,x)-A);
	} else if (x > H) { // To the right of the right ear
		L = sin(A)*D + H*(PI-atan2(y,x)-A);
		R = dist(H,0, x,y);
	} else { // In between the ears
		L = sin(A)*D + H*(PI-atan2(y,x)-A);
		R = sin(A)*D + H*(atan2(y,x)-A);
	}
	
	ITLD diff;
	// The difference between the distances, converted to seconds
	diff.ITD = (L - R)/S;
	// Find some decent function
	diff.ILD = 0;
	return diff;
}
