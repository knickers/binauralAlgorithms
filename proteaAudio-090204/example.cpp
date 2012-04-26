#include "proAudioRt.h"

int main( int argc, char **argv ) {
	// Create an audio device using the RtAudio backend and default parameters:
	DeviceAudio* audio=DeviceAudioRt::create();
	if(!audio) { // Exit in case of errors
		printf("Error: Cannot Find Audio.\n");
		return 1;
	}
	
	// Load and play a sample:
	unsigned int sample = audio->sampleFromFile("sample.ogg");
	if(sample) audio->soundPlay(sample);
	
	// Wait until the sound has finished:
	// For simplicity's sake, busy wait instead of the preferable sleep() call
	while(audio->soundActive());
	
	// cleanup and exit:
	audio->destroy();
	return 0;
}
