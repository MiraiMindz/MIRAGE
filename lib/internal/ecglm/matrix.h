/*******************************************************************************
 * This internal C header file is part of the MIRAGE Game Engine and distributed
 * under the MIT License, any question or modification regarding this file
 * should be done on the official comunication channels, mainly on github.com.
 *
 * This file is concerned about the matrices logic of the game engine that are
 * not covered by CGLM, like:
 *  - flattening
 *  - union types
 *  - others
 * please be aware of the constant change of this engine internals as it's
 * always evolving to be more error-prone and easy to use, so expect to have big
 * changes between releases.
 *                                                  - The MIRAGE Developer Team
 *******************************************************************************/

#ifndef ECGLM_MATRIX_H
#define ECGLM_MATRIX_H

#include "../types/types.h"
#include <cglm/types.h>

typedef float mat4f[16];
typedef float mat4x2f[8];
typedef float mat4x3f[12];
typedef float mat3f[9];
typedef float mat3x2f[6];
typedef float mat3x4f[12];
typedef float mat2f[4];
typedef float mat2x3f[6];
typedef float mat2x4f[8];

typedef union eivec2 {
    struct {
        int x, y;
    };
    ivec2 array;
} eivec2_t;

typedef union eivec3 {
    struct {
        int x, y, z;
    };
    struct {
        int r, g, b;
    };
    ivec3 array;
} eivec3_t;

typedef union eivec4 {
    struct {
        int x, y, z, w;
    };
    struct {
        int r, g, b, a;
    };
    ivec4 array;
} eivec4_t;

typedef union evec2 {
    struct {
        float x, y;
    };
    vec2 array;
} evec2_t;

typedef union evec3 {
    struct {
        float x, y, z;
    };
    struct {
        int r, g, b;
    };
    vec3 array;
} evec3_t;

typedef union evec4 {
    struct {
        float x, y, z, w;
    };
    struct {
        int r, g, b, a;
    };
    vec4 array;
} evec4_t;

typedef union eversor {
    struct {
        float x, y, z, w;
    };
    struct {
        int r, g, b, a;
    };
    versor array;
} eversor_t;

typedef union emat3 {
    struct {
        vec3 col1, col2, col3;
    };
    struct {
        vec3 row1, row2, row3;
    };
    mat3 matrix;
    struct {
        float a1, a2, a3;
        float b1, b2, b3;
        float c1, c2, c3;
    };
    mat3f flat; // 3x3 matrix in a flat array
} emat3_t;

typedef union emat3x2 {
    struct {
        vec2 row1, row2, row3;
    };
    struct {
        vec3 col1, col2;
    };
    mat3x2 matrix;
    struct {
        float a1, a2;
        float b1, b2;
        float c1, c2;
    };
    mat3x2f flat; // 3x2 matrix in a flat array
} emat3x2_t;

typedef union emat3x4 {
    struct {
        vec4 row1, row2, row3, row4;
    };
    struct {
        vec3 col1, col2, col3;
    };
    mat3x4 matrix;
    struct {
        float a1, a2, a3, a4;
        float b1, b2, b3, b4;
        float c1, c2, c3, c4;
    };
    mat3x4f flat; // 3x4 matrix in a flat array
} emat3x4_t;

typedef union emat2 {
    struct {
        vec2 row1, row2;
    };
    struct {
        vec2 col1, col2;
    };
    mat2 matrix;
    struct {
        float a1, a2;
        float b1, b2;
    };
    mat2f flat; // 2x2 matrix in a flat array
} emat2_t;

typedef union emat2x3 {
    struct {
        vec3 row1, row2;
    };
    struct {
        vec2 col1, col2, col3;
    };
    mat2x3 matrix;
    struct {
        float a1, a2, a3;
        float b1, b2, b3;
    };
    mat2x3f flat; // 2x3 matrix in a flat array
} emat2x3_t;

typedef union emat2x4 {
    struct {
        vec4 row1, row2;
    };
    struct {
        vec2 col1, col2, col3, col4;
    };
    mat2x4 matrix;
    struct {
        float a1, a2, a3, a4;
        float b1, b2, b3, b4;
    };
    mat2x4f flat; // 2x4 matrix in a flat array
} emat2x4_t;

typedef union emat4 {
    struct {
        vec4 col1, col2, col3, col4;
    };
    struct {
        vec4 row1, row2, row3, row4;
    };
    mat4 matrix;
    struct {
        float a1, a2, a3, a4;
        float b1, b2, b3, b4;
        float c1, c2, c3, c4;
        float d1, d2, d3, d4;
    };
    mat4f flat; // 4x4 matrix in a flat array
} emat4_t;

typedef union emat4x2 {
    struct {
        vec2 row1, row2, row3, row4;
    };
    struct {
        vec4 col1, col2;
    };
    mat4x2 matrix;
    struct {
        float a1, a2;
        float b1, b2;
        float c1, c2;
        float d1, d2;
    };
    mat4x2f flat; // 4x2 matrix in a flat array
} emat4x2_t;

typedef union emat4x3 {
    struct {
        vec4 col1, col2, col3;
    };
    struct {
        vec3 row1, row2, row3, row4;
    };
    mat4x3 matrix;
    struct {
        float a1, a2, a3;
        float b1, b2, b3;
        float c1, c2, c3;
        float d1, d2, d3;
    };
    mat4x3f flat; // 4x3 matrix in a flat array
} emat4x3_t;

// This function receives a CGLM mat4 (float[4][4]) and return a mat4f
// (float[16])
void eglm_mat4_flatten(mat4 in_matrix, mat4f out_array);
evec3_t eglm_vec3_crossn(evec3_t a, evec3_t b);
evec3_t eglm_vec3_zero();
emat4_t eglm_mat4_look(evec3_t eye, evec3_t dir, evec3_t up);
evec3_t eglm_vec3_add(evec3_t a, evec3_t b);
emat4_t eglm_mat4_identity();
emat4_t eglm_mat4_perspective(float fovy, float aspect, float nearZ, float farZ);

#endif
