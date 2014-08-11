/*
Copyright (c) 2014 fanzyflani & contributors.
See LICENCE.txt for licensing information (TL;DR: MIT-style).
*/

#include "common.h"

void fab_expand_surf_4_8x(void **dest, void *src, int w, int h, int pitch)
{
	int x, y, rot;

	/* Assertions */
	assert((w&7) == 0);
	assert((pitch&7) == 0);

	/* First image is just a memcpy */
	memcpy(dest[0], src, (pitch*h)>>1);

	/* The other 7 images require some rotation */
	for(rot = 1; rot < 8; rot++)
	{
		int brot = (32-(rot<<2));
		uint32_t *sp = src;
		uint32_t *dp = dest[rot];
		uint32_t bm_on = ~((1<<brot)-1);
		uint32_t bm_off = ~bm_on;

		for(y = 0; y < h; y++)
		{
			uint32_t bufv = 0;

			for(x = 0; x < w; x++)
			{
				uint32_t sv = sp[x];
				sv = (sv<<brot) | (sv>>(32-brot));
				bufv |= sv & bm_on;
				dp[x] = bufv;
				bufv = sv & bm_off;
			}

			dp[w] = bufv;

			sp += pitch>>3;
			dp += (pitch>>3)+1;
		}
	}
}

void fab_expand_surf_4mask_8x(void **dest, void *src, int w, int h, int pitch)
{
	int x, y, rot;

	/* Assertions */
	assert((w&7) == 0);
	assert((pitch&7) == 0);

	/* First image is just a memcpy */
	memcpy(dest[0], src, (pitch*h));

	/* The other 7 images require some rotation */
	for(rot = 1; rot < 8; rot++)
	{
		int brot = (32-(rot<<2));
		uint32_t *sp = src;
		uint32_t *dp = dest[rot];
		uint32_t bm_on = ~((1<<brot)-1);
		uint32_t bm_off = ~bm_on;

		for(y = 0; y < h; y++)
		{
			uint32_t bufv = 0;
			uint32_t bufm = bm_off;

			for(x = 0; x < w; x++)
			{
				uint32_t sv = sp[(x<<1)+0];
				uint32_t sm = sp[(x<<1)+1];
				sv = (sv<<brot) | (sv>>(32-brot));
				sm = (sm<<brot) | (sm>>(32-brot));
				bufv |= sv & bm_on;
				bufm |= sm & bm_on;
				dp[(x<<1)+0] = bufv;
				dp[(x<<1)+1] = bufm;
				bufv = sv & bm_off;
				bufm = sm & bm_off;
			}

			dp[(w<<1)+0] = bufv;
			dp[(w<<1)+1] = bufm | bm_on;

			sp += pitch>>2;
			dp += (pitch>>2)+2;
		}
	}
}

