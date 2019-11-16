#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cstring>
#include <map>
#include "./hdrs/IO.hh"
#include "./hdrs/matrix.hh"
#include "./hdrs/filter.hh"

using namespace std; 

// IO Functions 
char *to_txt(char *name){
    int m = strlen(name);
    char *modified_name = new char[m+1];
    strcpy(modified_name, name);

    modified_name[m-1] = 't';
    modified_name[m-2] = 'x';
    modified_name[m-3] = 't';
    modified_name[m-4] = '.';

    return modified_name;
}

char *to_pbm(char *name){
    int m = strlen(name);
    char *modified_name = new char[m+1];
    strcpy(modified_name, name);

    modified_name[m-1] = 'm';
    modified_name[m-2] = 'b';
    modified_name[m-3] = 'p';
    modified_name[m-4] = '.';

    return modified_name;
}

pixel **read_exported_PBM(char* filename){

    int convert_to_text;

    char *oldname = filename;
    char *newname = to_txt(filename);

    convert_to_text = rename(oldname,newname);
    if (convert_to_text != 0)
    {
        perror( "ERROR: Unable to rename file" );
        convert_to_text = rename(newname,oldname);
    }

    ifstream f;
    f.open(newname);
    string first;

    int width,height,a,b,c;
    // int data;

    if(f.is_open()==false)
    {
        cout<<"ERROR: File not opened"<<endl;
        exit(0);
    }

    f>>first;
    f>>width;
    f>>height;
    f>>a;

    pixel **arr = new pixel*[height];

    for (int i = 0; i < height; ++i) {
        arr[i] = new pixel[width];
    }

    for(int i = 0; i < height; i++) // Iterates through height of the image.
    {
        int k = 0;  // Variable that stores data in correct index of the pixel array.

        for(int j = 0; j < width*3; j += 3) // Skips 3 pixel ints at a time (R/G/B). 
        { // Iterates through width of the image.
            f>>a>>b>>c;

            arr[i][k].r=a;
            arr[i][k].g=b;
            arr[i][k].b=c;

            k++;
        }
    }

    // prints the contents
    /*
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
        cout<<arr[i][j].r<<" "<<arr[i][j].g<<" "<<arr[i][j].b<<" ";
        }
        cout<<"\n";
    }
    */

    int result_old;
    result_old = rename(newname,oldname);
    
    if(result_old != 0)
    {
        perror("ERROR: Unable to rename file");
    }
    
    return arr;
}

pixel **readBMP(char* filename){
    // -------------------------------------------------------------
    // Function: Reads .bmp file's R/G/B data into a 2D pixel array
    // Arguments: Name of the .bmp file.
    // Returns: 2D pixel array of R/G/B integers.
    // -------------------------------------------------------------

    FILE* f = fopen(filename, "rb"); // Reads binary file (rb) of .bmp file

    if(f == NULL)
        throw "Argument Exception";

    unsigned char buffer[54]; // Creates a buffer for header.

    // Reads the 54-byte header specific to .bmp images:
    fread(buffer, sizeof(unsigned char), 54, f);

    // Extracts image height and width from header.
    int width = *(int*)&buffer[18];
    int height = *(int*)&buffer[22];

    // prints Name/Width/Height data from header.
    cout << endl;
    cout << "Name: " << filename << endl;
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;

    // Attempting to fix potential negative height problem...
    if(height<0){
        height = height * -1;
    }

    //pixel numbers[height][width];
    pixel **numbers = new pixel*[height];
    for (int i = 0; i < height; ++i) {
        numbers[i] = new pixel[width];
    }

    int padding = (width*3 + 3) & (~3);
    unsigned char* img_code = new unsigned char[padding];
    unsigned char tmp; // Temporary variable for swapping

    for (int i = height-1; i > -1; i--)    
    {
        fread(img_code, sizeof(unsigned char), padding, f); // Reads image until padding.

        int k = 0; // Variable that stores data in correct index of the pixel array.

        for(int j = 0; j < width*3; j += 3) // Skips 3 pixel ints at a time (R/G/B). 
        {
            // Re-orders B/G/R information into R/G/B information.

            tmp = img_code[j];
            img_code[j] = img_code[j+2];
            img_code[j+2] = tmp;

            // Debugging information to print each pixel and its row/column:
            // cout << "R: "<< (int)data[j] << " G: " << (int)data[j+1]<< " B: " << (int)data[j+2] << endl;
            // cout << "\ti = " << i << "\tk = " << k <<endl;
            
            numbers[i][k].r = (int)img_code[j];     // Adds red value to struct
            numbers[i][k].g = (int)img_code[j+1];   // Adds green value to struct
            numbers[i][k].b = (int)img_code[j+2];   // Adds blue value to struct

            k++;
        }
    }

    fclose(f); // Closes file

    return numbers; // Returns the 2D pixel array of pixel data
}

int check_if_BMP(char *name){
    int m = strlen(name);
    char *modified_name = new char[m+1];
    strcpy(modified_name, name);

    if(modified_name[m-1] == 'p' && modified_name[m-2] == 'm' && modified_name[m-3] == 'b' && modified_name[m-4] == '.')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int check_if_PBM(char *name){
    int m = strlen(name);
    char *modified_name = new char[m+1];
    strcpy(modified_name, name);

    if(modified_name[m-1] == 'm' && modified_name[m-2] == 'b' && modified_name[m-3] == 'p' && modified_name[m-4] == '.')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int get_PBM_width(char *filename){
    int convert_to_text;

    char *oldname = filename;
    char *newname = to_txt(filename);

    convert_to_text = rename(oldname,newname);
    if (convert_to_text != 0)
    {
        perror( "ERROR: Unable to rename file" );
        convert_to_text = rename(newname,oldname);
    }

    ifstream f;
    f.open(newname);
    string first;

    int width;
    //int height,data,a,b,c;

    if(f.is_open()==false)
    {
        cout<<"ERROR: File not opened"<<endl;
        exit(0);
    }

    f>>first;
    f>>width;

    int result_old;
    result_old = rename(newname,oldname);

    return (int)width;
}

int get_PBM_height(char *filename){
    int convert_to_text;

    char *oldname = filename;
    char *newname = to_txt(filename);

    convert_to_text = rename(oldname,newname);
    if (convert_to_text != 0)
    {
        perror( "ERROR: Unable to rename file" );
        convert_to_text = rename(newname,oldname);
    }

    ifstream f;
    f.open(newname);
    string first;

    int width, height;
    // ,data,a,b,c;

    if(f.is_open()==false)
    {
        cout<<"ERROR: File not opened"<<endl;
        exit(0);
    }

    f>>first;
    f>>width;
    f>>height;

    int result_old;
    result_old = rename(newname,oldname);

    return (int)height;
}

int get_BMP_width(char* filename){
    // ----------------------------------------
    // Function: Gets width of .bmp image.
    // Arguments: Name of the .bmp file.
    // Returns: int value of the image width.
    // ----------------------------------------

    FILE* f = fopen(filename, "rb");

    if(f == NULL)
        throw "Argument Exception";

    unsigned char buffer[54]; // Creates a buffer for header.

    // Reads the 54-byte header specific to .bmp images:
    fread(buffer, sizeof(unsigned char), 54, f);

    // extract image height and width from header:
    int w = *(int*)&buffer[18];

    fclose(f);

    return w;
}

int get_BMP_height(char* filename){
    // ----------------------------------------
    // Function: Gets height of .bmp image.
    // Arguments: Name of the .bmp file.
    // Returns: int value of the image height.
    // ----------------------------------------

    FILE* f = fopen(filename, "rb");

    if(f == NULL)
        throw "Argument Exception";

    unsigned char buffer[54]; // Creates a buffer for header.

    // Reads the 54-byte header specific to .bmp images:
    fread(buffer, sizeof(unsigned char), 54, f);

    // extract image height and width from header:
    int h = *(int*)&buffer[22];
    
    fclose(f);

    return h;   
}

void write_PBM_image(char* filename, char *name){
    // ---------------------------------------------------------------------------
    // Function: Writes a copy of the input .bmp file to your drectory as a .pbm
    // Arguments: Takes the name of the input image and name of the output image.
    // Returns: Void function that creates a new .pbm file in your directory
    // ---------------------------------------------------------------------------

    int width = get_BMP_width(filename);     // Gets the width of .bmp file
    int height = get_BMP_height(filename);   // Gets the height of .bmp file

    pixel **arr = readBMP(filename); // Stores pixel information from the .bmp file into a new 2D pixel array.

    if(height<0){
    // Some .bmp images are loaded with a negative height value. We haven't found a consistent way to fix
    // this yet, but until then, we throw an error message if the image isn't positive.  

        cout << "----------------\n";
        cout << "ERROR: .bmp image has a negative height value of " << height << endl;
    }

    else{
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
                    f << arr[i][j].r << " " << arr[i][j].g << " " << arr[i][j].b;
                }

                else{
                // Writes the r/g/b data from the 2D pixel struct array into the file.
                // This format seperates each values by a single space.
                    f << arr[i][j].r << " " << arr[i][j].g << " " << arr[i][j].b << " ";
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
    free_matrix(height, arr);
}

void print_pixel_array(char *name, int width, int height, pixel **matrix){
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
                f << matrix[i][j].r << " " << matrix[i][j].g << " " << matrix[i][j].b;
            }
            else{
            // Writes the r/g/b data from the 2D pixel struct array into the file.
            // This format seperates each values by a single space.
                f << matrix[i][j].r << " " << matrix[i][j].g << " " << matrix[i][j].b << " ";
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
    f.close();
}

void b_test(char *filename, char *name, int width, int height){

    pixel **arr;

    if(check_if_PBM(filename) == 1)
    {
        width = get_PBM_width(filename);     // Gets the width of .bmp file
        height = get_PBM_height(filename);
        arr = read_exported_PBM(filename); // returns pixel array
    }
    else
    {
        width = get_BMP_width(filename);     // Gets the width of .bmp file
        height = get_BMP_height(filename);   // Gets the height of .bmp file
        arr = readBMP(filename); // Stores pixel information from the .bmp file into a new 2D pixel array.
    }

    pixel unique = unique_pixel(arr, width, height);
    
    pixel **ret_img = create_blank_array(width, height, unique.r, unique.g, unique.b);

    print_pixel_array(name, width, height, ret_img);    
}

void free_matrix(int height, pixel **matrix){
    for(int i = 0; i < height; i++){
        delete[] matrix[i];
    }
    delete[] matrix; 
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