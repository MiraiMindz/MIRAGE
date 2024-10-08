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

#include "../types/types.h"

// This function initializes the OpenGL Context
SDL_GLContext initialize_opengl(SDL_Window* window);

// This function initializes the OpenGL Renderer
void init_renderer(u16 width, u16 height);

// This function clears the OpenGL Renderer
void clear_renderer();

// This function draws an arbitrary point into the screen given it's coordinates
// and color
void draw_point(vec2 point, f32 size, vec4 color);

// This function draws an arbitrary line into the screen given it's coordinates
// width and color
void draw_line(vec2 start, vec2 end, f32 width, vec4 color);

// This function draws an arbitrary quad into the screen given it's coordinates
// size and color
void draw_quad(vec2 center, vec2 size,f32 angle, vec4 color);

#endif
