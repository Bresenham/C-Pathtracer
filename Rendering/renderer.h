//
// Created by Standardbenutzer on 31.03.2018.
//

#ifndef PATHTRACER_RENDERER_H
#define PATHTRACER_RENDERER_H

#include "Structs/Ray.h"

#define W 256
#define H 256
#define TRACEDEPTH  3
#define SAMPLES 100

void render();
struct RGB trace(struct Ray ry, int tdepth);

#endif //PATHTRACER_RENDERER_H
