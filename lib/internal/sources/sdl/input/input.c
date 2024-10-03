/*******************************************************************************
 * This internal C source file is part of the MIRAGE Game Engine and distributed
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

#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include "../../../types/types.h"

// Function to handle keyboard input
void handle_keyboard_input(SDL_Event *event, GAME_STATE *game_state) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_ESCAPE:  // If the escape key is pressed
                printf("Escape key pressed. Exiting...\n");
                // Here you can send a quit event or set a flag to exit
                *game_state = GAME_STATE_EXIT;
                break;

            case SDLK_UP:     // Handle up arrow key
            case SDLK_w:      // Handle W key
                printf("Up key pressed.\n");
                break;

            case SDLK_DOWN:   // Handle down arrow key
            case SDLK_s:      // Handle S key
                printf("Down key pressed.\n");
                break;

            case SDLK_LEFT:   // Handle left arrow key
            case SDLK_a:      // Handle A key
                printf("Left key pressed.\n");
                break;

            case SDLK_RIGHT:  // Handle right arrow key
            case SDLK_d:      // Handle D key
                printf("Right key pressed.\n");
                break;

            // Add more cases for other keys as needed
            default:
                break;
        }
    }
}
