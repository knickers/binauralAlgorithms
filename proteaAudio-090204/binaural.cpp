#include "proAudioRt.h"
#include <cstdio>
#include <cstdlib>

using namespace std;

// Platform-dependent sleep routines.
#if defined(__WINDOWS_ASIO__) || defined(__WINDOWS_DS__)
	#include <windows.h>
	#define SLEEP(milliseconds) Sleep((DWORD)milliseconds)
#else // Unix variants
	#include <unistd.h>
	#define SLEEP(milliseconds) usleep((unsigned long)(milliseconds*1000.0))
#endif

int main(int argc, char **argv) {
	if (argc<2) {
		printf("usage: %s audiofile\n", argv[0]);
		return 1;
	}
	DeviceAudio* audio = DeviceAudioRt::create();
	if (!audio) {
		fprintf(stderr, "ERROR opening audio device. Abort.\n");
		return 1;
	}
	
	float volume = (argc>2) ? atof(argv[2]) : 1.0f;
	float pitch  = (argc>3) ? atof(argv[3]) : 1.0f;
	printf("volume %f\n pitch %f\nLoading Sample...", volume, pitch);
	unsigned int sample1 = audio->sampleFromFile(argv[1], 1.0f);
	if (sample1) {
		printf("Done.\nPlaying...");
		fflush(stdout);
		// Sample VolumeL VolumeR Disparity Pitch
		audio->soundPlay(sample1, 1.0f, 1.0f, 0.0f, 1.0f);
	}
	
	// main loop:
	while (audio->soundActive()) {
		// Sample VolumeL VolumeR Disparity Pitch
		//audio->soundUpdate(sample1, 1.0f, 1.0f, 0.0f, 1.0f);
		SLEEP(20);
	}
	printf("Finished.\n");
	
	return 0;
}
