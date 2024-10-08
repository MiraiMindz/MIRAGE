/*******************************************************************************
 * This internal C source file is part of the MIRAGE Game Engine and distributed
 * under the MIT License, any question or modification regarding this file
 * should be done on the official comunication channels, mainly on github.com.
 *
 * This file is concerned about the main shaders logic of the game engine, like:
 *  - Loading fragments
 *  - linking
 *  - compiling
 *  - others
 * please be aware of the constant change of this engine internals as it's 
 * always evolving to be more error-prone and easy to use, so expect to have big
 * changes between releases.
 *                                                  - The MIRAGE Developer Team
*******************************************************************************/

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>

#include "../../../types/types.h"
#include "../../../opengl/shaders.h"

GLuint compile_shaders(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infolog[512];
        glGetShaderInfoLog(shader, sizeof(infolog), NULL, infolog);
        fprintf(stderr, "FAILED TO COMPILE SHADER:\n%s\n", infolog);
    }

    return shader;
}

GLuint link_program(usize num_shader, ...) {
    GLuint program = glCreateProgram();
    
    va_list vector_array;
    va_start(vector_array, num_shader);
    for (usize i = 0; i < num_shader; i++) {
        glAttachShader(program, va_arg(vector_array, GLuint));
    }
    va_end(vector_array);

    glLinkProgram(program);

    GLint success;
    glGetShaderiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infolog[512];
        glGetShaderInfoLog(program, sizeof(infolog), NULL, infolog);
        fprintf(stderr, "FAILED TO LINK PROGRAM:\n%s\n", infolog);
    }


    return program;
}
