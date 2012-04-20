#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdint.h>
using namespace std;
#include "audio.h"

void endWithError(char* msg) {
	// Display error message in console
	cout << msg << "\n";
	exit(0);
}

audio::audio() {
	mSrc.init((char*)"sounds/side_Both.wav");
	
	// Now OpenAL needs to be initialized
	device = alcOpenDevice(NULL); // Open the device
	if(!device)
		endWithError((char*)"no sound device"); // Error during device oening
	context = alcCreateContext(device, NULL); // Give the device a context
	alcMakeContextCurrent(context); // Make the context the current
	if(!context)
		endWithError((char*)"no sound context");
		// Error during context handeling

	// Generate one OpenAL Buffer and link to the source's buffer
	alGenBuffers(1, &mSrc.buf);
	// Generate one OpenAL Source and link to the source's source
	alGenSources(1, &mSrc.src);
	if(alGetError() != AL_NO_ERROR)
		endWithError((char*)"Error GenSource");
		// Error during buffer/source generation
	cout << "got GenSource\n";

	alBufferData(mSrc.buf, mSrc.frmt, mSrc.data, mSrc.size, mSrc.freq());
	// Store the sound data in the OpenAL Buffer
	if(alGetError() != AL_NO_ERROR)
		endWithError((char*)"Error loading ALBuffer");
		// Error during buffer loading
	cout << "got ALBuffer\n";

	//Sound setting variables
	mPos[0] = 0; mPos[1] = 0; mPos[2] = 0; // Listener Position
	mVel[0] = 0; mVel[1] = 0; mVel[2] = 0; // Listener Velocity
	mOri[0] = 0; mOri[1] = 1; mOri[2] = 0; // Listener Forward Vector
	mOri[3] = 0; mOri[4] = 0; mOri[5] = 1; // Listener Up Vector

	//Listener
	alListenerfv(AL_POSITION,   mPos); // Set listener position
	alListenerfv(AL_VELOCITY,   mVel); // Set listener velocity
	alListenerfv(AL_ORIENTATION,mOri); // Set listener orientation

	//Source
	alSourcei (mSrc.src, AL_BUFFER,   mSrc.buf); // Source-Buffer link
	alSourcef (mSrc.src, AL_PITCH,    1.0f);     // Source pitch(hi-low)
	alSourcef (mSrc.src, AL_GAIN,     1.0f);     // Source gain (volume)
	alSourcefv(mSrc.src, AL_POSITION, mSrc.pos); // Source position
	alSourcefv(mSrc.src, AL_VELOCITY, mSrc.vel); // Source velocity
	alSourcei (mSrc.src, AL_LOOPING,  AL_TRUE);  // Source loop sound?
}

audio::~audio() {
	fclose(mSrc.fp);               // Close the WAVE file
	delete[] mSrc.data;            // Delete the sound data buffer
	alDeleteSources(1, &mSrc.src); // Delete the OpenAL Source
	alDeleteBuffers(1, &mSrc.buf); // Delete the OpenAL Buffer
	alcMakeContextCurrent(NULL); // Make no context current
	alcDestroyContext(context);  // Destroy the OpenAL Context
	alcCloseDevice(device);      // Close the OpenAL Device
}

void audio::play() {
	alSourcePlay(mSrc.src); //Play the sound buffer linked to the source
	if (alGetError() != AL_NO_ERROR)
		endWithError((char*)"Error playing sound");
	cout << "\nPlaying sound...\n\n";
}

void audio::move(float x, float y) {
/*	static float rX = 3;
	static float rY = 2;
	static float t = 0;
	pos[0] = rX*cos(t);
	pos[1] = rY*sin(t);
	t += .00004;
	if (t > 6.28)
		t = 0;
	printf("Angle: %f  \r", t*180/3.1415926);*/
	mSrc.pos[0] = x;
	mSrc.pos[1] = y;
	alSourcefv(mSrc.src, AL_POSITION, mSrc.pos);
}

source::source() {
	pos[0] = 0; pos[1] = 0; pos[2] = 0;   // Source Position
	vel[0] = 0; vel[1] = 0; vel[2] = 0;   // Source Velocity
}

source::~source() {
}

// Loading of the WAVE file
void source::init(char* file) {
	fp = fopen(file, "rb"); // Open the WAVE file
	if (!fp)
		endWithError((char*)"\nFailed to open file"); // Could not open file
	cout << endl << file << "\ngot file";

	// Check that the WAVE file is OK
	// Reads the first bytes in the file. Should be "RIFF"
	if (fread(type,sizeof(char),4,fp) != 4 || strcmp(type, "RIFF") !=0)
		endWithError ((char*)"\nNo RIFF"); // Not RIFF
	cout << ", RIFF";

	// Continue to read the file
	fread(&size, sizeof(DWORD),1,fp);

	// Continue to read the file. This part should be "WAVE"
	if (fread(type,sizeof(char),4,fp) != 4 || strcmp(type, "WAVE") != 0)
		endWithError((char*)"\nNot WAVE"); // Not WAVE
	cout << ", WAVE";

	// Continue to read the file. This part should be "fmt "
	if (fread(type,sizeof(char),4,fp) != 4 || strcmp(type, "fmt ") != 0)
		endWithError((char*)"\nNo fmt "); // Not fmt
	cout << ", frmt";

	// Now we know that the file is an acceptable WAVE file
	// Info about the WAVE data is now read and stored
	fread(&chunkSize,     sizeof(DWORD), 1, fp);
	fread(&formatType,    sizeof(short), 1, fp);
	fread(&channels,      sizeof(short), 1, fp);
	fread(&sampleRate,    sizeof(DWORD), 1, fp);
	fread(&byteRate,      sizeof(DWORD), 1, fp);
	fread(&align,         sizeof(short), 1, fp);
	fread(&bitsPerSample, sizeof(short), 1, fp);

	// Continue to read the file. This part should be "data"
	if (fread(type,sizeof(char),4,fp) != 4 ||
	(type[0]!='d' && type[1]!='a' && type[2]!='t' && type[3]!='a')) {
		if (strcmp(type, "LIST") == 0) { // Metadata information
			cout << "\nfound LIST";
			while (strcmp(type, "data") != 0) {
				fread(type, sizeof(char),4,fp); // Look at next 4 bytes
			}
		} else {
			cout << endl << type[0] << type[1] << type[2] << type[3] << " data";
			cout << endl << strcmp(type,"data");
			endWithError((char*)"\nNo data"); // Not DATA
		}
	}
	cout << ", data";

	// The size of the sound data is read
	fread(&dataSize, sizeof(DWORD), 1, fp);

	// Display the info about the WAVE file
	cout << "\n\n";
	cout << "Format Type: " << formatType    << "\n";
	cout << "   Channels: " << channels      << "\n";
	cout << "Sample Rate: " << sampleRate    << "\n";
	cout << "   ByteRate: " << byteRate      << "\n";
	cout << "bits/Sample: " << bitsPerSample << "\n";
	cout << "Block align: " << align         << "\n";
	cout << "  Data Size: " << dataSize      << "\n\n";

	data = new unsigned char[dataSize];
	// Allocate memory for the sound data
	cout << fread(data, 1, dataSize, fp) << " bytes loaded\n";
	// Read the sound data and display the number of bytes loaded.
	// Should be the same as the Data Size if OK

	//Figure out the format of the WAVE file
	if(bitsPerSample == 8) {
		if(channels == 1)
			frmt = AL_FORMAT_MONO8;
		else if(channels == 2)
			frmt = AL_FORMAT_STEREO8;
	} else if(bitsPerSample == 16) {
		if(channels == 1)
			frmt = AL_FORMAT_MONO16;
		else if(channels == 2)
			frmt = AL_FORMAT_STEREO16;
	}
	if(!frmt)
		endWithError((char*)"Wrong BitPerSample"); // Not valid format
	cout << "got format: " << frmt << "\n";
}

int source::freq() {
	return sampleRate;
}
