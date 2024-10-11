/*******************************************************************************
 * This internal C header file is part of the MIRAGE Game Engine and distributed
 * under the MIT License, any question or modification regarding this file
 * should be done on the official comunication channels, mainly on github.com.
 *
 * This file is concerned about the map logic of the game engine, like:
 *  - loading MAP data
 *  - rendering the data
 *  - others
 * please be aware of the constant change of this engine internals as it's 
 * always evolving to be more error-prone and easy to use, so expect to have big
 * changes between releases.
 *                                                  - The MIRAGE Developer Team
*******************************************************************************/

#ifndef MAP_H
#define MAP_H

#include "../types/types.h"
#include <cglm/types.h>

#define LINEDEF_FLAGS_TWO_SIDED 0x0004

typedef struct linedef {
    u16 start_index, end_index;
    u16 flags;
} linedef_t;

typedef struct map {
    isize number_of_vertices;
    vec2* vertices;

    vec2 min, max;

    isize number_of_linedefs;
    linedef_t* linedefs;
} map_t;

void free_map(map_t* map);


#endif
