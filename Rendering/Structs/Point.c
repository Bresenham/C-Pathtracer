//
// Created by Standardbenutzer on 31.03.2018.
//

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "Point.h"
#include "Ray.h"

struct Point add(const struct Point p1, const struct Point p2) {
    struct Point ret;
    ret.x = (p1.x + p2.x);
    ret.y = (p1.y + p2.y);
    ret.z = (p1.z + p2.z);
    return ret;
};

struct Point sub(const struct Point p1, const struct Point p2) {
    struct Point ret;
    ret.x = (p1.x - p2.x);
    ret.y = (p1.y - p2.y);
    ret.z = (p1.z - p2.z);
    return ret;
};

struct Point mult(const struct Point p, float mul) {
    struct Point ret;
    ret.x = p.x * mul;
    ret.y = p.y * mul;
    ret.z = p.z * mul;
    return ret;
}

float length(const struct Point p) {
    return sqrtf(p.x*p.x + p.y*p.y + p.z*p.z);
}

struct Point norm(const struct Point p) {
    struct Point ret;
    const float len = length(p);
    ret.x = p.x / len;
    ret.y = p.y / len;
    ret.z = p.z / len;
    return ret;
}

struct Point diffuse() {
    float u1 = (float)rand() / (float)RAND_MAX;
    float u2 = (float)rand() / (float)RAND_MAX;
    float z = 1.0f - 2.0f * u1;
    float r = sqrtf(fmaxf(0.0, 1.0f - z * z));
    float phi = 2.0f * (float)M_PI * u2;
    float x = r * cosf(phi);
    float y = r * sinf(phi);
    return norm((struct Point) {.x = x, .y = y, .z = z});
}

float dot(const struct Point p1, const struct Point p2) {
    return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
};

bool cmpPoint(const struct Point p1, const struct Point p2) {
    return p1.x == p2.x && p1.y == p2.y && p1.z == p2.z;
};