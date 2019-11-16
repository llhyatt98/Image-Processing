#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <string.h>
#include <map>
#include "./hdrs/IO.hh"
#include "./hdrs/matrix.hh"
#include "./hdrs/filter.hh"

using namespace std;

// Pixel Altering Functions 

//RGB values set to default parameters in header
void create_blank_image(char* name, int width, int height, int r, int g, int b){
    // -------------------------------------------------------------------------------
    // Function: Creates a blank image of specified size and color (defaults to white).
    // Arguments: Name of the output image, width, height, and r/g/b integers.
    // Returns: Void function that creates a blank .pbm file in your directory.
    // -------------------------------------------------------------------------------
    
    ofstream f;     // Writes new file variable 'f'.

    f.open(name);   // Opens and names the file with the specified 'name'.
    f << "P3\n";    // Writes magic number to file (tells the computer its an r/g/b image).
    f << width << " " << height << "\n"; // Writes width and height to the file.
    f << "255\n";   // Writes the color range you're working with to the file (standard = 255).

    for(int i = 0; i < height; i++)     // Iterates through height of the image.
    {
        for (int j = 0; j < width; j++) // Iterates through width of the image.
        {
            if(j == width-1){
            // Writes r/g/b pixel data so there isn't an extra space at the end of each row.
                f << r << " " << g << " " << b;
            }

            else{
            // Writes the r/g/b data from the 2D pixel struct array into the file.
            // This format seperates each values by a single space.
                f << r << " " << g << " " << b << " ";
            }
        }

        if(i == height-1){
        // Adds a 0 to the very end of the file to signal the image is completed.
        // .pbm files will always end in a 0 that is seperate from the last pixel. 

            f << " 0";
        }
        
        else{
        // Adds a new line at the end of every row.
            f << "\n";
        }
    }
    f.close(); // Closes the file.
}

pixel **create_blank_array(int width, int height, int r, int g, int b){
    // -------------------------------------------------------------------------------
    // Function: Creates a blank image of specified size and color (defaults to white).
    // Arguments: Name of the output image, width, height, and r/g/b integers.
    // Returns: Void function that creates a blank .pbm file in your directory.
    // -------------------------------------------------------------------------------
    
    pixel **arr = new pixel*[height];

    for (int i = 0; i < height; ++i) {
        arr[i] = new pixel[width];
    }

    for(int i = 0; i < height; i++)     // Iterates through height of the image.
    {
        for (int j = 0; j < width; j++) // Iterates through width of the image.
        {
            arr[i][j].r = r;
            arr[i][j].g = g;
            arr[i][j].b = b;
        }
    }
    
    return arr; 
}

int pix_range(int p){
    // Increases a pixels value by 50
    // Makes sure it's in range 
    p = p + 50;

    if(p > 255)
    {
        p = 255;
    }
    return p;
}

int pix_range_input(int p, int num){
    // Increases a pixels value by a certain amount
    // Makes sure it's in range 
    p = p + num;

    if(p > 255)
    {
        p = 255;
    }
    else if(p < 0)
    {
        p = 0;
    }
    return p;
}

void greyscale_filter(char* filename, char *name){
    // ---------------------------------------------------------------------------
    // Function: Writes a copy of the input .bmp in greyscale stored as a .pbm 
    // Arguments: Takes the name of the input image and name of the output image.
    // Returns: Void function that creates a new .pbm file in your directory
    // ---------------------------------------------------------------------------

    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    pixel **arr = readBMP(filename); 
    if(height<0){

        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
    }

    else
    {
        ofstream f;
        f.open(name);
        f << "P2\n"; // Magic number that tells computer this is a greyscale image
        f << width << " " << height << "\n";
        f << "255\n";

        for(int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if(j == width-1){
                    // Takes the average of the r/g/b values and writes to file
                    int pix = (int)(((arr[i][j].r + arr[i][j].g + arr[i][j].b)/3)+0.5);
                    f << pix;
                }

                else{
                    // Takes the average of the r/g/b values and writes to file
                    int pix = (int)(((arr[i][j].r + arr[i][j].g + arr[i][j].b)/3)+0.5);
                    f << pix << " ";
                }
            }

            if(i == height-1){
                f << " 0";
            }
        
            else{
                f << "\n";
            }
        }
        f.close();
    }  

    free_matrix(height, arr);
}

void black_white_filter(char* filename, char *name){
    // ---------------------------------------------------------------------------
    // Function: Writes a copy of the input .bmp in black & white stored as a .pbm 
    // Arguments: Takes the name of the input image and name of the output image.
    // Returns: Void function that creates a new .pbm file in your directory
    // ---------------------------------------------------------------------------

    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    pixel **arr = readBMP(filename); 
    if(height<0){

        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
    }

    else
    {
        ofstream f;
        f.open(name);
        f << "P2\n"; // Magic number that tells computer this is a greyscale image
        f << width << " " << height << "\n";
        f << "255\n";

        for(int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if(j == width-1){
                    // Takes the average of the r/g/b values and writes to file
                    int pix = (int)(((arr[i][j].r + arr[i][j].g + arr[i][j].b)/3)+0.5);
                    if(pix <= 110)
                    {
                        f << 0;
                    }
                    else
                    {
                        f << 255;
                    }
                }

                else{
                    // Takes the average of the r/g/b values and writes to file
                    int pix = (int)(((arr[i][j].r + arr[i][j].g + arr[i][j].b)/3)+0.5);
                    if(pix <= 110)
                    {
                        f << 0 << " ";
                    }
                    else
                    {
                        f << 255 << " ";
                    }
                }
            }

            if(i == height-1){
                f << " 0";
            }
        
            else{
                f << "\n";
            }
        }
        f.close();
    }  

    free_matrix(height, arr);
}

void RGB_filter(char *filename, char *name){
        
    // Filter which finds and inserts dominant pixel value

    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    pixel **arr = readBMP(filename);

    if(height<0){
        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
        exit(EXIT_FAILURE);
    }

    pixel **temp = create_blank_array((width),(height), 255, 255, 255);
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // If the pixel is mostly red
            if(arr[i][j].r > arr[i][j].g && arr[i][j].r > arr[i][j].b)
            {
                temp[i][j].r = 255;
                temp[i][j].g = arr[i][j].g;
                temp[i][j].b = arr[i][j].b;

            }
            // If pixel is mostly green
            else if(arr[i][j].g > arr[i][j].r && arr[i][j].g > arr[i][j].b)
            {
                temp[i][j].r = arr[i][j].r;
                temp[i][j].g = 255;
                temp[i][j].b = arr[i][j].b;

            }                    
            else if(arr[i][j].b > arr[i][j].r && arr[i][j].b > arr[i][j].g)
            {
                temp[i][j].r = arr[i][j].r;
                temp[i][j].g = arr[i][j].g;
                temp[i][j].b = 255;
            }
            else //else leave the pixel
            {
                temp[i][j].r = arr[i][j].r;
                temp[i][j].g = arr[i][j].g;
                temp[i][j].b = arr[i][j].b;
            }
        }
    }
    print_pixel_array(name, width, height, temp);
    free_matrix(height, arr);
    free_matrix(height, temp);
}

void inverted_filter(char *filename, char *name){
    // ---------------------------------------------------------------------------
    // Function: Writes an inverted copy of the input .bmp in stored as a .pbm 
    // Arguments: Takes the name of the input image and name of the output image.
    // Returns: Void function that creates a new .pbm file in your directory
    // ---------------------------------------------------------------------------

    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    pixel **arr = readBMP(filename); 

    if(height<0){

        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
    }
    else
    {
        pixel **temp = create_blank_array((width),(height), 255, 255, 255);
        for(int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                //Calculation for inversion.
                temp[i][j].r = 255 - arr[i][j].r;
                temp[i][j].g = 255 - arr[i][j].g;
                temp[i][j].b = 255 - arr[i][j].b;
                
            }
        }
        print_pixel_array(name, width, height, temp);
        free_matrix(height, temp);
    }  

    free_matrix(height, arr);
}

void enhance_filter(char *filename, char *name){

    /*

        THIS FUNCTION ALTERS EACH PHOTO TO ENHANCE ITS PIXEL DATA

    */
    
    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    pixel **arr = readBMP(filename);

    if(height<0){
        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
        exit(EXIT_FAILURE);
    }

    pixel **temp = create_blank_array(width, height, 255, 255, 255);

    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redpix, bluepix, greenpix;
            // RED COLORS
            if((arr[i][j].r <= 255 && arr[i][j].r >= 51) && (arr[i][j].g <= 204 && arr[i][j].g >= 0) && (arr[i][j].b <= 204 && arr[i][j].b >= 0))
            {
                redpix = pix_range(arr[i][j].r);

                temp[i][j].r = redpix;
                temp[i][j].g = arr[i][j].g;
                temp[i][j].b = arr[i][j].b;
                
            }
            // ORANGE COLORS
            else if((arr[i][j].r <= 255 && arr[i][j].r >= 51) && (arr[i][j].g <= 229 && arr[i][j].g >= 25) && (arr[i][j].b <= 204 && arr[i][j].b >= 0))
            {
                redpix = pix_range(arr[i][j].r);
                greenpix = pix_range(arr[i][j].g);
                bluepix = pix_range(arr[i][j].b);
                
                temp[i][j].r = redpix;
                temp[i][j].g = greenpix;
                temp[i][j].b = bluepix;

            }                    
            // YELLOW COLORS
            else if((arr[i][j].r <= 255 && arr[i][j].r >= 51) && (arr[i][j].g <= 255 && arr[i][j].g >= 51) && (arr[i][j].b <= 204 && arr[i][j].b >= 0))
            {
                redpix = pix_range(arr[i][j].r);
                greenpix = pix_range(arr[i][j].g);
                
                temp[i][j].r = redpix;
                temp[i][j].g = greenpix;
                temp[i][j].b = arr[i][j].b;

            }
            // LIGHT GREEN COLORS
            else if((arr[i][j].r <= 229 && arr[i][j].r >= 25) && (arr[i][j].g <= 255 && arr[i][j].g >= 51) && (arr[i][j].b <= 204 && arr[i][j].b >= 0))
            {
                redpix = pix_range(arr[i][j].r);
                greenpix = pix_range(arr[i][j].g);
                bluepix = pix_range(arr[i][j].b);
                
                temp[i][j].r = redpix;
                temp[i][j].g = greenpix;
                temp[i][j].b = bluepix;

            }
            // GREEN COLORS
            else if((arr[i][j].r <= 204 && arr[i][j].r >= 0) && (arr[i][j].g <= 255 && arr[i][j].g >= 51) && (arr[i][j].b <= 204 && arr[i][j].b >= 0))
            {
                greenpix = pix_range(arr[i][j].g);

                temp[i][j].r = arr[i][j].r;
                temp[i][j].g = greenpix;
                temp[i][j].b = arr[i][j].b;

            }
            // BLUE-GREEN COLORS
            else if((arr[i][j].r <= 204 && arr[i][j].r >= 0) && (arr[i][j].g <= 255 && arr[i][j].g >= 51) && (arr[i][j].b <= 229 && arr[i][j].b >= 28))
            {
                redpix = pix_range(arr[i][j].r);
                greenpix = pix_range(arr[i][j].g);
                bluepix = pix_range(arr[i][j].b);
                
                temp[i][j].r = redpix;
                temp[i][j].g = greenpix;
                temp[i][j].b = bluepix;

            }
            // CYAN COLORS
            else if((arr[i][j].r <= 204 && arr[i][j].r >= 0) && (arr[i][j].g <= 255 && arr[i][j].g >= 51) && (arr[i][j].b <= 255 && arr[i][j].b >= 51))
            {
                bluepix = pix_range(arr[i][j].b);
                greenpix = pix_range(arr[i][j].g);
                
                temp[i][j].r = arr[i][j].r;
                temp[i][j].g = greenpix;
                temp[i][j].b = bluepix;

            }
            // BLUE COLORS
            else if((arr[i][j].r <= 204 && arr[i][j].r >= 0) && (arr[i][j].g <= 229 && arr[i][j].g >= 25) && (arr[i][j].b <= 255 && arr[i][j].b >= 51))
            {
                bluepix = pix_range(arr[i][j].b);

                temp[i][j].r = arr[i][j].r;
                temp[i][j].g = arr[i][j].g;
                temp[i][j].b = bluepix;



            }
            // DARK BLUE COLORS
            else if((arr[i][j].r <= 204 && arr[i][j].r >= 0) && (arr[i][j].g <= 204 && arr[i][j].g >= 0) && (arr[i][j].b <= 255 && arr[i][j].b >= 51))
            {
                redpix = pix_range(arr[i][j].r);
                greenpix = pix_range(arr[i][j].g);
                bluepix = pix_range(arr[i][j].b);

                temp[i][j].r = redpix;
                temp[i][j].g = greenpix;
                temp[i][j].b = bluepix;

            }
            // PURPLE COLORS
            else if((arr[i][j].r <= 229 && arr[i][j].r >= 25) && (arr[i][j].g <= 204 && arr[i][j].g >= 0) && (arr[i][j].b <= 255 && arr[i][j].b >= 51))
            {
                redpix = pix_range(arr[i][j].r);
                greenpix = pix_range(arr[i][j].g);
                bluepix = pix_range(arr[i][j].b);
                
                temp[i][j].r = redpix;
                temp[i][j].g = greenpix;
                temp[i][j].b = bluepix;

            }
            // PINK COLORS
            else if((arr[i][j].r <= 255 && arr[i][j].r >= 51) && (arr[i][j].g <= 229 && arr[i][j].g >= 25) && (arr[i][j].b <= 204 && arr[i][j].b >= 0))
            {
                redpix = pix_range(arr[i][j].r);
                bluepix = pix_range(arr[i][j].b);

                temp[i][j].r = redpix;
                temp[i][j].g = arr[i][j].g;
                temp[i][j].b = bluepix;

            }
            // HOT PINK COLORS
            else if((arr[i][j].r <= 255 && arr[i][j].r >= 51) && (arr[i][j].g <= 204 && arr[i][j].g >= 0) && (arr[i][j].b <= 229 && arr[i][j].b >= 25))
            {
                redpix = pix_range(arr[i][j].r);
                greenpix = pix_range(arr[i][j].g);
                bluepix = pix_range(arr[i][j].b);
              
                temp[i][j].r = redpix;
                temp[i][j].g = greenpix;
                temp[i][j].b = bluepix;
            }
            //black or white keep the same
            else
            {
                temp[i][j].r = arr[i][j].r;
                temp[i][j].g = arr[i][j].g;
                temp[i][j].b = arr[i][j].b;

            }
            
        }
    }
    print_pixel_array(name, width, height, temp);
    free_matrix(height, arr);
    free_matrix(height, temp);
}

void antique_filter(char *filename, char *name){

    /*

        THIS FUNCTION FILTERS EACH PICTURE WITH THE SEPIA FILTER

    */
    
    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    pixel **arr = readBMP(filename);

    if(height<0){
        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
        exit(EXIT_FAILURE);
    }

    pixel **temp = create_blank_array((width),(height), 255, 255, 255);
    int redpix, bluepix, greenpix; 
    for(int i = 0; i < height; i++)     // Iterates through height of the image.
    {
        for (int j = 0; j < width; j++) // Iterates through width of the image.
        {
            // Writes r/g/b pixel data so there isn't an extra space at the end of each row.
            redpix = int(0.439 * arr[i][j].r);
            redpix = pix_range(redpix);
            greenpix = int(0.259 * arr[i][j].g);
            greenpix = pix_range(greenpix);
            bluepix = int(.078 * arr[i][j].b);
            bluepix = pix_range(bluepix);

            temp[i][j].r = redpix;
            temp[i][j].g = greenpix;
            temp[i][j].b = bluepix; 
        }

    }
    print_pixel_array(name, width, height, temp);
    free_matrix(height, arr);
    free_matrix(height, temp);
}

void blood_filter(char *filename, char *name){

    /*

        THIS FUNCTION FILTERS EACH PICTURE WITH THE BLOOD FILTER

    */
    
    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    pixel **arr = readBMP(filename);

    if(height<0){

        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        pixel **temp = create_blank_array((width),(height), 255, 255, 255);

        for(int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                //Calculation for inversion.
                int r = arr[i][j].r;
                int g = arr[i][j].g;
                int b = arr[i][j].b;

                if((r + g + b) >= 256){
                    temp[i][j].r = 255; 
                    temp[i][j].g = 0;
                    temp[i][j].b = 0;
                }
                else{
                    temp[i][j].r = 0;
                    temp[i][j].g = 0;
                    temp[i][j].b = 0;
                }
            }
        }
        print_pixel_array(name, width, height, temp);
        free_matrix(height, temp);
    }  
    free_matrix(height, arr);
}

void blur_filter(char *filename, char *name, int blur){

    /*

        THIS FUNCTION FILTERS EACH PICTURE WITH THE BLUR FILTER

    */
    
    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    pixel **arr = readBMP(filename);

    if(height<0){

        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
    }

    else
    {
        pixel **temp = create_blank_array(width-4, height, 255, 255, 255);
            
        while(blur){
            
            //Majority
            for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    if(i < 2 || j < 2 || i > height-3 || j > width-3){
                        temp[i][j].r = arr[i][j].r;
                        temp[i][j].g = arr[i][j].g;
                        temp[i][j].b = arr[i][j].b;
                    }
                    else{
                        int average_r = (arr[i-2][j-2].r + arr[i-2][j-1].r + arr[i-2][j].r + arr[i-2][j+1].r + arr[i-2][j+2].r +
                            arr[i-1][j-2].r + arr[i-1][j-1].r + arr[i-1][j].r + arr[i-1][j+1].r + arr[i-1][j+2].r + 
                            arr[i][j-2].r + arr[i][j-1].r + arr[i][j].r + arr[i][j+1].r + arr[i][j+2].r +  
                            arr[i+1][j-2].r + arr[i+1][j-1].r + arr[i+1][j].r + arr[i+1][j+1].r + arr[i+1][j+2].r + 
                            arr[i+2][j-2].r + arr[i+2][j-1].r + arr[i+2][j].r + arr[i+2][j+1].r + arr[i+2][j+2].r)/25;
                        arr[i][j].r = average_r;
                        

                        int average_g = (arr[i-2][j-2].g + arr[i-2][j-1].g + arr[i-2][j].g + arr[i-2][j+1].g + arr[i-2][j+2].g +
                                    arr[i-1][j-2].g + arr[i-1][j-1].g + arr[i-1][j].g + arr[i-1][j+1].g + arr[i-1][j+2].g + 
                                    arr[i][j-2].g + arr[i][j-1].g + arr[i][j].g + arr[i][j+1].g + arr[i][j+2].g +  
                                    arr[i+1][j-2].g + arr[i+1][j-1].g + arr[i+1][j].g + arr[i+1][j+1].g + arr[i+1][j+2].g + 
                                    arr[i+2][j-2].g + arr[i+2][j-1].g + arr[i+2][j].g + arr[i+2][j+1].g + arr[i+2][j+2].g)/25; 
                        arr[i][j].g = average_g;


                        int average_b = (arr[i-2][j-2].b + arr[i-2][j-1].b + arr[i-2][j].b + arr[i-2][j+1].b + arr[i-2][j+2].b +
                                    arr[i-1][j-2].b + arr[i-1][j-1].b + arr[i-1][j].b + arr[i-1][j+1].b + arr[i-1][j+2].b + 
                                    arr[i][j-2].b + arr[i][j-1].b + arr[i][j].b + arr[i][j+1].b + arr[i][j+2].b +  
                                    arr[i+1][j-2].b + arr[i+1][j-1].b + arr[i+1][j].b + arr[i+1][j+1].b + arr[i+1][j+2].b + 
                                    arr[i+2][j-2].b + arr[i+2][j-1].b + arr[i+2][j].b + arr[i+2][j+1].b + arr[i+2][j+2].b)/25; 
                        arr[i][j].b = average_b;
                    }
                    
                }
            }

            for(int i = 0; i < width-2; i++){
                int average_r = (arr[0][i].r + arr[0][i+1].r + arr[0][i+2].r + arr[0][i-1].r + arr[0][i-2].r +
                            arr[1][i].r + arr[1][i+1].r + arr[1][i-1].r + arr[1][i-2].r + arr[1][i+2].r + 
                            arr[2][i].r + arr[2][i+1].r + arr[2][i-1].r + arr[2][i-2].r + arr[2][i+2].r)/15;
 
                arr[0][i].r = average_r;

                int average_g = (arr[0][i].g + arr[0][i+1].g + arr[0][i+2].g + arr[0][i-1].g + arr[0][i-2].g +
                            arr[1][i].g + arr[1][i+1].g + arr[1][i-1].g + arr[1][i-2].g + arr[1][i+2].g + 
                            arr[2][i].g + arr[2][i+1].g + arr[2][i-1].g + arr[2][i-2].g + arr[2][i+2].g)/15;
 
                arr[0][i].g = average_g;

                int average_b = (arr[0][i].b + arr[0][i+1].b + arr[0][i+2].b + arr[0][i-1].b + arr[0][i-2].b +
                            arr[1][i].b + arr[1][i+1].b + arr[1][i-1].b + arr[1][i-2].b + arr[1][i+2].b + 
                            arr[2][i].b + arr[2][i+1].b + arr[2][i-1].b + arr[2][i-2].b + arr[2][i+2].b)/15;
 
                arr[0][i].b = average_b;


                int average_r2 = (arr[3][i].r + arr[3][i+1].r + arr[3][i+2].r + arr[3][i-1].r + arr[3][i-2].r +
                            arr[0][i].r + arr[0][i+1].r + arr[0][i+2].r + arr[0][i-1].r + arr[0][i-2].r +
                            arr[1][i].r + arr[1][i+1].r + arr[1][i-1].r + arr[1][i-2].r + arr[1][i+2].r + 
                            arr[2][i].r + arr[2][i+1].r + arr[2][i-1].r + arr[2][i-2].r + arr[2][i+2].r)/20;
 
                arr[1][i].r = average_r2;

                int average_g2 = (arr[3][i].g + arr[3][i+1].g + arr[3][i+2].g + arr[3][i-1].g + arr[3][i-2].g +
                            arr[0][i].g + arr[0][i+1].g + arr[0][i+2].g + arr[0][i-1].g + arr[0][i-2].g +
                            arr[1][i].g + arr[1][i+1].g + arr[1][i-1].g + arr[1][i-2].g + arr[1][i+2].g + 
                            arr[2][i].g + arr[2][i+1].g + arr[2][i-1].g + arr[2][i-2].g + arr[2][i+2].g)/20;
 
                arr[1][i].g = average_g2;

                int average_b2 = (arr[3][i].b + arr[3][i+1].b + arr[3][i+2].b + arr[3][i-1].b + arr[3][i-2].b +
                            arr[0][i].b + arr[0][i+1].b + arr[0][i+2].b + arr[0][i-1].b + arr[0][i-2].b +
                            arr[1][i].b + arr[1][i+1].b + arr[1][i-1].b + arr[1][i-2].b + arr[1][i+2].b + 
                            arr[2][i].b + arr[2][i+1].b + arr[2][i-1].b + arr[2][i-2].b + arr[2][i+2].b)/20;
 
                arr[1][i].b = average_b2;


                int average_r3 = (arr[height-1][i].r + arr[height-1][i+1].r + arr[height-1][i+2].r + arr[height-1][i-1].r + arr[height-1][i-2].r +
                            arr[height-2][i].r + arr[height-2][i+1].r + arr[height-2][i-1].r + arr[height-2][i-2].r + arr[height-2][i+2].r + 
                            arr[height-3][i].r + arr[height-3][i+1].r + arr[height-3][i-1].r + arr[height-3][i-2].r + arr[height-3][i+2].r)/15;
 
                arr[height-1][i].r = average_r3;

                int average_g3 = (arr[height-1][i].g + arr[height-1][i+1].g + arr[height-1][i+2].g + arr[height-1][i-1].g + arr[height-1][i-2].g +
                            arr[height-2][i].g + arr[height-2][i+1].g + arr[height-2][i-1].g + arr[height-2][i-2].g + arr[height-2][i+2].g + 
                            arr[height-3][i].g + arr[height-3][i+1].g + arr[height-3][i-1].g + arr[height-3][i-2].g + arr[height-3][i+2].g)/15;
 
                arr[height-1][i].g = average_g3;

                int average_b3 = (arr[height-1][i].b + arr[height-1][i+1].b + arr[height-1][i+2].b + arr[height-1][i-1].b + arr[height-1][i-2].b +
                            arr[height-2][i].b + arr[height-2][i+1].b + arr[height-2][i-1].b + arr[height-2][i-2].b + arr[height-2][i+2].b + 
                            arr[height-3][i].b + arr[height-3][i+1].b + arr[height-3][i-1].b + arr[height-3][i-2].b + arr[height-3][i+2].b)/15;
 
                arr[height-1][i].b = average_b3;


                int average_r4 = (arr[height-4][i].r + arr[height-4][i+1].r + arr[height-4][i+2].r + arr[height-4][i-1].r + arr[height-4][i-2].r +
                            arr[height-1][i].r + arr[height-1][i+1].r + arr[height-1][i+2].r + arr[height-1][i-1].r + arr[height-1][i-2].r +
                            arr[height-2][i].r + arr[height-2][i+1].r + arr[height-2][i-1].r + arr[height-2][i-2].r + arr[height-2][i+2].r + 
                            arr[height-3][i].r + arr[height-3][i+1].r + arr[height-3][i-1].r + arr[height-3][i-2].r + arr[height-3][i+2].r)/20;
 
                arr[height-2][i].r = average_r4;

                int average_g4 = (arr[height-4][i].g + arr[height-4][i+1].g + arr[height-4][i+2].g + arr[height-4][i-1].g + arr[height-4][i-2].g +
                            arr[height-1][i].g + arr[height-1][i+1].g + arr[height-1][i+2].g + arr[height-1][i-1].g + arr[height-1][i-2].g +
                            arr[height-2][i].g + arr[height-2][i+1].g + arr[height-2][i-1].g + arr[height-2][i-2].g + arr[height-2][i+2].g + 
                            arr[height-3][i].g + arr[height-3][i+1].g + arr[height-3][i-1].g + arr[height-3][i-2].g + arr[height-3][i+2].g)/20;
 
                arr[height-2][i].g = average_g4;

                int average_b4 = (arr[height-4][i].b + arr[height-4][i+1].b + arr[height-4][i+2].b + arr[height-4][i-1].b + arr[height-4][i-2].b +
                            arr[height-1][i].b + arr[height-1][i+1].b + arr[height-1][i+2].b + arr[height-1][i-1].b + arr[height-1][i-2].b +
                            arr[height-2][i].b + arr[height-2][i+1].b + arr[height-2][i-1].b + arr[height-2][i-2].b + arr[height-2][i+2].b + 
                            arr[height-3][i].b + arr[height-3][i+1].b + arr[height-3][i-1].b + arr[height-3][i-2].b + arr[height-3][i+2].b)/20;
 
                arr[height-2][i].b = average_b4;

            }

            blur--; 
        }
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                temp[i][j] = arr[i][j];
            }
        }
        
        print_pixel_array(name, width, height, temp);
        free_matrix(height, temp); 
    } 

    free_matrix(height, arr);
}

void duck_filter(char *filename, char *name){

    /*

        THIS FUNCTION FILTERS EACH PICTURE WITH THE UNIVERSITY OF OREGON DUCK COLORS

    */
    
    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    pixel **arr = readBMP(filename);

    if(height<0)
    {
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
    }

    pixel **temp = create_blank_array(width, height);

    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r = arr[i][j].r;
            int g = arr[i][j].g;
            int b = arr[i][j].b;

            if((r + g + b) >= 256)
            {
                temp[i][j].r = 243; 
                temp[i][j].g = 243;
                temp[i][j].b = 40;
            }
            else
            {
                temp[i][j].r = 12;
                temp[i][j].g = 75;
                temp[i][j].b = 36;
            }
        }
    }
    print_pixel_array(name, (width),(height), temp);
    free_matrix(height, arr);
    free_matrix(height, temp);
}

void double_vision_filter(char* filename, char *name, const char *orientation){
    // ---------------------------------------------------------------------------
    // Function: Writes a copy of the input .bmp in double-vision stored as a .pbm 
    // Arguments: Takes the name of the input image and name of the output image.
    // Returns: Void function that creates a new .pbm file in your directory
    // ---------------------------------------------------------------------------

    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    pixel **arr = readBMP(filename); 

    if(height<0){

        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
        exit(EXIT_FAILURE);
    }

    if(strcmp(orientation, "horizontal") == 0){
        width = width * 2;
        pixel **temp = create_blank_array(width, height, 130, 170, 50);

        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width/2; j++)
            {
                //Calculation for inversion.
                temp[i][j].r = arr[i][j].r;
                temp[i][j].g = arr[i][j].g;
                temp[i][j].b = arr[i][j].b;      
            }

            for(int k = width/2; k < width; k++)
            {
                //Calculation for inversion.
                temp[i][k].r = arr[i][k-(width/2)].r;
                temp[i][k].g = arr[i][k-(width/2)].g;
                temp[i][k].b = arr[i][k-(width/2)].b;      
            }
        }
        print_pixel_array(name, width, height, temp);
    }
    else if(strcmp(orientation, "vertical") == 0){
        height = height * 2;
        pixel **temp = create_blank_array(width, height, 130, 170, 50);

        for(int i = 0; i < height/2; i++)
        {
            for(int j = 0; j < width; j++)
            {
                //Calculation for inversion.
                temp[i][j].r = arr[i][j].r;
                temp[i][j].g = arr[i][j].g;
                temp[i][j].b = arr[i][j].b;      
            }
        }

        for(int k = height/2; k < height; k++){
            for(int m = 0; m < width; m++)
            {
                //Calculation for inversion.
                temp[k][m].r = arr[k-height/2][m].r;
                temp[k][m].g = arr[k-height/2][m].g;
                temp[k][m].b = arr[k-height/2][m].b;    
            }

        } 
        print_pixel_array(name, width, height, temp);
        free_matrix(height, arr);
        free_matrix(height, temp);
    }
    else{
        cout << "Not a valid orientation" << endl; 
    }      
}

void popart_filter(char *filename, char *name){

    /*

        THIS FUNCTION FILTERS EACH PICTURE WITH THE POPART FILTER

    */
    
    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    //initialize arrays
    pixel **arr = readBMP(filename);

    pixel **red = new pixel *[height];
    for (int i = 0; i < height; ++i) {
        red[i] = new pixel[width];
    }
    pixel **yellow = new pixel*[height];
    for (int i = 0; i < height; ++i) {
        yellow[i] = new pixel[width];
    }
    pixel **blue = new pixel*[height];
    for (int i = 0; i < height; ++i) {
        blue[i] = new pixel[width];
    }
    pixel **green = new pixel*[height];
    for (int i = 0; i < height; ++i) {
        green[i] = new pixel[width];
    }

    if(height<0){
        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
    }


    //int redpix, bluepix, greenpix; 

    // Change each box to have the a tint
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            /*
                CHANGES THE RED ARRAY TO HAVE A RED TINT
            */
            int pix = (int)(((arr[i][j].r + arr[i][j].g + arr[i][j].b)/3)+0.5);
            if(pix < 51)
            {
                red[i][j].r = 13;
                red[i][j].g = 29;
                red[i][j].b = 128;
            }
            else if(pix <= 51 && pix < 102)
            {
                red[i][j].r = 231;
                red[i][j].g = 88;
                red[i][j].b = 51;
            }
            else if(pix <= 102 && pix < 153)
            {
                red[i][j].r = 192;
                red[i][j].g = 159;
                red[i][j].b = 219;
            }
            else if(pix <= 153 && pix < 204)
            {
                red[i][j].r = 115;
                red[i][j].g = 218;
                red[i][j].b = 229;
            }
            else
            {
                red[i][j].r = 232;
                red[i][j].g = 235;
                red[i][j].b = 85;
            }

            /*
                CHANGES THE BLUE ARRAY TO HAVE A BLUE TINT
            */


             if(pix < 51)
            {
                blue[i][j].r = 130;
                blue[i][j].g = 19;
                blue[i][j].b = 63;
            }
            else if(pix <= 51 && pix < 102)
            {
                blue[i][j].r = 170;
                blue[i][j].g = 44;
                blue[i][j].b = 141;
            }
            else if(pix <= 102 && pix < 153)
            {
                blue[i][j].r = 192;
                blue[i][j].g = 137;
                blue[i][j].b = 201;
            }
            else if(pix <= 153 && pix < 204)
            {
                blue[i][j].r = 233;
                blue[i][j].g = 185;
                blue[i][j].b = 241;
            }
            else
            {
                blue[i][j].r = 232;
                blue[i][j].g = 235;
                blue[i][j].b = 85;
            }

            /*
                CHANGES THE GREEN ARRAY TO HAVE A GREEN TINT
            */

             if(pix < 51)
            {
                green[i][j].r = 5;
                green[i][j].g = 59;
                green[i][j].b = 16;
            }
            else if(pix <= 51 && pix < 102)
            {
                green[i][j].r = 158;
                green[i][j].g = 123;
                green[i][j].b = 196;
            }
            else if(pix <= 102 && pix < 153)
            {
                green[i][j].r = 248;
                green[i][j].g = 173;
                green[i][j].b = 0;
            }
            else if(pix <= 153 && pix < 204)
            {
                green[i][j].r = 147;
                green[i][j].g = 219;
                green[i][j].b = 59;
            }
            else
            {
                green[i][j].r = 213;
                green[i][j].g = 238;
                green[i][j].b = 70;
            }

            /*
                CHANGES THE YELLOW ARRAY TO HAVE A YELLOW TINT
            */

             if(pix < 51)
            {
                yellow[i][j].r = 0;
                yellow[i][j].g = 0;
                yellow[i][j].b = 0;
            }
            else if(pix <= 51 && pix < 102)
            {
                yellow[i][j].r = 231;
                yellow[i][j].g = 88;
                yellow[i][j].b = 51;
            }
            else if(pix <= 102 && pix < 153)
            {
                yellow[i][j].r = 65;
                yellow[i][j].g = 161;
                yellow[i][j].b = 230;
            }
            else if(pix <= 153 && pix < 204)
            {
                yellow[i][j].r = 242;
                yellow[i][j].g = 195;
                yellow[i][j].b = 75;
            }
            else
            {
                yellow[i][j].r = 106;
                yellow[i][j].g = 213;
                yellow[i][j].b = 235;
            }
        }
    }

    pixel **temp = create_blank_array((width*2),(height*2), 255, 255, 255);

    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
                temp[i][j].r = red[i][j].r;
                temp[i][j].g = red[i][j].g;
                temp[i][j].b = red[i][j].b;
        }
    }
    for(int i = height; i < (height*2); i++)
    {
        for (int j = 0; j < width; j++)
        {
                temp[i][j].r = green[i-height][j].r;
                temp[i][j].g = green[i-height][j].g;
                temp[i][j].b = green[i-height][j].b;
        }
    }
    for(int i = 0; i < height; i++)
    {
        for (int j = width; j < (width*2); j++)
        {
                temp[i][j].r = yellow[i][j-width].r;
                temp[i][j].g = yellow[i][j-width].g;
                temp[i][j].b = yellow[i][j-width].b;
        }
    }
    for(int i = height; i < (height*2); i++)
    {
        for (int j = width; j < (width*2); j++)
        {
                temp[i][j].r = blue[i-height][j-width].r;
                temp[i][j].g = blue[i-height][j-width].g;
                temp[i][j].b = blue[i-height][j-width].b;
        }
    }


    print_pixel_array(name, (width*2),(height *2), temp);
    free_matrix(height, arr);
    free_matrix(height, temp);
}

void thermal_filter(char* filename, char *name){

    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);
 
    pixel **arr = readBMP(filename);
    if(height<0)
    {
        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
        exit (EXIT_FAILURE);
    }

    pixel **temp = create_blank_array(width, height);
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int pix = (int)(((arr[i][j].r + arr[i][j].g + arr[i][j].b)/3)+0.5);
            if(pix < 25)
            {
                temp[i][j].r = 15;
                temp[i][j].g = 39;
                temp[i][j].b = 122;
            }
            else if(pix <= 25 && pix < 50)
            {
                temp[i][j].r = 29;
                temp[i][j].g = 84;
                temp[i][j].b = 193;
            }
            else if(pix <= 50 && pix < 75)
            {
                temp[i][j].r = 23;
                temp[i][j].g = 196;
                temp[i][j].b = 207;
            }
            else if(pix <= 75 && pix < 100)
            {
                temp[i][j].r = 14;
                temp[i][j].g = 132;
                temp[i][j].b = 17;
            }
            else if(pix <= 100 && pix < 125)
            {
                temp[i][j].r = 195;
                temp[i][j].g = 255;
                temp[i][j].b = 6;
            }
            else if(pix <= 125 && pix < 150)
            {
                temp[i][j].r = 255;
                temp[i][j].g = 251;
                temp[i][j].b = 6;
               
            }
            else if(pix <= 150 && pix < 175)
            {
                temp[i][j].r = 255;
                temp[i][j].g = 209;
                temp[i][j].b = 0;
            }
            else if(pix <= 175 && pix < 200)
            {
                temp[i][j].r = 255;
                temp[i][j].g = 108;
                temp[i][j].b = 0;
            }
            else if(pix <= 200 && pix < 225)
            {
                temp[i][j].r = 255;
                temp[i][j].g = 0;
                temp[i][j].b = 0;
            }
            else if(pix <= 225 && pix < 250)
            {
                temp[i][j].r = 255;
                temp[i][j].g = 71;
                temp[i][j].b = 160;
            }
            else
            {
                temp[i][j].r = 255;
                temp[i][j].g = 237;
                temp[i][j].b = 246;
            }
        }
    }
    print_pixel_array(name, width, height, temp);
    free_matrix(height, arr);
    free_matrix(height, temp);
}

void checkers_filter(char* filename, char *name, int box, int type){

    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);
 
    pixel **arr = readBMP(filename);

    if(height<0){

        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
    }
    if(box > width || box > height)
    {
        cout << "Please enter a smaller number of checkers" << endl;
    }

    int wsize = width / box;
    int hsize = height /box;
    
    int darkpix, lightpix;
    // int countw = 0;
    int counth = 0;
    // int sww = 1;
    int swh = 1;

    pixel **temp = create_blank_array(width, height);

    for(int i = 0; i < height; i++)
    {
        int m = 0;
        int sw = 1;
        if(swh == 1){
            for (int j = 0; j < width; j++)
            {
                if(m == wsize)
                {
                    sw = sw * (-1);
                    m = 0;
                }
                if(sw == 1)
                {
                    if(type != 2)
                    {
                        temp[i][j].r = arr[i][j].r;
                        temp[i][j].g = arr[i][j].g;
                        temp[i][j].b = arr[i][j].b;
                    }
                    else
                    {
                        lightpix = arr[i][j].r;
                        lightpix = pix_range_input(lightpix, 50);
                        temp[i][j].r = lightpix;

                        lightpix = arr[i][j].g;
                        lightpix = pix_range_input(lightpix, 50);
                        temp[i][j].g = lightpix;

                        lightpix = arr[i][j].b;
                        lightpix = pix_range_input(lightpix, 50);
                        temp[i][j].b = lightpix;
                    }
                   
                }
                else if (sw == -1)
                {
                    // Normal checkers with black
                    if(type == 0)
                    {
                        temp[i][j].r = 0;
                        temp[i][j].g = 0;
                        temp[i][j].b = 0;
                    }
                    // Inverse checkers
                    else if(type == 1)
                    {
                        temp[i][j].r = 255-arr[i][j].r;
                        temp[i][j].g = 255-arr[i][j].g;
                        temp[i][j].b = 255-arr[i][j].b;
                    }
                    // Darker Pixel checkers
                    else if(type == 2)
                    {
                        darkpix = arr[i][j].r;
                        darkpix = pix_range_input(darkpix, -50);
                        temp[i][j].r = darkpix;

                        darkpix = arr[i][j].g;
                        darkpix = pix_range_input(darkpix, -50);
                        temp[i][j].g = darkpix;

                        darkpix = arr[i][j].b;
                        darkpix = pix_range_input(darkpix, -50);
                        temp[i][j].b = darkpix;
                    }
                    //Normal Checker but with the light pixels in white
                    else if(type == 3)
                    {
                        int pix = (int)(((arr[i][j].r + arr[i][j].g + arr[i][j].b)/3)+0.5);
                        if(pix <= 110)
                        {
                            temp[i][j].r = 0;
                            temp[i][j].g = 0;
                            temp[i][j].b = 0;
                        }
                        else
                        {
                            temp[i][j].r = 255;
                            temp[i][j].g = 255;
                            temp[i][j].b = 255;
                        }
                    }
                    
                }

                m += 1;
                
            }   
        }
        if(swh == -1)
        {
            for(int j = 0; j < width; j++)
            {
                if(m == wsize)
                {
                    sw = sw * -1;
                    m = 0;
                }

                if(sw == 1)
                {
                   // Normal checkers with black
                    if(type == 0)
                    {
                        temp[i][j].r = 0;
                        temp[i][j].g = 0;
                        temp[i][j].b = 0;
                    }
                    // Inverse checkers
                    else if(type == 1)
                    {
                        temp[i][j].r = 255-arr[i][j].r;
                        temp[i][j].g = 255-arr[i][j].g;
                        temp[i][j].b = 255-arr[i][j].b;
                    }
                    // Darker Pixel checkers
                    else if(type == 2)
                    {
                        darkpix = arr[i][j].r;
                        darkpix = pix_range_input(darkpix, -50);
                        temp[i][j].r = darkpix;

                        darkpix = arr[i][j].g;
                        darkpix = pix_range_input(darkpix, -50);
                        temp[i][j].g = darkpix;

                        darkpix = arr[i][j].b;
                        darkpix = pix_range_input(darkpix, -50);
                        temp[i][j].b = darkpix;
                    }
                    // Normal checkers but with the light pixels in white
                    else if(type == 3)
                    {
                        int pix = (int)(((arr[i][j].r + arr[i][j].g + arr[i][j].b)/3)+0.5);
                        if(pix <= 110)
                        {
                            temp[i][j].r = 0;
                            temp[i][j].g = 0;
                            temp[i][j].b = 0;
                        }
                        else
                        {
                            temp[i][j].r = 255;
                            temp[i][j].g = 255;
                            temp[i][j].b = 255;
                        }
                    }
                }
                if(sw == -1)
                {
                   if(type != 2)
                    {
                        temp[i][j].r = arr[i][j].r;
                        temp[i][j].g = arr[i][j].g;
                        temp[i][j].b = arr[i][j].b;
                    }
                    else
                    {
                        lightpix = arr[i][j].r;
                        lightpix = pix_range_input(lightpix, 50);
                        temp[i][j].r = lightpix;

                        lightpix = arr[i][j].g;
                        lightpix = pix_range_input(lightpix, 50);
                        temp[i][j].g = lightpix;

                        lightpix = arr[i][j].b;
                        lightpix = pix_range_input(lightpix, 50);
                        temp[i][j].b = lightpix;
                    }

                }
                m += 1;
            }
        }
        counth += 1;
        if(counth == hsize)
        {
            counth = 0;
            swh = swh * -1;
        }
        
    }
    print_pixel_array(name, width, height, temp);
    free_matrix(height, arr);
    free_matrix(height, temp);
}

void static_filter(char *filename, char *name){

    /*

        THIS FUNCTION FILTERS EACH PICTURE WITH THE STATIC FILTER:

            *THE ROWS ALTERNATE BETWEEN RED, GREEN, AND BLUE, GIVING
            IT A STATIC EFFECT*

    */
    
    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    if(height<0){
        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
    }
    pixel **arr = readBMP(filename);
    pixel **temp = create_blank_array((width),(height), 255, 255, 255);

    int greenpix, redpix, bluepix;
    for(int i = 1; i <= height; i++)
    {
        int row = i % 3; // one rows for each color
        for(int j = 0; j < width; j++)
        {
            if(row == 1)
            {
                redpix = pix_range(int(0 * arr[i - 1][j].r));
                greenpix = pix_range(int(1.5 * arr[i - 1][j].g));
                bluepix = pix_range(int(0 * arr[i - 1][j].b));

                temp[i - 1][j].r = redpix;
                temp[i - 1][j].g = greenpix;
                temp[i - 1][j].b = bluepix;
            }
            else if(row == 2)
            {
                redpix = pix_range(int(1.5 * arr[i - 1][j].r));
                greenpix = pix_range(int(0.0 * arr[i - 1][j].g));
                bluepix = pix_range(int(0 * arr[i - 1][j].b));

                temp[i - 1][j].r = redpix;
                temp[i - 1][j].g = greenpix;
                temp[i - 1][j].b = bluepix;
            }
            else if(row == 0)
            {
                redpix = pix_range(int(0 * arr[i - 1][j].r));
                greenpix = pix_range(int(0.0 * arr[i - 1][j].g));
                bluepix = pix_range(int(1.5 * arr[i - 1][j].b));

                temp[i - 1][j].r = redpix;
                temp[i - 1][j].g = greenpix;
                temp[i - 1][j].b = bluepix;
            }

        }
    }

    print_pixel_array(name, (width),(height), temp);
    free_matrix(height, arr);
    free_matrix(height, temp);
}

void fast_filter(char *filename, char *name, int type){

    /*

        THIS FUNCTION EDITS MOST PIXELS IN FOCUS AND THE REST IS A SPEED EFFECT

    */
    
    int width = get_BMP_width(filename);
    int height = get_BMP_height(filename);

    //initialize arrays
    pixel **arr = readBMP(filename);


    if(height<0){
        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
    }

    int half = int(width / 2);
    pixel **temp = create_blank_array((width),(height), 255, 255, 255);

    // Change each box to have the a tint
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            /* Whatever is in focus is black and white, speed is in color */
            if(type == 4)
            {
                int pix = (int)(((arr[i][j].r + arr[i][j].g + arr[i][j].b)/3)+0.5);
                if(pix > 110)
                {
                    temp[i][j].r = pix;
                    temp[i][j].g = pix;
                    temp[i][j].b = pix;
                }
                else
                {
                    temp[i][j].r = arr[i][half].r;
                    temp[i][j].g = arr[i][half].g;
                    temp[i][j].b = arr[i][half].b;
                }

            }
            /* Focus is in color, other is B&W */
            else if(type == 3)
            {
                int pix = (int)(((arr[i][j].r + arr[i][j].g + arr[i][j].b)/3)+0.5);
                if(pix > 110)
                {
                    temp[i][j].r = arr[i][j].r;
                    temp[i][j].g = arr[i][j].g;
                    temp[i][j].b = arr[i][j].b;
                }
                else
                {
                    pix = (int)(((arr[i][half].r + arr[i][half].g + arr[i][half].b)/3)+0.5);
                    temp[i][j].r = pix;
                    temp[i][j].g = pix;
                    temp[i][j].b = pix;
                }

            }
             /* all in color */
            else if(type == 2)
            {
                int pix = (int)(((arr[i][j].r + arr[i][j].g + arr[i][j].b)/3)+0.5);
                if(pix > 110)
                {
                    temp[i][j].r = arr[i][j].r;
                    temp[i][j].g = arr[i][j].g;
                    temp[i][j].b = arr[i][j].b;
                }
                else
                {
                    temp[i][j].r = arr[i][half].r;
                    temp[i][j].g = arr[i][half].g;
                    temp[i][j].b = arr[i][half].b;        
                }

            }
            /* All in Grayscale*/
            else if(type == 1)
            {
                int pix = (int)(((arr[i][j].r + arr[i][j].g + arr[i][j].b)/3)+0.5);
                if(pix > 110)
                {
                    temp[i][j].r = pix;
                    temp[i][j].g = pix;
                    temp[i][j].b = pix;
                }
                else
                {
                    pix = (int)(((arr[i][half].r + arr[i][half].g + arr[i][half].b)/3)+0.5);
                    temp[i][j].r = pix;
                    temp[i][j].g = pix;
                    temp[i][j].b = pix;       
                }

            }
     
        }
            
    }

    print_pixel_array(name, (width),(height), temp);
    free_matrix(height, arr);
    free_matrix(height, temp);
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
