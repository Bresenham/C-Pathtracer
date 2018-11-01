//
// Created by Standardbenutzer on 31.03.2018.
//

#include <math.h>
#include <stdio.h>
#include "camera.h"
#include "Ray.h"
#include "Point.h"
#include "halton.h"

struct Ray generateRay(const struct camera c, int x, int y, int w, int h, int samples) {

    const float fov = 160.0f * (float)M_PI / 180.0f;
    const float zdir = 1.0f / tanf(fov);

    const float aspect = (float)h / (float)w;

    const float jitterX = (halton(2, samples)) - 0.5f;
    const float jitterY = (halton(3, samples)) - 0.5f;

    const float xH = x + jitterX;
    const float yH = y + jitterY;

    const float xdir = (xH / (float)w) * 2.0f - 1.0f;
    const float ydir = ((yH/ (float)h) * 2.0f - 1.0f) * aspect;

    const struct Point dir = norm((struct Point){.x = xdir, .y = ydir, .z = zdir});

    return (struct Ray){.origin = c.pos, .dir = dir};

}