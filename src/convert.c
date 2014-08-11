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

