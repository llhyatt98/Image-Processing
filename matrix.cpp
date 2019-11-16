#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <map>
#include <math.h>
#include "hdrs/IO.hh"
#include "hdrs/matrix.hh"
#include "hdrs/filter.hh"

using namespace std; 

// Array Altering Functions 
pixel **image_transpose(int width, int height, pixel **matrix){

    pixel **t_matrix = new pixel*[height];
    
    for (int m = 0; m < height; ++m) {
        t_matrix[m] = new pixel[width];
    }
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
                t_matrix[i][j].r = matrix[j][i].r;
                t_matrix[i][j].g = matrix[j][i].g;
                t_matrix[i][j].b = matrix[j][i].b;
        }
    }

    return t_matrix;
}

pixel unique_pixel(pixel **arr, int width, int height){
    
    int sw = 0;

    pixel px;

    for(int a = 255; a > 0; a--){
        for(int b = 255; b > 0; b--){
            for(int c = 255; c > 0; c--){
                sw = 0;
                px.r = a;
                px.g = b;
                px.b = c;
                for(int i = 0; i < height; i++){
                    for(int j = 0; j < width; j++){
                        if(arr[i][j].r == px.r && arr[i][j].g == px.g && arr[i][j].b == px.b){
                            sw = 1;
                        }
                    }
                }

                if(sw == 0){
                    break;
                }
            }
        if(sw == 0){
                break;
            }
        }
    if(sw == 0){
                break;
            }
    }
    return px;
}

void resize_filter(char *filename, char *name, float factor){
    // ---------------------------------------------------------------------------
    // Function: Writes an resized copy of the input .bmp in stored as a .pbm 
    // Arguments: Takes the name of the input image and name of the output image.
    // Returns: Void function that creates a new .pbm file in your directory
    // ---------------------------------------------------------------------------

    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    int w = width * factor;
    int h = height * factor;

    pixel **arr = readBMP(filename); 
    pixel **temp = create_blank_array(w, h, 255, 255, 255);

    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            unsigned char R, G, B;
            R = arr[int(i / factor)][int(j / factor)].r;
            G = arr[int(i / factor)][int(j / factor)].g;
            B = arr[int(i / factor)][int(j / factor)].b;
            temp[i][j].r = R;
            temp[i][j].g = G;
            temp[i][j].b = B;
        }
    }
    print_pixel_array(name, w, h, temp);
    free_matrix(height, arr);
    free_matrix(height, temp);
}

void mirror_h_filter(char *filename, char *name){
    /*

        THIS FUNCTION MIRRORS EACH PICTURE HORIZONTALLY 

    */

    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    pixel **arr = readBMP(filename);

    if(height<0){
        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
        exit(EXIT_FAILURE);
    }


    // Mirrors each pixel to the other side (horizontally) 
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            arr[i][width - j].r = arr[i][j].r;
            arr[i][width - j].g = arr[i][j].g;
            arr[i][width - j].b = arr[i][j].b;

        }
    }

    print_pixel_array(name, width, height, arr);
    free_matrix(height, arr);
    
}

void mirror_v_filter(char *filename, char *name){
    /*

        THIS FUNCTION MIRRORS EACH PICTURE VERTICALLY

    */
    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    pixel **arr = readBMP(filename);

    if(height<0){
        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
        exit(EXIT_FAILURE);
    }

    // Temp height that takes into account the 0 for an array
    // so that you do not get a seg fault
    int h1 = height - 1;

    // Mirrors each pixel to the other side (vertically) 
    for(int i = 0; i < h1 - 1; i++)
    {
        for(int j = 0; j < width; j++)
        {
            arr[h1 - i][j].r = arr[i][j].r;
            arr[h1 - i][j].g = arr[i][j].g;
            arr[h1 - i][j].b = arr[i][j].b;
        }
    }
    // Prints out the RGB data for the new image
    print_pixel_array(name, width, height, arr);
    free_matrix(height, arr);
}

void flip_h_filter(char *filename, char *name){

    /*

        THIS FUNCTION FLIPS EACH PICTURE ACROSS THE VERTICAL AXIS. 

    */

    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    pixel **arr = readBMP(filename);

    if(height<0){
        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < height; i++)
    {
        int temp;
        int count = 0;
        int w = width - 1;

        // Goes until halfway when count and w meet
        while (count < w) 
        { 
            // Swaps the R values
            temp = arr[i][count].r;  
            arr[i][count].r = arr[i][w].r; 
            arr[i][w].r = temp; 

            // Swaps the G values
            temp = arr[i][count].g;  
            arr[i][count].g = arr[i][w].g; 
            arr[i][w].g = temp; 

            // Swaps the B values
            temp = arr[i][count].b;  
            arr[i][count].b = arr[i][w].b; 
            arr[i][w].b = temp; 

            // Update counters
            count = count + 1; 
            w = w - 1; 
        } 

    }

    // Prints to a file
    print_pixel_array(name, width, height, arr);
    free_matrix(height, arr);
}

void flip_v_filter(char *filename, char *name){
    /*

        THIS FUNCTION MIRRORS EACH PICTURE VERTICAL 
    */

    
    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    pixel **arr = readBMP(filename);

    if(height<0){
        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
        exit(EXIT_FAILURE);
    }


    for(int i = 0; i < width; i++)
    {
        int temp;
        int count = 0;
        int h = height - 1;

        // Goes until halfway when count and h meet
        while (count < h) 
        { 

            // Swaps the R values
            temp = arr[count][i].r;  
            arr[count][i].r = arr[h][i].r; 
            arr[h][i].r = temp; 


            // Swaps the G values
            temp = arr[count][i].g;  
            arr[count][i].g = arr[h][i].g; 
            arr[h][i].g = temp; 

            // Swaps the B values
            temp = arr[count][i].b;  
            arr[count][i].b = arr[h][i].b; 
            arr[h][i].b = temp; 

            // Update counters
            count = count + 1; 
            h = h - 1; 

        } 

    }

    // Print values to file
    print_pixel_array(name, width, height, arr);
    free_matrix(height, arr);
}

void shuffle_filter(char *filename, char *name){
        
    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    pixel **arr = readBMP(filename);

    if(height<0){
        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
        exit(EXIT_FAILURE);
    } 
    


    int h1 = (int)(height / 3);
    int h2 = h1 * 2;

    int w1 = (int)(width / 3);
    int w2 = w1 * 2;

    pixel **temp = create_blank_array(width, height, 255, 255, 255);


    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            // For the first row
            if(i < h1)
            {
                // Lower Left in Upper Left 
                if(j < w1)
                {
                    temp[i][j].r = arr[h2 + i][j].r;
                    temp[i][j].g = arr[h2 + i][j].g;
                    temp[i][j].b = arr[h2 + i][j].b;
                }
                // Upper Right to Upper Middle
                else if(j >= w1 && j < w2)
                {
                    temp[i][j].r = arr[h1 + i][j].r;
                    temp[i][j].g = arr[h1 + i][j].g;
                    temp[i][j].b = arr[h1 + i][j].b;
                }
                // Upper Left to Upper Right
                else if(j >= w2 && j < width)
                {
                    temp[i][j].r = arr[i][j - w2].r;
                    temp[i][j].g = arr[i][j - w2].g;
                    temp[i][j].b = arr[i][j - w2].b;

                }
                else{
                    temp[i][j].r = 0;
                    temp[i][j].g = 0;
                    temp[i][j].b = 0;
                }


            }
            // For the middle row
            else if(i >= h1 && i < h2)
            {
                // Upper Right to Middle Left 
                if(j < w1)
                {
                    temp[i][j].r = arr[i - h1][j + w2].r;
                    temp[i][j].g = arr[i - h1][j + w2].g;
                    temp[i][j].b = arr[i - h1][j + w2].b;
                    //f << arr[i - h1][j + w2].r << " " << arr[i - h1][j+w2].g << " " << arr[i - h1][j+w2].b;
                }
                // Center to Upper Middle
                else if(j >= w1 && j < w2)
                {
                    temp[i][j].r = arr[i + h1][j + w1].r;
                    temp[i][j].g = arr[i + h1][j + w1].g;
                    temp[i][j].b = arr[i + h1][j + w1].b;
                    //f << arr[i + h1][j + w1].r << " " << arr[i + h1][j + w1].g << " " << arr[i + h1][j + w1].b;
                }
                // Upper Left to Upper Right
                else if(j >= w2)
                {
                    temp[i][j].r = arr[i + h1][j - w1].r;
                    temp[i][j].g = arr[i + h1][j - w1].g;
                    temp[i][j].b = arr[i + h1][j - w1].b;
                    //f << arr[i + h1][j - w1].r << " " << arr[i + h1][j - w1].g << " " << arr[i + h1][j - w1].b;
                }
                
                else{
                    temp[i][j].r = 0;
                    temp[i][j].g = 0;
                    temp[i][j].b = 0;
                }
                
            }
            // For the last row
            else
            {
                // Upper Right to Middle Left 
                if(j < w1)
                {
                    temp[i][j].r = arr[i - h1][j].r;
                    temp[i][j].g = arr[i - h1][j].g;
                    temp[i][j].b = arr[i - h1][j].b;
                    //f << arr[i - h1][j].r << " " << arr[i - h1][j].g << " " << arr[i - h1][j].b ;
                }
                // Center to Upper Middle
                else if(j >= w1 && j < w2)
                {
                    temp[i][j].r = arr[i - h2][j].r;
                    temp[i][j].g = arr[i - h2][j].g;
                    temp[i][j].b = arr[i - h2][j].b;
                    
                    //f << arr[i - h2][j].r << " " << arr[i - h2][j].g << " " << arr[i - h2][j].b;
                }
                // Upper Left to Upper Right
                else if(j >= w2)
                {
                    temp[i][j].r = arr[i - h1][j].r;
                    temp[i][j].g = arr[i - h1][j].g;
                    temp[i][j].b = arr[i - h1][j].b;
                }
                
                else
                {
                    temp[i][j].r = 0;
                    temp[i][j].g = 0;
                    temp[i][j].b = 0;
                }

            }          
        }
    }
    print_pixel_array(name, width, height, temp);
    free_matrix(height, arr);
    free_matrix(height, temp);
}

void pixelate_filter(char *filename, char *name, int p){

    /*

        THIS FUNCTION FILTERS EACH PICTURE WITH THE PIXEL FILTER

    */
    
    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    pixel **arr = readBMP(filename);

    if(height<0){

        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
        exit(EXIT_FAILURE);
    }

    if(p > width || p > height)
    {
        cout << "Pixelate factor too large." << endl;
    } 


    pixel **temp = create_blank_array(width, height, 255, 255, 255);

    for(int i = p; i < height; i+=p)
    {
        for(int j = p; j < width; j+=p)
        {
            int r = 0;
            int g = 0; 
            int b = 0;
            int count = 0;
            //set all 25 equal to average
            for(int k = i-p; k < (i + p); k++)
            {
                if(k >= height)
                {
                    break;
                }
                for(int m = j-p; m < (j + p); m++)
                {
                    if(m >= width)
                    {
                        break;
                    }
                    r += arr[k][m].r;
                    g += arr[k][m].g;
                    b += arr[k][m].b;
                    count++;
                }
            }
            // Get average
            r = r /count;
            g = g /count;
            b = b / count;

            for(int k = i-p; k < (i + p); k++)
            {
                if(k >= height)
                {
                    break;
                }
                for(int m = j-p; m < (j + p); m++)
                {
                    if(m >= width)
                    {
                        break;
                    }
                    temp[k][m].r = r;
                    temp[k][m].g = g;
                    temp[k][m].b = b;
                }
            }
            
        }

    }

   print_pixel_array(name, width, height, temp);
   free_matrix(height, arr);
   free_matrix(height, temp);
}

int rotate_i(int i_val, int j_val, int list_width, int list_height, int deg){

    float x_val = j_val - list_width;
    float y_val = list_height - i_val; 

    float x_val_original = x_val;
    float y_val_original = y_val;

    const float pi = 3.14159265358979f;
    float rads = deg*(pi/180);

    x_val = (x_val_original*cos(rads))-(y_val_original*sin(rads));
    x_val = round(x_val);

    y_val = (x_val_original*sin(rads))+(y_val_original*cos(rads));
    y_val = round(y_val);

    j_val = int(x_val + list_width);
    i_val = int(list_height - y_val);

    return i_val;
}

int rotate_j(int i_val, int j_val, int list_width, int list_height, int deg){

    float x_val = j_val - list_width;
    float y_val = list_height - i_val; 

    float x_val_original = x_val;
    float y_val_original = y_val;

    const float pi = 3.14159265358979f;
    float rads = deg*(pi/180);

    x_val = (x_val_original*cos(rads))-(y_val_original*sin(rads));
    x_val = round(x_val);

    y_val = (x_val_original*sin(rads))+(y_val_original*cos(rads));
    y_val = round(y_val);

    j_val = int(x_val + list_width);
    i_val = int(list_height - y_val);

    return j_val;
}

void kaleidoscope(char *filename, char *name){
    int height;
    int width;
    pixel **arr;

    if(check_if_PBM(filename) == 1)
    {
        width = get_PBM_width(filename);
        height = get_PBM_height(filename);
        arr = read_exported_PBM(filename);
    }
    else
    {
        width = get_BMP_width(filename);
        height = get_BMP_height(filename);
        arr = readBMP(filename);
    }

    if(height < 0){

        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
    }

    if(width % 2 != 0){
        width = width - 1;
    }

    if(height % 2 != 0){
        height = height - 1;
    }

    pixel **arr_even = create_blank_array(width,height);

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            arr_even[i][j].r = arr[i][j].r;
            arr_even[i][j].g = arr[i][j].g;
            arr_even[i][j].b = arr[i][j].b;
        }
    }
    // print_pixel_array(name, width, height, arr_even);

    width = width/2;
    height = height/2;

    // The image should be even at this point

    pixel **arr_crop = create_blank_array(width,height);

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            arr_crop[i][j].r = arr_even[i][j].r;
            arr_crop[i][j].g = arr_even[i][j].g;
            arr_crop[i][j].b = arr_even[i][j].b;
        }
    }

    pixel **arr_sq;
    if(width >= height){
        arr_sq = create_blank_array(height,height);
        int start_at = width - height;

        for(int i = 0; i < height; i++){
            for(int j = start_at; j < width; j++){

                arr_sq[i][j-start_at].r = arr_crop[i][j].r;
                arr_sq[i][j-start_at].g = arr_crop[i][j].g;
                arr_sq[i][j-start_at].b = arr_crop[i][j].b;
            }
        }
        width = height;
    }
    if(width < height){
        arr_sq = create_blank_array(width,width);
        int start_at = height - width;

        for(int i = start_at; i < height; i++){
            for(int j = 0; j < width; j++){

                arr_sq[i-start_at][j].r = arr_crop[i][j].r;
                arr_sq[i-start_at][j].g = arr_crop[i][j].g;
                arr_sq[i-start_at][j].b = arr_crop[i][j].b;
            }
        }
        height = width;
    }

    // The image is now a square, and the heights and widths are final


    pixel u_pix = unique_pixel(arr_sq, width, height);

    pixel **arr_tri = create_blank_array(width, height, u_pix.r, u_pix.g, u_pix.b);

    // cout << width << endl;
    // cout << height << endl;


    for(int i = 0; i < height; i++){

            int i_copy = i;

            int i_copy_2 = rotate_i(i_copy, width-1, width-1, height-1, 30);
            int j_copy_2 = rotate_j(i_copy, width-1, width-1, height-1, 30);

            // cout << i_copy_2 << endl;
            // cout << j_copy_2 << endl;

            if(0 <= i_copy_2 <= height && 0 <= j_copy_2 <= width)
            {
                arr_tri[i_copy_2][j_copy_2].r = 0;
                arr_tri[i_copy_2][j_copy_2].g = 0;
                arr_tri[i_copy_2][j_copy_2].b = 0;
            }   
        }


    // Fills in the image triangle with black

    for(int i = width-1; i > 0; i--){
        int swit = 0; 

        for(int j = 0; j < height; j++){
            if(arr_tri[j][i].r == 0 && arr_tri[j][i].r == 0 && arr_tri[j][i].r == 0){
                swit = 1;
            }
        }

        if(swit == 1){
            int stop_color = 0;
            for(int j = 0; j < height; j++){
                if(arr_tri[j][i].r == 0 && arr_tri[j][i].r == 0 && arr_tri[j][i].r == 0){
                    stop_color = 1;
                }
                else{
                    arr_tri[j][i].r = 0;
                    arr_tri[j][i].g = 0;
                    arr_tri[j][i].b = 0;
                }
                if(stop_color == 1){
                    break;
                }
            }
        }
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < height; j++){
            if(arr_tri[i][j].r == 0 && arr_tri[i][j].r == 0 && arr_tri[i][j].r == 0){
                arr_tri[i][j].r = arr_sq[i][j].r;
                arr_tri[i][j].g = arr_sq[i][j].g;
                arr_tri[i][j].b = arr_sq[i][j].b;
            }
        }
    }

    // arr_tri = original triangle image

    // The array is now a 30 degree triangle

    pixel **arr_tri_rot = create_blank_array(width, height, u_pix.r, u_pix.g, u_pix.b);

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(arr_tri[i][j].r != u_pix.r && arr_tri[i][j].g != u_pix.g && arr_tri[i][j].b != u_pix.b){

            int i_copy = i;
            int j_copy = j;

            int i_copy_2 = rotate_i(i_copy, j_copy, width-1, height-1, 30);
            int j_copy_2 = rotate_j(i_copy, j_copy, width-1, height-1, 30);

            if(0 <= i_copy_2 && i_copy_2 < height-1 && 0 <= j_copy_2 && j_copy_2< width-1){

                arr_tri_rot[i_copy_2][j_copy_2].r = arr_tri[i][j].r;
                arr_tri_rot[i_copy_2][j_copy_2].g = arr_tri[i][j].g;
                arr_tri_rot[i_copy_2][j_copy_2].b = arr_tri[i][j].b;
            }
            
            }
        }
    }

    // The image is rotated 30 degrees
    //print_pixel_array(name, width, height, arr_tri_rot);
    
    for(int i = 1; i < height-1; i++){
        for(int j = 1; j < width-1; j++){
            if(arr_tri_rot[i][j].r == u_pix.r && arr_tri_rot[i][j].g == u_pix.g && arr_tri_rot[i][j].b == u_pix.b){
                //if the pixel is the unique color
                if(arr_tri_rot[i][j+1].r != u_pix.r && arr_tri_rot[i][j+1].g != u_pix.g && arr_tri_rot[i][j+1].b != u_pix.b){
                    // if the pixel to the right is a color
                    if(arr_tri_rot[i][j-1].r != u_pix.r && arr_tri_rot[i][j-1].g != u_pix.g && arr_tri_rot[i][j-1].b != u_pix.b){
                    // if the pixel to the left is a color
                        if(arr_tri_rot[i-1][j].r != u_pix.r && arr_tri_rot[i-1][j].g != u_pix.g && arr_tri_rot[i-1][j].b != u_pix.b){
                        // if the pixel above is a color
                            if(arr_tri_rot[i+1][j].r != u_pix.r && arr_tri_rot[i+1][j].g != u_pix.g && arr_tri_rot[i+1][j].b != u_pix.b){
                            // if the pixel below is a color

                                    int avg_red = arr_tri_rot[i+1][j].r + arr_tri_rot[i-1][j].r + arr_tri_rot[i][j+1].r + arr_tri_rot[i][j-1].r;
                                    avg_red = (avg_red/4);

                                    int avg_gre = arr_tri_rot[i+1][j].g + arr_tri_rot[i-1][j].g + arr_tri_rot[i][j+1].g + arr_tri_rot[i][j-1].g;
                                    avg_gre = (avg_gre/4);

                                    int avg_blu = arr_tri_rot[i+1][j].b + arr_tri_rot[i-1][j].b + arr_tri_rot[i][j+1].b + arr_tri_rot[i][j-1].b;
                                    avg_blu = (avg_blu/4);

                                    arr_tri_rot[i][j].r = avg_red;
                                    arr_tri_rot[i][j].g = avg_gre;
                                    arr_tri_rot[i][j].b = avg_blu;
                            }
                        }
                    }
                }
            }
        }
    }

    pixel **arr_tri_rot_t = create_blank_array(width, height, u_pix.r, u_pix.g, u_pix.b);

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
        
                arr_tri_rot_t[i][j].r = arr_tri_rot[j][i].r;
                arr_tri_rot_t[i][j].g = arr_tri_rot[j][i].g;
                arr_tri_rot_t[i][j].b = arr_tri_rot[j][i].b;

            }
        }

    pixel **arr_tri_rot_s = create_blank_array(width, height, u_pix.r, u_pix.g, u_pix.b);

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(arr_tri[i][j].r != u_pix.r && arr_tri[i][j].g != u_pix.g && arr_tri[i][j].b != u_pix.b){

            int i_copy = i;
            int j_copy = j;

            int i_copy_2 = rotate_i(i_copy, j_copy, width-1, height-1, 60);
            int j_copy_2 = rotate_j(i_copy, j_copy, width-1, height-1, 60);

            if(0 <= i_copy_2 && i_copy_2 < height-1 && 0 <= j_copy_2 && j_copy_2< width-1){

                arr_tri_rot_s[i_copy_2][j_copy_2].r = arr_tri[i][j].r;
                arr_tri_rot_s[i_copy_2][j_copy_2].g = arr_tri[i][j].g;
                arr_tri_rot_s[i_copy_2][j_copy_2].b = arr_tri[i][j].b;
            }
            
            }
        }
    }

    for(int i = 1; i < height-1; i++){
        for(int j = 1; j < width-1; j++){
            if(arr_tri_rot_s[i][j].r == u_pix.r && arr_tri_rot_s[i][j].g == u_pix.g && arr_tri_rot_s[i][j].b == u_pix.b){
                //if the pixel is the unique color
                if(arr_tri_rot_s[i][j+1].r != u_pix.r && arr_tri_rot_s[i][j+1].g != u_pix.g && arr_tri_rot_s[i][j+1].b != u_pix.b){
                    // if the pixel to the right is a color
                    if(arr_tri_rot_s[i][j-1].r != u_pix.r && arr_tri_rot_s[i][j-1].g != u_pix.g && arr_tri_rot_s[i][j-1].b != u_pix.b){
                    // if the pixel to the left is a color
                        if(arr_tri_rot_s[i-1][j].r != u_pix.r && arr_tri_rot_s[i-1][j].g != u_pix.g && arr_tri_rot_s[i-1][j].b != u_pix.b){
                        // if the pixel above is a color
                            if(arr_tri_rot_s[i+1][j].r != u_pix.r && arr_tri_rot_s[i+1][j].g != u_pix.g && arr_tri_rot_s[i+1][j].b != u_pix.b){
                            // if the pixel below is a color

                                    int avg_red = arr_tri_rot_s[i+1][j].r + arr_tri_rot_s[i-1][j].r + arr_tri_rot_s[i][j+1].r + arr_tri_rot_s[i][j-1].r;
                                    avg_red = (avg_red/4);

                                    int avg_gre = arr_tri_rot_s[i+1][j].g + arr_tri_rot_s[i-1][j].g + arr_tri_rot_s[i][j+1].g + arr_tri_rot_s[i][j-1].g;
                                    avg_gre = (avg_gre/4);

                                    int avg_blu = arr_tri_rot_s[i+1][j].b + arr_tri_rot_s[i-1][j].b + arr_tri_rot_s[i][j+1].b + arr_tri_rot_s[i][j-1].b;
                                    avg_blu = (avg_blu/4);

                                    arr_tri_rot_s[i][j].r = avg_red;
                                    arr_tri_rot_s[i][j].g = avg_gre;
                                    arr_tri_rot_s[i][j].b = avg_blu;
                            }
                        }
                    }
                }
            }
        }
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(arr_tri[i][j].r != u_pix.r && arr_tri[i][j].g != u_pix.g && arr_tri[i][j].b != u_pix.b){
                arr_tri_rot_t[i][j].r = arr_tri[i][j].r;
                arr_tri_rot_t[i][j].g = arr_tri[i][j].g;
                arr_tri_rot_t[i][j].b = arr_tri[i][j].b;
            }
        }
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(arr_tri_rot_s[i][j].r != u_pix.r && arr_tri_rot_s[i][j].g != u_pix.g && arr_tri_rot_s[i][j].b != u_pix.b){
                arr_tri_rot_t[i][j].r = arr_tri_rot_s[i][j].r;
                arr_tri_rot_t[i][j].g = arr_tri_rot_s[i][j].g;
                arr_tri_rot_t[i][j].b = arr_tri_rot_s[i][j].b;
            }
        }
    }


    //Edge case (bottom):

    for(int i = 0; i < height; i++){
        arr_tri_rot_t[height-1][i].r = arr_tri_rot_t[height-2][i].r;
        arr_tri_rot_t[height-1][i].g = arr_tri_rot_t[height-2][i].g;
        arr_tri_rot_t[height-1][i].b = arr_tri_rot_t[height-2][i].b;
    }

    for(int i = 0; i < height; i++){
        for(int j = 1; j < width-1; j++){
            if(arr_tri_rot_t[i][j].r == u_pix.r && arr_tri_rot_t[i][j].g == u_pix.g && arr_tri_rot_t[i][j].b == u_pix.b){
                if(arr_tri_rot_t[i][j-1].r != u_pix.r && arr_tri_rot_t[i][j-1].g != u_pix.g && arr_tri_rot_t[i][j-1].b != u_pix.b){
                    if(arr_tri_rot_t[i][j+1].r != u_pix.r && arr_tri_rot_t[i][j+1].g != u_pix.g && arr_tri_rot_t[i][j+1].b != u_pix.b){

                        int avg_red_h = arr_tri_rot_t[i][j+1].r + arr_tri_rot_t[i][j-1].r;
                        avg_red_h = (avg_red_h/2);

                        int avg_gre_h = arr_tri_rot_t[i][j+1].g + arr_tri_rot_t[i][j-1].g;
                        avg_gre_h = (avg_gre_h/2);

                        int avg_blu_h = arr_tri_rot_t[i][j+1].b + arr_tri_rot_t[i][j-1].b;
                        avg_blu_h = (avg_blu_h/2);

                        arr_tri_rot_t[i][j].r = avg_red_h;
                        arr_tri_rot_t[i][j].g = avg_gre_h;
                        arr_tri_rot_t[i][j].b = avg_blu_h;
                    }   
                }
            }
        }
    }

    for(int i = 1; i < height-1; i++){
        for(int j = 0; j < width; j++){
            if(arr_tri_rot_t[i][j].r == u_pix.r && arr_tri_rot_t[i][j].g == u_pix.g && arr_tri_rot_t[i][j].b == u_pix.b){
                if(arr_tri_rot_t[i-1][j].r != u_pix.r && arr_tri_rot_t[i-1][j].g != u_pix.g && arr_tri_rot_t[i-1][j].b != u_pix.b){
                    if(arr_tri_rot_t[i+1][j].r != u_pix.r && arr_tri_rot_t[i+1][j].g != u_pix.g && arr_tri_rot_t[i+1][j].b != u_pix.b){

                        int avg_red_h = arr_tri_rot_t[i][j+1].r + arr_tri_rot_t[i][j-1].r;
                        avg_red_h = (avg_red_h/2);

                        int avg_gre_h = arr_tri_rot_t[i][j+1].g + arr_tri_rot_t[i][j-1].g;
                        avg_gre_h = (avg_gre_h/2);

                        int avg_blu_h = arr_tri_rot_t[i][j+1].b + arr_tri_rot_t[i][j-1].b;
                        avg_blu_h = (avg_blu_h/2);

                        arr_tri_rot_t[i][j].r = avg_red_h;
                        arr_tri_rot_t[i][j].g = avg_gre_h;
                        arr_tri_rot_t[i][j].b = avg_blu_h;
                    }   
                }
            }
        }
    }


    int wid_sq = width*.73;
    int hig_sq = height*.73;

    int off_w = width - wid_sq;
    int off_h = height - hig_sq;

    // cout << "" << endl;
    // cout << wid_sq << endl;
    // cout << hig_sq << endl;

    pixel **fin_arr = create_blank_array(wid_sq, hig_sq, u_pix.r, u_pix.g, u_pix.b);

    for(int i = off_h; i < height; i++){
        for(int j = off_w; j < width; j++){
            fin_arr[i-off_w][j-off_w].r = arr_tri_rot_t[i][j].r; 
            fin_arr[i-off_w][j-off_w].g = arr_tri_rot_t[i][j].g;
            fin_arr[i-off_w][j-off_w].b = arr_tri_rot_t[i][j].b;
        }
    }


    int double_width = wid_sq * 2;
    int double_height = hig_sq * 2;

    pixel **mirr = create_blank_array(double_width, hig_sq);

    for(int i = 0; i < hig_sq; i++){
        for(int j = 0; j < wid_sq; j++){
            mirr[i][j].r = fin_arr[i][j].r; 
            mirr[i][j].g = fin_arr[i][j].g;
            mirr[i][j].b = fin_arr[i][j].b;

            mirr[i][j+wid_sq].r = fin_arr[i][wid_sq-j-1].r; 
            mirr[i][j+wid_sq].g = fin_arr[i][wid_sq-j-1].g;
            mirr[i][j+wid_sq].b = fin_arr[i][wid_sq-j-1].b;
        }
    }

    pixel **final = create_blank_array(double_width, double_height);

    for(int i = 0; i < hig_sq; i++){
        for(int j = 0; j < double_width; j++){
            final[i][j].r = mirr[i][j].r; 
            final[i][j].g = mirr[i][j].g;
            final[i][j].b = mirr[i][j].b;

            final[i+hig_sq][j].r = mirr[hig_sq-1-i][j].r; 
            final[i+hig_sq][j].g = mirr[hig_sq-1-i][j].g;
            final[i+hig_sq][j].b = mirr[hig_sq-1-i][j].b;
        }
    }

    print_pixel_array(name, double_width, double_height, final);
   
    free_matrix(height, arr);
    free_matrix(height, arr_even);
    free_matrix(height, arr_crop);
    free_matrix(height, arr_sq);
    free_matrix(height, arr_tri);
    free_matrix(height, arr_tri_rot);
    free_matrix(height, arr_tri_rot_t);
    free_matrix(height, arr_tri_rot_s);
    free_matrix(height, fin_arr);
    free_matrix(height, mirr);
    free_matrix(height, final);
}




/*
           --- EXAMPLE .PBM IMAGE FORMAT ---

This is what a 5x10 .pbm image looks like:

If you copy and paste this code into a blank file
that has a .pbm file extension, you should get a 
purple rectangle that's 5x10 pixels in size:

Create a .pbm file with:

    touch <insert_name>.pbm
    vim <insert_name>.pbm 

Image code:

P3
5 10
255
125 85 175 125 85 175 125 85 175 125 85 175 125 85 176
125 85 175 125 85 175 125 85 175 125 85 175 125 85 176
125 85 175 125 85 175 125 85 175 125 85 175 125 85 176
125 85 175 125 85 175 125 85 175 125 85 175 125 85 176
125 85 175 125 85 175 125 85 175 125 85 175 125 85 176
125 85 175 125 85 175 125 85 175 125 85 175 125 85 176
125 85 175 125 85 175 125 85 175 125 85 175 125 85 176
125 85 175 125 85 175 125 85 175 125 85 175 125 85 176
125 85 175 125 85 175 125 85 175 125 85 175 125 85 176
125 85 175 125 85 175 125 85 175 125 85 175 125 85 176 0

*/