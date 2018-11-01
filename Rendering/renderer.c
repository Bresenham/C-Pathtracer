//
// Created by Standardbenutzer on 31.03.2018.
//

#include <stdint.h>
#include <stdio.h>
#include "renderer.h"
#include "image.h"
#include "Structs/Sphere.h"
#include "Structs/camera.h"

/*
sphere1 = Sphere(Point3D(0.0,-0.57,3.0),.75,Color(0,0,255),Material.Diffuse,False)
sphere4 = Sphere(Point3D(0.0,8.0,3.0),6,Color(255,255,255),Material.Diffuse,False)
sphere5 = Sphere(Point3D(0.0,-8.0,3.0),6,Color(255,255,255),Material.Diffuse,False)
sphere6 = Sphere(Point3D(0.0,1.5,3.0),0.75,Color(255, 255, 255),Material.Glossy,False)
sphere7 = Sphere(Point3D(0.0,0.48,3.0),0.33,Color(255,255,255),Material.Diffuse,False)
sphere8 = Sphere(Point3D(0.0,0.0,-8.5),8,Color(255,255,255),Material.Diffuse,False)
*/

struct Sphere spheres[] = {
        { .center = {.x = 0.0f, .y = -0.0f, .z = 3.0f}, .color = {.r = 255, .g = 255, .b = 255}, .radius = 4.0f, .isEmitter = true },
        { .center = {.x = 0.0f, .y = 8.0f, .z = 3.0f}, .color = {.r = 255, .g = 255, .b = 255}, .radius = 4.0f, .isEmitter = false },
        { .center = {.x = 0.0f, .y = -8.0f, .z = 3.0f}, .color = {.r = 255, .g = 255, .b = 255}, .radius = 4.0f, .isEmitter = false }
};

int buffer[W * H * 3];

const struct camera c = {.pos = {.x = 0.0, .y = .25f, .z = 50.25}};

void render() {
    int samples = 1;
    while (samples < SAMPLES) {
        int i = 0;
        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                const struct Ray r = generateRay(c, x, y, W, H, samples);
                const struct RGB color = trace(r, 0);
                buffer[i * 3 + 0] += color.r;
                buffer[i * 3 + 1] += color.g;
                buffer[i * 3 + 2] += color.b;
                //printf("Pixel [%3d,%3d] has color [%3d,%3d,%3d]\r\n", x, y, color.r, color.g, color.b);
                i++;
            }
        }
        samples++;
    }
    drawbmp("test.bmp",W,H,buffer,samples);
    //save_bitmap("test.bmp", W, H, 128, buffer, samples);
    /*
    int height = H;
    int width = (int)(1.47 * H);
    int buffer[width * height * 3 + 1];
    int i = 0;
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            buffer[i * 3 + 0] = (int)((float)y/height*255);
            buffer[i * 3 + 1] = (int)((float)x/width*255);
            buffer[i * 3 + 2] = (int)(((float)x+y)/(height + width)*255);
            i++;
        }
    }
    save_bitmap("test2.bmp", width, height, 96, buffer, 1);
     */
}

struct RGB trace(const struct Ray ry, int tdepth) {
    if(tdepth == TRACEDEPTH) return (struct RGB){.r = 0, .g = 0, .b = 0};

    float hitDistance  = 1e20f;
    struct Sphere hitObject = {};
    for(int i = 0; i < (sizeof(spheres) / sizeof(spheres[0])); i++) {
        float dist = intersectSphere(spheres[i], ry);
        if(dist != -1.0 && dist < hitDistance) {
            hitDistance = dist;
            hitObject = spheres[i];
        }
    }

    if(hitDistance == 1e20f) return (struct RGB){.r = 0, .g = 0, .b = 0};
    if(hitObject.isEmitter) return hitObject.color;

    const struct Point hitPoint = add(ry.origin, mult(ry.dir, hitDistance * 0.998));
    const struct Point nrml = sphereNormal(hitObject, hitPoint);
    struct Point rnd = diffuse();

    /* Wrong hemisphere */
    /*
    if(dot(rnd, nrml) < 0.0)
        rnd = mult(rnd, -1.0);
    */
    const struct Ray reflectionRay = (struct Ray){ .origin = hitPoint, .dir = norm(rnd) };

    struct RGB returnColor = trace(reflectionRay, tdepth + 1);
    int r = hitObject.color.r * returnColor.r;
    int g = hitObject.color.g * returnColor.g;
    int b = hitObject.color.b * returnColor.b;

    r /= 255.0f;
    g /= 255.0f;
    b /= 255.0f;

    return (struct RGB){ .r = r, .g = g, .b = b};
}