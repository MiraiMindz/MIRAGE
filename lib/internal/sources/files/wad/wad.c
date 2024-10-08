/*******************************************************************************
 * This internal C source file is part of the MIRAGE Game Engine and distributed
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../files/wad/wad.h"
#include "../../../types/types.h"

// This macro reads N bytes from any buffer in little endian
#define READ_LE32I(buffer, offset) ((buffer)[(offset)] | \
    ((buffer)[(offset + 1)] << 8) | \
    ((buffer)[(offset + 2)] << 16) | \
    ((buffer)[(offset + 3)] << 24))


i32 load_wad_from_file(const str filename, wad_t* wad) {
    if (wad == NULL) {
        return 1;
    }
    
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        return 2;
    }

    fseek(fp, 0, SEEK_END);
    isize file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    u8* buffer = malloc(file_size);
    fread(buffer, file_size, 1, fp);
    
    if (file_size < 12) {
        return 3;
    }
    // The 4 bytes of the ID and the null terminator
    wad->id = malloc(5);
    memcpy(wad->id, buffer, 4);
    wad->id[4] = 0;

    wad->number_of_lumps = READ_LE32I(buffer, 4);
    u32 directory_offset = READ_LE32I(buffer, 8);
    // wad->directory_offset = READ_LE32I(buffer, 8);

    wad->lumps = malloc(sizeof(lump_t) * wad->number_of_lumps);
    for (u64 i = 0; i < wad->number_of_lumps; i++) {
        u32 lumps_load_offset = directory_offset + i * 16;
        // u32 lumps_offset = wad->directory_offset + i * 16;
        // wad->lumps[i].offset = READ_LE32I(buffer, lumps_load_offset);
        u32 lump_offset = READ_LE32I(buffer, lumps_load_offset);
        wad->lumps[i].size = READ_LE32I(buffer, lumps_load_offset + 4);  
        wad->lumps[i].name = malloc(9);
        memcpy(wad->lumps[i].name, &buffer[lumps_load_offset + 8], 8);
        wad->lumps[i].name[8] = 0; // NULL Byte terminator

        wad->lumps[i].data = malloc(wad->lumps[i].size);
        memcpy(wad->lumps[i].data, &buffer[lump_offset], wad->lumps[i].size);
    }

    fclose(fp);
    free(buffer);

    return 0;
}

void free_wad(wad_t* wad) {
    if (wad == NULL) {
        return;
    }

    for (u64 i = 0; i < wad->number_of_lumps; i++) {
        free(wad->lumps[i].data);
        free(wad->lumps[i].name);
    }
    
    free(wad->lumps);
    free(wad->id);

    wad->number_of_lumps = 0;
    // wad->directory_offset = 0;
}
