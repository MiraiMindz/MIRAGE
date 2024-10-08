/******************************************************************************
 * This is the start of the MIRAGE Game Engine, the idea is to create a RayCast
 * basic engine to make DOOM/Wolfeinstain3D like games.
 *****************************************************************************/

#include "../lib/external/GLAD/glad.h"
#include "../lib/internal/types/types.h"
#include "../lib/internal/sdl/input.h"
#include "../lib/internal/sdl/window.h"
#include "../lib/internal/opengl/renderer.h"
#include "../lib/internal/opengl/colors.h"
#include "../lib/internal/files/wad/wad.h"

#include "cglm/types.h"

#include <SDL2/SDL.h>
#include <cglm/util.h>
#include <stdio.h>

#define WINDOW_WIDTH    1280
#define WINDOW_HEIGHT   720

void game_loop(SDL_Window *window, GAME_STATE* game_state) {
    // Main loop
    float angle = 0.f;
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
        clear_renderer();

        draw_line((vec2){0.f, 0.f}, (vec2){WINDOW_WIDTH, WINDOW_HEIGHT}, 5.f, (vec4){RGBA_ANSI_COLOR_RED_SYSTEM_A100});
        draw_line((vec2){WINDOW_WIDTH, 0.f}, (vec2){0.f, WINDOW_HEIGHT}, 5.f, (vec4){RGBA_ANSI_COLOR_RED_SYSTEM_A100});
        draw_point((vec2){WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f}, 64.f, (vec4){RGBA_ANSI_COLOR_WHITE_SYSTEM_A100});
        draw_quad((vec2){WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f}, (vec2){40.f, 40.f}, glm_rad(angle), (vec4){RGBA_ANSI_COLOR_BLACK_SYSTEM_A100});


        // Swap the buffers to display the blue screen
        SDL_GL_SwapWindow(window);
        SDL_Delay(16);  // Delay to limit the loop to ~60 FPS
        angle += .5f;
    }
}

int main() {
    // Create an SDL window
    SDL_Window *window = initialize_window("MIRAGE Game Engine",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_OPENGL);

    SDL_GLContext glContext = initialize_opengl(window);
    
    GAME_STATE game_state = GAME_STATE_RUNNING;
    init_renderer(WINDOW_WIDTH, WINDOW_HEIGHT);

    wad_t WAD;
    if (load_wad_from_file("data/files/wad/doom1.wad", &WAD) != 0) {
        printf("FAILED TO LOAD WAD FILE (doom1.wad)\n");
        free_wad(&WAD);
        return 2;
        // Cleanup: Delete OpenGL context and window
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        
        // Quit SDL subsystems
        SDL_Quit();
    }

    printf("LOADED WAD FILE OF TYPE %s with %u lumps\n", WAD.id, WAD.number_of_lumps);
    printf("LUMPS:\n");
    for (u64 i = 0; i < WAD.number_of_lumps; i++) {
        printf("\t%8s:\t%u\n", WAD.lumps[i].name, WAD.lumps[i].size);
    }
    free_wad(&WAD);
    game_loop(window, &game_state);
    // Cleanup: Delete OpenGL context and window
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    
    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
