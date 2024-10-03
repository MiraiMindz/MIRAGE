/******************************************************************************
 * This is the start of the MIRAGE Game Engine, the idea is to create a RayCast
 * basic engine to make DOOM/Wolfeinstain3D like games.
 *****************************************************************************/

#include "../lib/external/GLAD/glad.h"
#include "../lib/internal/types/types.h"
#include "../lib/internal/sdl/input.h"
#include "../lib/internal/sdl/window.h"
#include "../lib/internal/opengl/renderer.h"

#include <SDL2/SDL.h>

void game_loop(SDL_Window *window, GAME_STATE* game_state) {
    // Set the clear color to blue (R, G, B, A)
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);  // Blue color

    // Main loop
    while (*game_state != GAME_STATE_EXIT && *game_state == GAME_STATE_RUNNING) {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                *game_state = GAME_STATE_EXIT;
            }

            handle_keyboard_input(&event, game_state);
        }

        // Clear the screen with the blue color
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the buffers to display the blue screen
        SDL_GL_SwapWindow(window);
        SDL_Delay(16);  // Delay to limit the loop to ~60 FPS
    }
}

int main() {
    // Create an SDL window
    SDL_Window *window = initialize_window("MIRAGE Game Engine",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_OPENGL);

    SDL_GLContext glContext = initialize_opengl(window);
    
    GAME_STATE game_state = GAME_STATE_RUNNING;
    game_loop(window, &game_state);

    // Cleanup: Delete OpenGL context and window
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    
    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
