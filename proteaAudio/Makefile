#--- generic settings ----------------------------------------------
# settings for C++ compiler:
C = gcc
CC = g++
CFLAGS = -O2 -Wall # -D_DEBUG -g
INCDIR = -Irtaudio -Irtaudio/include -I../lua/src

# linker settings:
LCC = ar
LFLAGS = -rcs
LNAME = libproAudio.a
LIB = $(LNAME)
LIBDIR =

# settings for optional libSDL backend:
INCDIR += -I../archive/baseCode/include
SDLLIB = $(shell sdl-config --libs)
SDLDIR = $(shell sdl-config --cflags)

#--- platform specific settings ------------------------------------
ARCH = $(shell uname -s)
ifeq ($(ARCH),Linux)
	LIBS = $(LIBDIR) $(LIB) -lpthread -lasound
	LUALIB = -llua -ldl
	CFLAGS += $(shell sdl-config --cflags) -DHAVE_GETTIMEOFDAY -D__LINUX_ALSA__ #-D__LINUX_OSS__
	DLLFLAGS = -fPIC -shared
	DLLSUFFIX = .so
	EXESUFFIX =
else
	ifeq ($(ARCH),Darwin) # MacOSX
		LIBS = $(LIBDIR) $(LIB)
		LUALIB = -L/usr/local/lib -llua
		CFLAGS += -DHAVE_GETTIMEOFDAY -D__MACOSX_CORE__
		DLLFLAGS = -bundle
		DLLSUFFIX = .so
		EXESUFFIX = .app
	else # windows, MinGW
		LIBS = $(LIBDIR) $(LIB) -lole32 -ldsound -lwinmm -mconsole -s
		LUALIB = -L../lua/src -llua51
		SDLLIB = -lmingw32 -lSDLmain -lSDL -mconsole -s
		CFLAGS += -D__WINDOWS_DS__
		DLLFLAGS = -shared
		DLLSUFFIX = .dll
		EXESUFFIX = .exe
	endif
endif

#--- make targets and rules ----------------------------------------

# example for optional libSDL backend
sdl: binaural$(EXESUFFIX)

ALL = $(LNAME) binaural$(EXESUFFIX)
all: $(ALL)

binaural$(EXESUFFIX) : binaural.o proAudio.o proAudioSdl.o stb_vorbis.o interpolate.o common.o ITLD.o
	$(CC) $(CFLAGS) $^ $(SDLDIR) $(SDLLIB) -o $@

# generic rules
.cpp.o:
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@
clean:
	rm -f *.o *~ $(OBJ) $(ALL)

#--- project specific dependencies ---------------------------------
stb_vorbis.o: stb_vorbis.c
proAudio.o: proAudio.cpp proAudio.h
binaural.o: binaural.cpp proAudioSdl.h proAudio.h ITLD.h ITLD.cpp common.h common.cpp interpolate.h interpolate.cpp
ITLD.o: common.h common.cpp
common.o: common.h common.cpp
interpolate.o: interpolate.h interpolate.cpp
proAudioSdl.o: proAudioSdl.cpp proAudioSdl.h proAudio.h
