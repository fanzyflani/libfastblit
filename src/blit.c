/*
Copyright (c) 2014 fanzyflani & contributors.
See LICENCE.txt for licensing information (TL;DR: MIT-style).
*/

#include "common.h"

void fab_blit_aligned_unclipped_4_to_32(void *dest, void *src, uint32_t *pal64, int dpitch, int spitch, int dx, int dy, int sx, int sy, int w, int h)
{
	int x, y;

	/* Assert stuff */
	assert((spitch&7) == 0);
	assert((sx&7) == 0);
	assert((w&7) == 0);
	assert(sx+w <= spitch);
	assert(dx+w <= dpitch);

	/* Calculate stuff */
	uint32_t *dp = (dest + (dx<<2) + ((dy*dpitch)<<2));
	uint32_t *sp = (src  + (sx>>1) + ((sy*spitch)>>1));

	/* Loop */
	for(y = 0; y < h; y++)
	{
		for(x = 0; x < (w>>3); x++)
		{
			uint32_t s = sp[x];
			dp[(x<<3)+0] = pal64[(((s>> 0)&0xFF)<<1)+0];
			dp[(x<<3)+1] = pal64[(((s>> 0)&0xFF)<<1)+1];
			dp[(x<<3)+2] = pal64[(((s>> 8)&0xFF)<<1)+0];
			dp[(x<<3)+3] = pal64[(((s>> 8)&0xFF)<<1)+1];
			dp[(x<<3)+4] = pal64[(((s>>16)&0xFF)<<1)+0];
			dp[(x<<3)+5] = pal64[(((s>>16)&0xFF)<<1)+1];
			dp[(x<<3)+6] = pal64[(((s>>24)&0xFF)<<1)+0];
			dp[(x<<3)+7] = pal64[(((s>>24)&0xFF)<<1)+1];
		}

		dp += dpitch;
		sp += spitch>>3;
	}
}

void fab_blit_aligned_unclipped_unmasked_4mask_to_32(void *dest, void *src, uint32_t *pal64, int dpitch, int spitch, int dx, int dy, int sx, int sy, int w, int h)
{
	int x, y;

	/* Assert stuff */
	assert((spitch&7) == 0);
	assert((sx&7) == 0);
	assert((w&7) == 0);
	assert(sx+w <= spitch);
	assert(dx+w <= dpitch);

	/* Calculate stuff */
	uint32_t *dp = (dest + (dx<<2) + ((dy*dpitch)<<2));
	uint32_t *sp = (src  + sx + ((sy*spitch)));

	/* Loop */
	for(y = 0; y < h; y++)
	{
		for(x = 0; x < (w>>3); x++)
		{
			uint32_t sv = sp[(x<<1)+0];
			dp[(x<<3)+0] = pal64[(((sv>> 0)&0xFF)<<1)+0];
			dp[(x<<3)+1] = pal64[(((sv>> 0)&0xFF)<<1)+1];
			dp[(x<<3)+2] = pal64[(((sv>> 8)&0xFF)<<1)+0];
			dp[(x<<3)+3] = pal64[(((sv>> 8)&0xFF)<<1)+1];
			dp[(x<<3)+4] = pal64[(((sv>>16)&0xFF)<<1)+0];
			dp[(x<<3)+5] = pal64[(((sv>>16)&0xFF)<<1)+1];
			dp[(x<<3)+6] = pal64[(((sv>>24)&0xFF)<<1)+0];
			dp[(x<<3)+7] = pal64[(((sv>>24)&0xFF)<<1)+1];
		}

		dp += dpitch;
		sp += spitch>>2;
	}
}

void fab_blit_aligned_unclipped_4_to_4(void *dest, void *src, int dpitch, int spitch, int dx, int dy, int sx, int sy, int w, int h)
{
	int x, y;

	/* Assert stuff */
	assert((spitch&7) == 0);
	assert((dpitch&7) == 0);
	assert((sx&7) == 0);
	assert((dx&7) == 0);
	assert((w&7) == 0);
	assert(sx+w <= spitch);
	assert(dx+w <= dpitch);

	/* Calculate stuff */
	uint32_t *dp = (dest + (dx>>1) + ((dy*dpitch)>>1));
	uint32_t *sp = (src  + (sx>>1) + ((sy*spitch)>>1));

	/* Loop */
	for(y = 0; y < h; y++)
	{
		for(x = 0; x < (w>>3); x++)
			dp[x] = sp[x];

		dp += dpitch>>3;
		sp += spitch>>3;
	}
}

void fab_blit_aligned_unclipped_4mask_to_4(void *dest, void *src, int dpitch, int spitch, int dx, int dy, int sx, int sy, int w, int h)
{
	int x, y;

	/* Assert stuff */
	assert((spitch&7) == 0);
	assert((dpitch&7) == 0);
	assert((sx&7) == 0);
	assert((dx&7) == 0);
	assert((w&7) == 0);
	assert(sx+w <= spitch);
	assert(dx+w <= dpitch);

	/* Calculate stuff */
	uint32_t *dp = (dest + (dx>>1) + ((dy*dpitch)>>1));
	uint32_t *sp = (src  + sx + ((sy*spitch)));

	/* Loop */
	for(y = 0; y < h; y++)
	{
		for(x = 0; x < (w>>3); x++)
			dp[x] = (dp[x] & sp[(x<<1)+1]) ^ sp[(x<<1)+0];

		dp += dpitch>>3;
		sp += spitch>>2;
	}
}

