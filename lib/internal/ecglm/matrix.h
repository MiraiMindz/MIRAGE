/*******************************************************************************
 * This internal C header file is part of the MIRAGE Game Engine and distributed
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

#ifndef ECGLM_MATRIX_H
#define ECGLM_MATRIX_H

#include <cglm/types.h>
#include "../types/types.h"

// This function receives a CGLM mat4 (float[4][4]) and return a mat4f (float[16])
void eglm_mat4_flatten(mat4 in_matrix, mat4f out_array);

#endif
