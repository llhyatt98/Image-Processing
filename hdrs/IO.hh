#ifndef IO_H
#define IO_H

//Pixel Struct 
struct pixel{
    int r; // red pixel
    int g; // green pixel 
    int b; // blue pixel
};

char *to_txt(char *name);
char *to_pbm(char *name);
// void remove_file(char *filename);
pixel **read_exported_PBM(char* filename);
pixel **readBMP(char* filename);
int check_if_BMP(char *name);
int check_if_PBM(char *name);
int get_PBM_width(char *filename);
int get_PBM_height(char *filename);
int get_BMP_width(char* filename);
int get_BMP_height(char* filename);
void write_PBM_image(char* filename, char *name);
void print_pixel_array(char *name, int width, int height, pixel **matrix);
void b_test(char *filename, char *name, int width, int height);
void free_matrix(int height, pixel **matrix);

#endif //Guards against including more than once. 