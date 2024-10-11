#ifndef _CAMERA_H
#define _CAMERA_H

#include "../types/types.h"

#include <cglm/types.h>

#define WORLD_UP ((vec3){0.f, 1.f, 0.f})

typedef struct camera {
    vec3 position;
    f32 yaw, pitch;
    //   Z        X     Y
    vec3 forward, right, up;
} camera_t;

void camera_update_direction_vectors(camera_t *camera);

#endif
