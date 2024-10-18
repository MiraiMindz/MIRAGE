/*******************************************************************************
 * This internal C header file is part of the MIRAGE Game Engine and distributed
 * under the MIT License, any question or modification regarding this file
 * should be done on the official comunication channels, mainly on github.com.
 *
 * This file is concerned about the main render logic of the game engine, like:
 *  - Drawing
 *  - Transformation
 *  - Shaders
 *  - others
 * please be aware of the constant change of this engine internals as it's
 * always evolving to be more error-prone and easy to use, so expect to have big
 * changes between releases.
 *                                                  - The MIRAGE Developer Team
 *******************************************************************************/

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <cglm/types.h>

#include "../opengl/mesh.h"
#include "../types/types.h"
#include "../ecglm/matrix.h"

// This function initializes the OpenGL Context
SDL_GLContext initialize_opengl(SDL_Window *window);

// This function initializes the OpenGL Renderer
void init_renderer(u16 width, u16 height);

// This function clears the OpenGL Renderer
void clear_renderer();

// Allows the program to set the view matrix
void set_view(emat4_t view);

// Allows the program to set the projection matrix
void set_projection(emat4_t projection);

// This function draws an arbitrary mesh into the screen given it's
// transformation and color
void draw_mesh(const mesh_t *mesh, emat4_t transformation, evec4_t color);

// This function draws an arbitrary point into the screen given it's coordinates
// and color
void draw_point(evec2_t point, f32 size, evec4_t color);

// This function draws an arbitrary line into the screen given it's coordinates
// width and color
void draw_line(evec2_t start, evec2_t end, f32 width, evec4_t color);

// This function draws an arbitrary quad into the screen given it's coordinates
// size and color
void draw_quad(evec2_t center, evec2_t size, f32 angle, evec4_t color);

f32 get_width();
f32 get_height();
evec2_t get_dimensions();

#endif
