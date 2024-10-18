#include "../../camera/camera.h"
#include "../../ecglm/matrix.h"

#include <cglm/cglm.h>
#include <math.h>

void camera_update_direction_vectors(camera_t *camera) {
    camera->forward = (evec3_t){
        cosf(camera->yaw) * cosf(camera->pitch),
        sinf(camera->pitch),
        sinf(camera->yaw) * cosf(camera->pitch),
    };

    camera->right = eglm_vec3_crossn(camera->forward, WORLD_UP);
    camera->up = eglm_vec3_crossn(camera->right, camera->forward);
}
