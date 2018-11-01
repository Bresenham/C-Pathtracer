//
// Created by Standardbenutzer on 31.03.2018.
//

#ifndef PATHTRACER_IMAGE_H
#define PATHTRACER_IMAGE_H

void save_bitmap(const char *file_name, unsigned int width, unsigned int height, unsigned int dpi, const int *buffer,
                 int samples);
void drawbmp (char * filename, int WIDTH, int HEIGHT, int *buffer, int samples);
#endif //PATHTRACER_IMAGE_H
