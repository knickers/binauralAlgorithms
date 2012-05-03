#pragma once
#include "common.h"

// Interaural Time/Level Difference
struct ITLD {
	double ITD, ILD;
};

// Calculates the Interaraul Time Delay and Interaural Level Difference for the
// given source point, the listener being at the origin.
// Return value: Delay in seconds
//  <0 = Source is on the right side, delay left side
//   0 = Source is in the middle, no delay
//  >0 = Source is on the left side, delay right side
ITLD TimeLevelDiff(double x, double y, double z);
ITLD TimeLevelDiff(point p);
