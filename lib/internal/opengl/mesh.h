/*******************************************************************************
 * This internal C header file is part of the MIRAGE Game Engine and distributed
 * under the MIT License, any question or modification regarding this file
 * should be done on the official comunication channels, mainly on github.com.
 *
 * This file is concerned about the main mesh logic of the game engine, like:
 *  - 2D meshes
 *  - 3D meshes
 *  - other
 * please be aware of the constant change of this engine internals as it's
 * always evolving to be more error-prone and easy to use, so expect to have big
 * changes between releases.
 *                                                  - The MIRAGE Developer Team
 ******************************************************************************/

#ifndef MESH_H
#define MESH_H

#include "../../external/GLAD/glad.h"
#include "../types/types.h"

#include <cglm/types.h>

typedef struct mesh {
    GLuint vertex_array_object, vertex_buffer_object, element_buffer_object;
    isize number_of_indices;
} mesh_t;

typedef struct vertex {
    vec3 position;
} vertex_t;

void create_mesh(mesh_t *mesh, isize number_of_vertices, vertex_t *vertices,
                 isize number_of_indices, u32 *indices);

#endif
