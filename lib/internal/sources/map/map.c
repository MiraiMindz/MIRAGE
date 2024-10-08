/*******************************************************************************
 * This internal C source file is part of the MIRAGE Game Engine and distributed
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

#include "../../map/map.h"
#include "../../types/types.h"
#include <stdlib.h>

void free_map(map_t* map) {
    if (map == NULL) {
        return;
    }

    // for (i64 i = 0; i < map->number_of_vertices; i++) {
    //     free(map->vertices[i]);
    // }
    
    free(map->vertices);
    map->vertices = 0;
}
