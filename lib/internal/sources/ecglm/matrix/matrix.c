/*******************************************************************************
 * This internal C source file is part of the MIRAGE Game Engine and distributed
 * under the MIT License, any question or modification regarding this file
 * should be done on the official comunication channels, mainly on github.com.
 *
 * This file is concerned about the matrices logic of the game engine that are
 * not covered by CGLM, like:
 *  - flattening
 *  - others
 * please be aware of the constant change of this engine internals as it's 
 * always evolving to be more error-prone and easy to use, so expect to have big
 * changes between releases.
 *                                                  - The MIRAGE Developer Team
*******************************************************************************/

#include <cglm/cglm.h>
#include <cglm/mat4.h>

#include "../../../ecglm/matrix.h"
#include "../../../types/types.h"

// This function receives a CGLM mat4 (float[4][4]) and return a mat4f (float[16])
void eglm_mat4_flatten(mat4 in_matrix, mat4f out_array) {
    // This is the same as a double for-loop.
    for (int idx = 0; idx < 16; idx++) {
        out_array[idx] = in_matrix[idx / 4][idx % 4];
    }
}

evec3_t eglm_vec3_crossn(evec3_t a, evec3_t b) {
    evec3_t result;
    glm_vec3_crossn(a.array, b.array, result.array);
    return result;
}

evec3_t eglm_vec3_zero() {
    return (evec3_t){0.f, 0.f, 0.f};
}

emat4_t eglm_mat4_look(evec3_t eye, evec3_t dir, evec3_t up) {
    emat4_t result;
    glm_look(eye.array, dir.array, up.array, result.matrix);
    return result;
}
evec3_t eglm_vec3_add(evec3_t a, evec3_t b) {
    evec3_t result;
    glm_vec3_add(a.array, b.array, result.array);
    return result;
}

emat4_t eglm_mat4_identity() {
    emat4_t result;
    glm_mat4_zero(result.matrix);
    glm_mat4_identity(result.matrix);
    return result;
}

emat4_t eglm_mat4_perspective(float fovy, float aspect, float nearZ, float farZ) {
    emat4_t result;
    glm_perspective(fovy, aspect, nearZ, farZ, result.matrix);
    return result;
}
