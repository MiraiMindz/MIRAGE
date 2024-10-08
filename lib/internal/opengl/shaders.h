/*******************************************************************************
 * This internal C header file is part of the MIRAGE Game Engine and distributed
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

#ifndef SHADERS_H
#define SHADERS_H

#include "../../external/GLAD/glad.h"
#include "../types/types.h"

GLuint compile_shaders(GLenum type, const char* source);
GLuint link_program(usize num_shader, ...);

#endif
