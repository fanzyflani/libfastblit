/*
Copyright (c) 2014 fanzyflani & contributors.
See LICENCE.txt for licensing information (TL;DR: MIT-style).
*/

#ifndef FAB_FASTBLIT_H
#define FAB_FASTBLIT_H

#include <stdint.h>

/* blit.c */
void fab_blit_aligned_unclipped_4_to_32(void *dest, void *src, uint32_t *pal64, int dpitch, int spitch, int dx, int dy, int sx, int sy, int w, int h);
void fab_blit_aligned_unclipped_unmasked_4mask_to_32(void *dest, void *src, uint32_t *pal64, int dpitch, int spitch, int dx, int dy, int sx, int sy, int w, int h);
void fab_blit_aligned_unclipped_4_to_4(void *dest, void *src, int dpitch, int spitch, int dx, int dy, int sx, int sy, int w, int h);
void fab_blit_aligned_unclipped_4mask_to_4(void *dest, void *src, int dpitch, int spitch, int dx, int dy, int sx, int sy, int w, int h);

/* blitexp.c */
void fab_blit_expanded_unclipped_4mask_to_4(void *dest, void **src, int dpitch, int spitch, int dx, int dy, int sx, int sy, int w, int h);

/* convert.c */
void fab_convert_pal_4bppbot_32_to_32bpp_64(uint32_t *dest, uint32_t *src);
void fab_convert_pal_4bppbot_16_to_16bppbot_32(uint32_t *dest, uint16_t *src);

/* expand.c */
void fab_expand_surf_4_8x(void **dest, void *src, int w, int h, int pitch);
void fab_expand_surf_4mask_8x(void **dest, void *src, int w, int h, int pitch);

#endif

