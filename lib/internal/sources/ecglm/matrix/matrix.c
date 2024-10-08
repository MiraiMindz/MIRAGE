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

#include <cglm/types.h>

#include "../../../ecglm/matrix.h"
#include "../../../types/types.h"

void eglm_mat4_flatten(mat4 in_matrix, mat4f out_array) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            out_array[i * 4 + j] = in_matrix[i][j];
        }
    }
}
