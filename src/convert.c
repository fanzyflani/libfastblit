/*
Copyright (c) 2014 fanzyflani & contributors.
See LICENCE.txt for licensing information (TL;DR: MIT-style).
*/

#include "common.h"

void fab_convert_pal_4bppbot_32_to_32bpp_64(uint32_t *dest, uint32_t *src)
{
	int i;

	for(i = 0; i < 256; i++)
	{
		dest[(i<<1)+0] = src[i&15];
		dest[(i<<1)+1] = src[i>>4];
	}
}

void fab_convert_pal_4bppbot_16_to_16bppbot_32(uint32_t *dest, uint16_t *src)
{
	int i;

	for(i = 0; i < 256; i++)
		dest[i] = ((uint32_t)src[i&15]) | (((uint32_t)src[i>>4]) << 16);
}

void fab_convert_pal_4bppbot_32_xrgb_to_4bppbot_16_rgb(uint16_t *dest, uint32_t *src)
{
	int i;
	uint32_t r,g,b;

	for(i = 0; i < 16; i++)
	{
		uint32_t v = src[i];

		r = (v>>16) & 0xFF;
		g = (v>> 8) & 0xFF;
		b = (v>> 0) & 0xFF;

		r += 4;
		g += 2;
		b += 4;

		if(r > 0xFF) r = 0xFF;
		if(g > 0xFF) g = 0xFF;
		if(b > 0xFF) b = 0xFF;

		r >>= 3;
		g >>= 2;
		b >>= 3;

		dest[i] = (r<<11) | (g<<5) | b;
	}

}

