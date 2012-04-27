#include <cmath>
#include "common.h"

struct ITLD {
	float ITD, ILD;
};

// Calculates the Interaraul Time Delay for the diven source point with the
//   listener being at the origin.
// Return value: <0 = delay the left side  >0 delay the right side
float ITD(float x, float y) {
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
	
	// The difference between the distances, converted to seconds
	// <0 = Source on the left side
	//  0 = Source is in the middle
	// >0 = source on the right side
	return (L - R)/S;
}
