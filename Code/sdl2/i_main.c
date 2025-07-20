#include "../doomdef.h"
#include "../d_main.h"
#include "../m_argv.h"
#include <SDL_rwops.h>

int mb_used = 32;

SDL_RWops* logstream;

#ifndef FORCESDLMAIN
int main(int argc, char **argv)
#else
int SDL_main(int argc, char** argv)
#endif
{
	myargc = argc;
	myargv = argv; /// \todo pull out path to exe from this string


	// init logstream
	logstream = SDL_RWFromFile("sdllog.txt", "a");
	if (!logstream)
		I_Error("Unable to initialize log file.");

	// startup SRB2
	CONS_Printf ("Setting up SRB2...\n");
	D_SRB2Main();
	CONS_Printf ("Entering main game loop...\n");
	// never return
	D_SRB2Loop();

	// return to OS
#ifndef __GNUC__
	return 0;
#endif
}