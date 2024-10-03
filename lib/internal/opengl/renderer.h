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
SDL_GLContext initialize_opengl(SDL_Window* window);

#endif
