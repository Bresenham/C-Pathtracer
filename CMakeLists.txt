cmake_minimum_required(VERSION 3.10)
project(Pathtracer C)

set(CMAKE_C_STANDARD 11)

add_executable(Pathtracer main.c Rendering/renderer.c Rendering/renderer.h Rendering/Structs/camera.h Rendering/Structs/Point.c Rendering/Structs/Point.h Rendering/Structs/RGB.c Rendering/Structs/RGB.h Rendering/Structs/Ray.c Rendering/Structs/Ray.h Rendering/Structs/Sphere.c Rendering/Structs/Sphere.h Rendering/Structs/camera.c Rendering/image.c Rendering/image.h Rendering/Structs/halton.c Rendering/Structs/halton.h)