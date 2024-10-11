/*******************************************************************************
 * This internal C source file is part of the MIRAGE Game Engine and distributed
 * under the MIT License, any question or modification regarding this file
 * should be done on the official comunication channels, mainly on github.com.
 *
 * This file is concerned about the main mesh logic of the game engine, like:
 *  - 2D meshes
 *  - 3D meshes
 *  - others
 * please be aware of the constant change of this engine internals as it's
 * always evolving to be more error-prone and easy to use, so expect to have big
 * changes between releases.
 *                                                  - The MIRAGE Developer Team
 ******************************************************************************/

#include "../../../opengl/mesh.h"
#include "../../../types/types.h"

void create_mesh(mesh_t *mesh, isize number_of_vertices, vertex_t *vertices,
                 isize number_of_indices, u32 *indices) {
    mesh->number_of_indices = number_of_indices;

    glGenVertexArrays(1, &mesh->vertex_array_object);
    glGenBuffers(1, &mesh->vertex_buffer_object);
    glGenBuffers(1, &mesh->element_buffer_object);

    glBindVertexArray(mesh->vertex_array_object);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * number_of_vertices,
                 vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->element_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * number_of_indices,
                 indices, GL_STATIC_DRAW);
}
