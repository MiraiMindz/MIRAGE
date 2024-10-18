#include "../../engine/engine.h"
#include "../../camera/camera.h"
#include "../../ecglm/matrix.h"
#include "../../emath/emath.h"
#include "../../opengl/mesh.h"
#include "../../opengl/renderer.h"
#include "../../types/types.h"

#include <cglm/cglm.h>
#include <math.h>
#include <stdio.h>

#define FOV (M_PI_3)

static camera_t camera_g;
static mesh_t quad_mesh_g;

void engine_init(wad_t *wad, const str mapname) {
    camera_g = (camera_t){
        .position = {0.f, 0.f, 3.f},
        .yaw = -M_PI_2,
        .pitch = 0.f,
    };

    evec2_t size = get_dimensions();
    printf("size[0] %.2f\n", size.x);
    printf("size[1] %.2f\n", size.y);

    emat4_t projection = eglm_mat4_perspective(FOV, size.x / size.y, .1f, 1000.f);
    set_projection(projection);

    map_t MAP;
    if (wad_read_map(mapname, &MAP, wad) != 0) {
        printf("FAILED TO LOAD MAP FROM wad FILE (E1M1@doom1.wad)\n");
        free_wad(wad);
        // Cleanup: Delete OpenGL context and window
        // SDL_GL_DeleteContext(glContext);
        // SDL_DestroyWindow(window);

        // Quit SDL subsystems
        // SDL_Quit();
        return;
    }

    // the origin (0, 0) is on the middle, so:
    //      +x = right
    //      -x = left
    //      +y = top
    //      -y = bottom
    // our quad will be 1 unit in size
    vertex_t vertices[] = {
        //   X       Y      Z
        {.position = {.5f, .5f, 0.f}},   // top-right
        {.position = {.5f, -.5f, 0.f}},  // bottom-right
        {.position = {-.5f, .5f, 0.f}},  // top-left
        {.position = {-.5f, -.5f, 0.f}}, // bottom-left
    };

    u32 indices[] = {
        0, 1, 3,    // 1st triangle
        1, 2, 3,    // 2nd triangle
    };

    create_mesh(&quad_mesh_g, 4, vertices, 6, indices);

    // unbind only vertex_buffer_object
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void engine_update(f32 delta_time) {
    camera_update_direction_vectors(&camera_g);
    // printf("DELTA_TIME: %.2f\n", delta_time);
    f32 a  = delta_time;
    delta_time  = a;
}

void engine_renderer() {
    emat4_t camera_view = eglm_mat4_look(camera_g.position, eglm_vec3_add(camera_g.position, camera_g.forward), camera_g.up);
    set_view(camera_view);

    // NOTE:
    // https://github.com/Yousaf-Wajih/doom/commit/5927daf16bf3759cb69dffa873e02ced7fb6a1fa
    // FIX: THIS ISN'T WORKING
    draw_mesh(&quad_mesh_g, eglm_mat4_identity(), (vec4){1.f, 1.f, 1.f, 1.f});
}
