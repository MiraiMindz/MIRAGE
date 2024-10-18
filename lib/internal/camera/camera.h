#ifndef _CAMERA_H
#define _CAMERA_H

#include "../types/types.h"
#include "../ecglm/matrix.h"

#include <cglm/types.h>

#define WORLD_UP ((evec3_t){0.f, 1.f, 0.f})

typedef struct camera {
    evec3_t position;
    f32 yaw, pitch;
    //   Forward represents the Z axis.
    //   Right represents the X axis.
    //   Up represents the Y axis.
    evec3_t forward, right, up;
} camera_t;

void camera_update_direction_vectors(camera_t *camera);

#endif
