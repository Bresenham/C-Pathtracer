//
// Created by Standardbenutzer on 31.03.2018.
//

#ifndef PATHTRACER_POINT_H
#define PATHTRACER_POINT_H

#include <stdbool.h>

typedef struct Point {
    float x,y,z;
} Point;

bool cmpPoint(struct Point p1, struct Point p2);
float dot(struct Point p1, struct Point p2);
float length(struct Point p);

struct Point sub(struct Point p1, struct Point p2);
struct Point add(struct Point p1, struct Point p2);
struct Point mult(struct Point p, float mul);
struct Point norm(struct Point p);

struct Point diffuse();
#endif //PATHTRACER_POINT_H
