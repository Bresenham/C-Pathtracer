//
// Created by Standardbenutzer on 31.03.2018.
//

#ifndef PATHTRACER_SPHERE_H
#define PATHTRACER_SPHERE_H

#include <stdbool.h>
#include "RGB.h"
#include "Point.h"
#include "Ray.h"

typedef struct Sphere {
    struct Point center;
    struct RGB color;
    float radius;
    bool isEmitter;
} Sphere;

float intersectSphere(struct Sphere s, struct Ray r);
struct Point sphereNormal(struct Sphere s, struct Point p);

#endif //PATHTRACER_SPHERE_H
