/*******************************************************************************
 * This internal C header file is part of the MIRAGE Game Engine and distributed
 * under the MIT License, any question or modification regarding this file
 * should be done on the official comunication channels, mainly on github.com.
 *
 * This file is concerned about rendering WAD files.
 *
 * please be aware of the constant change of this engine internals as it's 
 * always evolving to be more error-prone and easy to use, so expect to have big
 * changes between releases.
 *                                                  - The MIRAGE Developer Team
*******************************************************************************/

#ifndef FILE_WAD_H
#define FILE_WAD_H

#include "../../types/types.h"

typedef struct lump {
    str name;
    u8* data;
    // u32 offset;
    u32 size;
} lump_t;

typedef struct wad {
    str id;
    u32 number_of_lumps;
    // u32 directory_offset;
    lump_t* lumps;
} wad_t;

i32 load_wad_from_file(const str filename, wad_t* wad);
void free_wad(wad_t* wad);

#endif
