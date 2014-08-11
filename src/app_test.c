/*
Copyright (c) 2014 fanzyflani & contributors.
See LICENCE.txt for licensing information (TL;DR: MIT-style).
*/

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#ifndef WIN32
#include <signal.h>
#endif

#include "fastblit.h"

uint32_t palbase[16];
uint32_t palbase_32bpp_64[256*2];
uint32_t shots1[2*128*128];
uint32_t shots1_expanded[8][2*128*(128+8)];
void *shots1_expanded_ptrs[8];

uint32_t surf4[80*480];

int main(int argc, char *argv[])
{
	FILE *fp;
	int i;

	fp = fopen("dat/pal.bin", "rb");
	fread(palbase, 1, 16*4, fp);
	fclose(fp);
	fp = fopen("dat/shots1.bin", "rb");
	fread(shots1, 1, 2*128*128, fp);
	fclose(fp);

	for(i = 0; i < 8; i++)
		shots1_expanded_ptrs[i] = shots1_expanded[i];

	fab_expand_surf_4mask_8x(shots1_expanded_ptrs, shots1, 128, 128, 128);

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE);
	SDL_Surface *screen = SDL_SetVideoMode(640, 480, 32, 0);

#ifndef WIN32
	signal(SIGTERM, SIG_DFL);
	signal(SIGINT,  SIG_DFL);
#endif

	for(i = 0; i < 100; i++)
	{
		memset(surf4, 0x88, 80*480*4);
		fab_blit_expanded_unclipped_4mask_to_4(surf4, shots1_expanded_ptrs,
			640, 128,
			i, 0, 0, 0,
			128, 128);

		fab_convert_pal_4bppbot_32_to_32bpp_64(palbase_32bpp_64, palbase);
		SDL_LockSurface(screen);
		fab_blit_aligned_unclipped_4_to_32(screen->pixels, surf4, palbase_32bpp_64,
			screen->pitch/4, 640,
			0, 0, 0, 0,
			640, 480);
		SDL_UnlockSurface(screen);
		SDL_Flip(screen);

		SDL_Delay(50);
	}

	return 0;
}

