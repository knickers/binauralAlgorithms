#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_mixer.h"

Mix_Chunk *phaser = NULL;
Mix_Chunk *one = NULL;
Mix_Chunk *oneEnd = NULL;
Mix_Chunk *two = NULL;
Mix_Chunk *twoEnd = NULL;
Mix_Chunk *three = NULL;
Mix_Chunk *threeEnd = NULL;
Mix_Chunk *four = NULL;
Mix_Chunk *fourEnd = NULL;
Mix_Chunk *five = NULL;
Mix_Chunk *fiveEnd = NULL;
Mix_Chunk *six = NULL;
Mix_Chunk *sixEnd = NULL;
Mix_Music *music = NULL;

int gunChannel = -1;

void handleKey(SDL_KeyboardEvent key);
void shoot(Mix_Chunk *gun, Mix_Chunk *end, int type);
void musicDone();

int main(void) {
	SDL_Surface *screen;
	SDL_Event event;
	int done = 0;
	/* Same setup as before */
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16;
	int audio_channels = 2;
	int audio_buffers = 4096;
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
		printf("Unable to open audio!\n");
		exit(1);
	}
	/* Pre-load sound effects */
	phaser = Mix_LoadWAV("phaser.wav");
	one = Mix_LoadWAV("sounds/1.wav");
	oneEnd = Mix_LoadWAV("sounds/1-end.wav");
	two = Mix_LoadWAV("sounds/2.wav");
	twoEnd = Mix_LoadWAV("sounds/2-end.wav");
	three = Mix_LoadWAV("sounds/3.wav");
	threeEnd = Mix_LoadWAV("sounds/3-end.wav");
	four = Mix_LoadWAV("sounds/4.wav");
	fourEnd = Mix_LoadWAV("sounds/4-end.wav");
	five = Mix_LoadWAV("sounds/5.wav");
	fiveEnd = Mix_LoadWAV("sounds/5-end.wav");
	six = Mix_LoadWAV("sounds/6.wav");
	sixEnd = Mix_LoadWAV("sounds/6-end.wav");
	screen = SDL_SetVideoMode(320, 240, 0, 0);
	while(!done) {
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
			case SDL_QUIT:
				done = 1;
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				handleKey(event.key);
				break;
			}
		}
		SDL_Delay(50);
	}
	Mix_CloseAudio();
	SDL_Quit();
}

void handleKey(SDL_KeyboardEvent key) {
	switch(key.keysym.sym) {
	case SDLK_p:
		shoot(phaser, NULL, key.type);
		break;
	case SDLK_1:
		shoot(one, oneEnd, key.type);
		break;
	case SDLK_2:
		shoot(two, twoEnd, key.type);
		break;
	case SDLK_3:
		shoot(three, threeEnd, key.type);
		break;
	case SDLK_4:
		shoot(four, fourEnd, key.type);
		break;
	case SDLK_5:
		shoot(five, fiveEnd, key.type);
		break;
	case SDLK_6:
		shoot(six, sixEnd, key.type);
		break;
	case SDLK_m:
		if(key.state == SDL_PRESSED) {
			if(music == NULL) {
				music = Mix_LoadMUS("music.ogg");
				Mix_PlayMusic(music, 0);
				Mix_HookMusicFinished(musicDone);
			} else {
				Mix_HaltMusic();
				Mix_FreeMusic(music);
				music = NULL;
			}
		}
		break;
	}
}

void shoot(Mix_Chunk *gun, Mix_Chunk *end, int type) {
	if(type == SDL_KEYDOWN) {
		if(gunChannel < 0) {
			gunChannel = Mix_PlayChannel(-1, gun, -1);
		}
	} else {
		Mix_HaltChannel(gunChannel);
		gunChannel = -1;
		Mix_PlayChannel(-1, end, 0);
	}
}

void musicDone() {
	Mix_HaltMusic();
	Mix_FreeMusic(music);
	music = NULL;
}
