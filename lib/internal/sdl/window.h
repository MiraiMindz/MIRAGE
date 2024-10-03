/*******************************************************************************
 * This internal C header file is part of the MIRAGE Game Engine and distributed
 * under the MIT License, any question or modification regarding this file
 * should be done on the official comunication channels, mainly on github.com.
 *
 * This file is concerned about the main window logic of the game engine, like:
 *  - Creation
 *  - Manipulation
 *  - Contexts
 *  - others
 * please be aware of the constant change of this engine internals as it's 
 * always evolving to be more error-prone and easy to use, so expect to have big
 * changes between releases.
 *                                                  - The MIRAGE Developer Team
*******************************************************************************/

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

SDL_Window* initialize_window(const char* title, int window_x_position,
                              int window_y_position, int window_width,
                              int window_height, int window_flags);

#endif
