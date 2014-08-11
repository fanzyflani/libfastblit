/*
Copyright (c) 2014 fanzyflani & contributors.
See LICENCE.txt for licensing information (TL;DR: MIT-style).
*/

#include "common.h"

void fab_blit_expanded_unclipped_4mask_to_4(void *dest, void **src, int dpitch, int spitch, int dx, int dy, int sx, int sy, int w, int h)
{
	int x, y;

	/* Assert stuff */
	assert((sx&7) == 0); /* TODO: remove this limitation */
	assert((w&7) == 0); /* TODO: remove this limitation */
	assert((spitch&7) == 0);
	assert((dpitch&7) == 0);
	assert(sx+w <= spitch);
	assert(dx+w <= dpitch);

	/* Calculate stuff */
	int imgsel = (sx-dx)&7;
	if(imgsel != 0) { spitch += 8; w += 8; }
	dx &= ~7;
	sx &= ~7;
	uint32_t *dp = (dest + (dx>>1) + ((dy*dpitch)>>1));
	uint32_t *sp = (src[imgsel] + sx + ((sy*spitch)));
	uint32_t smask_v_beg = (imgsel == 0 ? 0xFFFFFFFF : ~(0xFFFFFFFF>>(imgsel<<2)));
	uint32_t smask_m_beg = ~smask_v_beg;
	uint32_t smask_v_end = (imgsel == 0 ? 0xFFFFFFFF : (0xFFFFFFFF>>(imgsel<<2)));
	uint32_t smask_m_end = ~smask_v_end;

	/* Loop */
	for(y = 0; y < h; y++)
	{
		dp[0] = (dp[0] & (sp[0+1] | smask_m_beg)) ^ (sp[0+0] & smask_v_beg);
		for(x = 1; x < (w>>3)-1; x++)
			dp[x] = (dp[x] & sp[(x<<1)+1]) ^ sp[(x<<1)+0];
		dp[(w>>3)-1] = (dp[(w>>3)-1] & (sp[(w>>2)-1] | smask_m_end)) ^ (sp[(w>>2)-2] & smask_v_end);

		dp += dpitch>>3;
		sp += spitch>>2;
	}
}

