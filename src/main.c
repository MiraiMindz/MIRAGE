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
#include "../lib/internal/map/map.h"
#include "../lib/internal/emath/emath.h"

#include "cglm/types.h"

#include <SDL2/SDL.h>
#include <cglm/util.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH    1280
#define WINDOW_HEIGHT   720

// void test_wad_loading(wad_t* wad) {
//     printf("LOADED WAD FILE OF TYPE %s with %u lumps\n", wad->id, wad->number_of_lumps);
//     printf("LUMPS:\n");
//     for (u64 i = 0; i < wad->number_of_lumps; i++) {
//         printf("\t%8s:\t%u\n", wad->lumps[i].name, wad->lumps[i].size);
//     }
// }

// void test_map_loading(map_t* map) {
//     for (i64 i = 0 ; i < map->number_of_vertices; i++) {
//         printf("\t\t%g\t%g\n", map->vertices[i][0], map->vertices[i][1]);
//     }
// }


void game_loop(SDL_Window *window, GAME_STATE* game_state, map_t* map) {
    // Main loop
    // float angle = 0.f;
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

        for (isize i = 0; i < map->number_of_vertices; i++) {
            draw_line(map->vertices[map->linedefs[i].start_index], map->vertices[map->linedefs[i].end_index], 2.f, (vec4){RGBA_ANSI_COLOR_WHITE_SYSTEM_A100});
        }

        for (isize i = 0; i < map->number_of_vertices; i++) {
            draw_point(map->vertices[i], 4.f, (vec4){RGBA_ANSI_COLOR_YELLOW_SYSTEM_A100});
        }


        // Swap the buffers to display the blue screen
        SDL_GL_SwapWindow(window);
        SDL_Delay(16);  // Delay to limit the loop to ~60 FPS
        // angle += .5f;
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
        // Cleanup: Delete OpenGL context and window
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        
        // Quit SDL subsystems
        SDL_Quit();
        return 2;
    }

    // test_wad_loading(&WAD);

    map_t MAP;
    if (wad_read_map("E1M2", &MAP, &WAD) != 0) {
        printf("FAILED TO LOAD MAP FROM WAD FILE (E1M1@doom1.wad)\n");
        free_wad(&WAD);
        // Cleanup: Delete OpenGL context and window
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        
        // Quit SDL subsystems
        SDL_Quit();
        return 3;
    }

    
    vec2 output_min = {20.f, 20.f};
    vec2 output_max = {WINDOW_WIDTH - 20.f, WINDOW_HEIGHT - 20.f};
    vec2* remapped_vertices = malloc(sizeof(vec2) * MAP.number_of_vertices);
    for (isize i = 0; i < MAP.number_of_vertices; i++) {
        // Clamp the X coordinate to [MAP.min[0], MAP.max[0]]
        float clamped_x = emath_max_f32(MAP.min[0], emath_min_f32(MAP.vertices[i][0], MAP.max[0]));
        // Map the clamped X coordinate to the screen space
        remapped_vertices[i][0] = (clamped_x - MAP.min[0]) * 
            (output_max[0] - output_min[0]) / (MAP.max[0] - MAP.min[0]) + output_min[0];
        
        // Clamp the Y coordinate to [MAP.min[1], MAP.max[1]]
        float clamped_y = emath_max_f32(MAP.min[1], emath_min_f32(MAP.vertices[i][1], MAP.max[1]));
        // Map the clamped Y coordinate to the screen space
        remapped_vertices[i][1] = WINDOW_HEIGHT - (clamped_y - MAP.min[1]) * 
            (output_max[1] - output_min[1]) / (MAP.max[1] - MAP.min[1]) + output_min[1];
    }


    map_t NEW_MAP;
    NEW_MAP.number_of_vertices = MAP.number_of_vertices;
    NEW_MAP.max[0] = MAP.max[0];
    NEW_MAP.max[1] = MAP.max[1];
    NEW_MAP.min[0] = MAP.min[0];
    NEW_MAP.min[1] = MAP.min[1];
    NEW_MAP.number_of_linedefs = MAP.number_of_linedefs;


    NEW_MAP.vertices = malloc(sizeof(vec2) * NEW_MAP.number_of_vertices);
    for (isize i = 0; i < MAP.number_of_vertices; i++) {
        NEW_MAP.vertices[i][0] = remapped_vertices[i][0];
        NEW_MAP.vertices[i][1] = remapped_vertices[i][1];
    }
    
    NEW_MAP.linedefs = malloc(sizeof(linedef_t) * NEW_MAP.number_of_linedefs);
    for (isize i = 0; i < MAP.number_of_linedefs; i++) {
        NEW_MAP.linedefs[i] = MAP.linedefs[i];
    }

    // test_map_loading(&MAP);
    
    game_loop(window, &game_state, &NEW_MAP);

    free_wad(&WAD);
    free_map(&MAP);
    free_map(&NEW_MAP);
    // Cleanup: Delete OpenGL context and window
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    
    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
