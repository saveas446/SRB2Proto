#include "../i_sound.h"
#include <SDL.h>
#ifdef HAVE_SDL_MIXER
#include <SDL_mixer.h>
#endif

#ifdef HAVE_SDL_MIXER
Mix_Music* music;
#endif

byte sound_started = 0;

void *I_GetSfx(sfxinfo_t *sfx)
{
	sfx = NULL;
	return NULL;
}

void I_FreeSfx(sfxinfo_t *sfx)
{
	sfx = NULL;
}

void I_StartupSound(void){
	SDL_setenv("SDL_MIXER_MIDI_DRIVER", "native", 1);
	SDL_Init(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void I_ShutdownSound(void){
	Mix_CloseAudio();
}

//
//  SFX I/O
//

int I_StartSound(int id, int vol, int sep, int pitch, int priority)
{
	id = vol =sep = pitch = priority = 0;
	return -1;
}

void I_StopSound(int handle)
{
	handle = 0;
}

int I_SoundIsPlaying(int handle)
{
	handle = 0;
	return -1;
}

void I_UpdateSoundParams(int handle, int vol, int sep, int pitch)
{
	handle = vol = sep = pitch = 0;
}

void I_SetSfxVolume(int volume)
{
	volume = 0;
}

//
//  MUSIC I/O
//
byte music_started = 0;

void I_InitMusic(void){}

void I_ShutdownMusic(void){}

void I_PauseSong(int handle)
{
	handle = 0;
}

void I_ResumeSong(int handle)
{
	handle = 0;
}

//
//  MIDI I/O
//

byte midimusic_started = 0;

void I_InitMIDIMusic(void){}

void I_ShutdownMIDIMusic(void){}

void I_SetMusicVolume(int volume)
{
	Mix_VolumeMusic(volume << 2);
}

int I_RegisterSong(void *data, int len)
{
#ifdef HAVE_SDL_MIXER
	SDL_RWops* rw = SDL_RWFromConstMem(data, len);
	music = Mix_LoadMUSType_RW(rw, MUS_MID, 1);
#else
	data = NULL;
	len = 0;
	return -1;
#endif
}

void I_PlaySong(int handle, int looping)
{
#ifdef HAVE_SDL_MIXER
	Mix_PlayMusic(music, -1);
#else
	handle = 0;
	looping = 0;
#endif
}

void I_StopSong(int handle)
{
	handle = 0;
}

void I_UnRegisterSong(int handle)
{
	handle = 0;
}

//
//  DIGMUSIC I/O
//

byte digmusic_started = 0;

void I_InitDigMusic(void){}

void I_ShutdownDigMusic(void){}

boolean I_StartDigSong(const char *musicname, int looping)
{
	musicname = NULL;
	looping = 0;
	return false;
}

void I_StopDigSong(void){}

void I_SetDigMusicVolume(int volume)
{
	volume = 0;
}

