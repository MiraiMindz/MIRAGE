/*******************************************************************************
 * This internal C header file is part of the MIRAGE Game Engine and distributed
 * under the MIT License, any question or modification regarding this file
 * should be done on the official comunication channels, mainly on github.com.
 *
 * This file is concerned about the main input logic of the game engine, like:
 *  - Keyboard
 *  - Mouse
 *  - Joysticks
 *  - others
 * please be aware of the constant change of this engine internals as it's 
 * always evolving to be more error-prone and easy to use, so expect to have big
 * changes between releases.
 *                                                  - The MIRAGE Developer Team
*******************************************************************************/
#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include "../types/types.h"

void handle_keyboard_input(SDL_Event *event, GAME_STATE *game_state);

#endif
