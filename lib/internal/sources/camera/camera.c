#include "../../camera/camera.h"
#include "../../emath/emath.h"
#include "../../types/types.h"

#include <cglm/cglm.h>
#include <math.h>
#include <stdio.h>

void camera_update_direction_vectors(camera_t *camera) {
    camera->forward[0] = cosf(camera->yaw) * cosf(camera->pitch);
    camera->forward[1] = sinf(camera->pitch);
    camera->forward[2] = sinf(camera->yaw) * cosf(camera->pitch);
    
    // printf("camera->forward[0] %2.f\n", camera->forward[0]);
    // printf("camera->forward[1] %2.f\n", camera->forward[1]);
    // printf("camera->forward[2] %2.f\n", camera->forward[2]);

    vec3 crossnres;
    glm_vec3_crossn(camera->forward, WORLD_UP, crossnres);
    glm_vec3_copy(crossnres, camera->right);
    glm_vec3_zero(crossnres);
    glm_vec3_crossn(camera->right, camera->forward, crossnres);
    glm_vec3_copy(crossnres, camera->up);
}
