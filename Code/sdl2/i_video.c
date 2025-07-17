#include "../doomdef.h"
#include "../command.h"
#include "../i_video.h"
#include <SDL.h>
#include "../screen.h"

rendermode_t rendermode = render_soft;

boolean highcolor = false;

boolean allow_fullscreen = false;

consvar_t cv_vidwait = {"vid_wait", "On", CV_SAVE, CV_OnOff, NULL, 0, 0, NULL};

SDL_Window* SDL_window;

SDL_DisplayMode SDL_displaymode;

SDL_Renderer* SDL_renderer;
SDL_Texture* window_texture;

// temp temp temp teMP TEMP TEMP TEMP TEMPORARY!!!
// once we have stuff displaying to the sdl2 window we'll have more than one video mode
#define VID_WIDTH 640
#define VID_HEIGHT 400
#define VID_BPP 1

void I_StartupGraphics(void){
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		I_Error("Could not initialize SDL2: %s\n", SDL_GetError());

	if(SDL_GetCurrentDisplayMode(0, &SDL_displaymode))
		I_Error("I_StartupGraphics(): Error while initializing display mode");

	// Init window (hardcoded to 640x400 for now) in the center of the screen
	SDL_window = SDL_CreateWindow("SRB2 March 2000 Prototype", SDL_displaymode.w >> 1, SDL_displaymode.h >> 1, VID_WIDTH, VID_HEIGHT, 0);

	if (!SDL_window) 
		I_Error("I_StartupGraphics(): Could not create window!");

	SDL_renderer = SDL_CreateRenderer(SDL_window, -1, SDL_RENDERER_ACCELERATED);
	if (!SDL_renderer)
		I_Error("I_StartupGraphics(): Could not create renderer!");

	window_texture = SDL_CreateTexture(SDL_renderer, SDL_PIXELFORMAT_RGB332, SDL_TEXTUREACCESS_STREAMING, VID_WIDTH, VID_HEIGHT);

	// just hardcoding the video mode for now, i just wanna get things drawing
	vid.modenum = NULL;
	vid.width = VID_WIDTH;
	vid.height = VID_HEIGHT;
	vid.bpp = VID_BPP;
	vid.rowbytes = VID_WIDTH * VID_BPP;

	
	// allocate buffer
	// We're gonna replace this soon right? Right????
	vid.buffer = malloc((vid.width * vid.height * vid.bpp * NUMSCREENS) + (vid.width * ST_HEIGHT * vid.bpp));
}

void I_ShutdownGraphics(void){
	SDL_DestroyRenderer(SDL_renderer);
	SDL_DestroyWindow(SDL_window);
}

void I_SetPalette(byte *palette)
{
	palette = NULL;
}

// For now, the only mode is 640x400 windowed

int VID_NumModes(void)
{
	return 1;
}

int VID_GetModeForSize(int w, int h)
{
	w = VID_WIDTH;
	h = VID_HEIGHT;
	return 0;
}

int VID_SetMode(int modenum)
{
	modenum = 0;
	return 0;
}


const char *VID_GetModeName(int modenum)
{
	modenum = 0;
	return NULL;
}

void I_UpdateNoBlit(void){}

void I_FinishUpdate(void)
{
	SDL_UpdateTexture(window_texture, NULL, vid.buffer, vid.rowbytes);
	SDL_RenderClear(SDL_renderer);
	SDL_RenderCopy(SDL_renderer, window_texture, NULL, NULL);
	SDL_RenderPresent(SDL_renderer);
}

void I_WaitVBL(int count)
{
	count = 0;
}

void I_ReadScreen(byte *scr)
{
	scr = NULL;
}

void VID_BlitLinearScreen(byte* srcptr, byte* destptr, int width, int height, int srcrowbytes, int destrowbytes){
	if (srcrowbytes == destrowbytes)
	{
		memcpy(destptr, srcptr, srcrowbytes * height);
	}
	else
	{
		while (height--)
		{
			memcpy(destptr, srcptr, width);
			destptr += destrowbytes;
			srcptr += srcrowbytes;
		}
	}
}

void I_BeginRead(void){}

void I_EndRead(void){}

