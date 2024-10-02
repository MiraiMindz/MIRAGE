#ifndef _RENDERER_H
#define _RENDERER_H

#include "../types/vector.h"

void init_renderer(int width, int height);
void clear_screen();

void renderer_draw_point(vec2_t point, float size, vec4_t color);

#endif
