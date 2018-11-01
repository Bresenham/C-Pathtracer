//
// Created by Standardbenutzer on 31.03.2018.
//

#include <math.h>
#include <stdlib.h>
#include "Sphere.h"
#include "Point.h"
#include "Ray.h"
#include "RGB.h"

float intersectSphere(const struct Sphere s, const struct Ray r) {
    const struct Point v = sub(r.origin, s.center);
    const float a = dot(r.dir,r.dir);
    const float b = 2.0f * dot(r.dir,v);
    const float c = dot(v,v) - s.radius * s.radius;
    const float discr = (b * b) - (4.0f * a * c);
    if(discr > 0) {
        const float x1 = (-b - sqrtf(discr)) / (2.0f * a);
        const float x2 = (-b + sqrtf(discr)) / (2.0f * a);
        return fminf(x1,x2);
    }
    return -1.0f;
};

struct Point sphereNormal(const struct Sphere s, const struct Point p){
    return norm(sub(p, s.center));
}