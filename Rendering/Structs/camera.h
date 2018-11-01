//
// Created by Standardbenutzer on 31.03.2018.
//

#ifndef PATHTRACER_CAMERA_H
#define PATHTRACER_CAMERA_H

#include "Point.h"

typedef struct camera {
    struct Point pos;
} camera;

struct Ray generateRay(struct camera c, int x, int y, int w, int h, int samples);

#endif //PATHTRACER_CAMERA_H
