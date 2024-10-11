#ifndef _ENGINE_H
#define _ENGINE_H

#include "../files/wad/wad.h"
#include "../types/types.h"

void engine_init(wad_t *wad, const str mapname);
void engine_update(f32 delta_time);
void engine_renderer();

#endif
