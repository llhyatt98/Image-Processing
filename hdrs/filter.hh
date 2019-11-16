#ifndef FILTER_H
#define FILTER_H

#include "IO.hh"

void create_blank_image(char* name, int width, int height, int r = 255, int g = 255, int b = 255);
pixel **create_blank_array(int width, int height, int r = 255, int g = 255, int b = 255);
int pix_range(int p);
int pix_range_input(int p, int num);
// void black_to_image(char *filename, char *filename_2, char *name);
void greyscale_filter(char* filename, char *name);
void black_white_filter(char* filename, char *name);
void RGB_filter(char *filename, char *name);
void inverted_filter(char *filename, char *name);
void enhance_filter(char *filename, char *name);
void antique_filter(char *filename, char *name);
void blood_filter(char *filename, char *name);
void blur_filter(char *filename, char *name, int blur);
void duck_filter(char *filename, char *name);
void double_vision_filter(char* filename, char *name, const char *orientation);
void popart_filter(char *filename, char *name);
void thermal_filter(char* filename, char *name);
void checkers_filter(char* filename, char *name, int box, int type);
void static_filter(char *filename, char *name);
void fast_filter(char *filename, char *name, int type);

#endif //Guards against including more than once. 


