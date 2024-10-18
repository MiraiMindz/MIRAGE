/******************************************************************************
 * This is the start of the MIRAGE Game Engine, the idea is to create a RayCast
 * basic engine to make DOOM/Wolfeinstain3D like games.
 *****************************************************************************/

#include "../lib/external/GLAD/glad.h"
#include "../lib/internal/emath/emath.h"
#include "../lib/internal/engine/engine.h"
#include "../lib/internal/files/wad/wad.h"
#include "../lib/internal/map/map.h"
#include "../lib/internal/opengl/colors.h"
#include "../lib/internal/opengl/renderer.h"
#include "../lib/internal/sdl/input.h"
#include "../lib/internal/sdl/window.h"
#include "../lib/internal/types/types.h"

#include <SDL2/SDL.h>
#include <cglm/types.h>
#include <cglm/util.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 675
#define OUTPUT_X_OFFSET 20.f
#define OUTPUT_Y_OFFSET 20.f

void game_loop(SDL_Window *window, GAME_STATE *game_state) {
    // Main loop
    // float angle = 0.f;
    Uint32 lastTime = SDL_GetTicks();
    while (*game_state != GAME_STATE_EXIT &&
           *game_state == GAME_STATE_RUNNING) {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                *game_state = GAME_STATE_EXIT;
            }

            handle_keyboard_input(&event, game_state);
        }

        // draw_2d_map_view(map);

        // Swap the buffers to display the blue screen
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime =
            (currentTime - lastTime) / 1000.0f; // Convert milliseconds to
                                                // seconds Calculate frame rate
        // float frameRate = 1.0f / deltaTime;

        // Update your game logic here using deltaTime

        // Optionally print or display the frame rate
        // printf("Frame Rate: %.2f FPS\n", frameRate);

        engine_update(deltaTime);

        lastTime = currentTime;

        // Clear the screen with the blue color
        clear_renderer();
        engine_renderer();

        SDL_GL_SwapWindow(window);
        SDL_Delay(16); // Delay to limit the loop to ~60 FPS
                       // angle += .5f;
    }
}

int main() {
    // Create an SDL window
    SDL_Window *window = initialize_window(
        "MIRAGE Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

    SDL_GLContext glContext = initialize_opengl(window);

    GAME_STATE game_state = GAME_STATE_RUNNING;
    init_renderer(WINDOW_WIDTH, WINDOW_HEIGHT);

    wad_t WAD;
    if (load_wad_from_file("data/files/wad/doom1.wad", &WAD) != 0) {
        printf("FAILED TO LOAD WAD FILE (doom1.wad)\n");
        free_wad(&WAD);
        // Cleanup: Delete OpenGL context and window
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);

        // Quit SDL subsystems
        SDL_Quit();
        return 2;
    }

    engine_init(&WAD, "E1M1");
    game_loop(window, &game_state);

    free_wad(&WAD);
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
