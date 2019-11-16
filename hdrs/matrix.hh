#ifndef MATRIX_H
#define MATRIX_H

#include "IO.hh"

void resize_filter(char *filename, char *name, float factor);
pixel **image_transpose(int width, int height, pixel **matrix);
void mirror_h_filter(char *filename, char *name);
void mirror_v_filter(char *filename, char *name);
void flip_h_filter(char *filename, char *name);
void flip_v_filter(char *filename, char *name);
void shuffle_filter(char *filename, char *name);
void pixelate_filter(char *filename, char *name, int p);
pixel unique_pixel(pixel **arr, int width, int height);
int rotate_i(int i_val, int j_val, int list_width, int list_height, int deg);
int rotate_j(int i_val, int j_val, int list_width, int list_height, int deg);
void kaleidoscope(char *filename, char *name);

#endif //Guards against including more than once. 