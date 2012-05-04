#include <cstring>
#include <cmath>
#include <string>
#include "SDL.h"
#include "proAudioSdl.h"
using namespace std;
#include "ITLD.h"
#include "common.h"
#include "interpolate.h"

int main(int argc, char **argv) {
	if(argc<2) {
		fprintf(stderr,"usage: %s audioFile\n",argv[0]);
		return 1;
	}
	DeviceAudio* audio=DeviceAudioSdl::create();
	if(!audio) {
		fprintf(stderr, "ERROR opening audio device. Abort.\n");
		return 1;
	}
	
	unsigned int sample1=audio->sampleFromFile(argv[1]);
	if(sample1) audio->soundPlay(sample1, 1.0f,1.0f,0.0f, 1.0f); // Pitch
	
	Bezier b(3);
	b.setPoint(0, 1,0,0);
	b.setPoint(1, 0,1,0);
	b.setPoint(2, -1,0,0);
	
	double time = 0;
	double length = audio->soundLength(sample1);
	ITLD diff = TimeLevelDiff(b.Evaluate(time));
	
	// main loop:
	while(audio->soundActive()) {
		time = audio->soundTime(sample1);
		diff = TimeLevelDiff(b.Evaluate(time/length));
		
		audio->soundUpdate(sample1, 1.0f,1.0f, diff.ITD,1.0f);
		
		printf("ITD = %f TIME = %f/%f\r", diff.ITD, time, length);
		fflush(stdout);
		
		SDL_Delay(1);
	}
	
	return 0;
}
