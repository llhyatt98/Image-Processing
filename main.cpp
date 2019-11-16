#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include "hdrs/IO.hh"
#include "hdrs/filter.hh"
#include "hdrs/matrix.hh"

using namespace std;

int main()
{
    int choice; 
    char *input_file_name;
    char *output;

    char option;
    int again = 0;

    do
    {
        again = 0;
        cout << endl;
        cout << "Choose a photo:  " << endl << endl;
        cout << "tiger.bmp [1]  ~  rainier.bmp [2]" << endl; 
        cout << "ocean.bmp [3]  ~   road.bmp [4]" << endl;
        cout << "light.bmp [5]  ~   flower.bmp [6]" << endl;
        cout << endl << "            Quit [0]" << endl;
        cin >> choice;
        cout << endl;

        //Hidden built-in case for testing functions.
        if(choice == 99){
            output = (char *)"./output/blur.pbm";
            input_file_name = (char *)"./imgs/tiger.bmp";
            blur_filter(input_file_name, output, 5);
        }
        else{

            if(choice == 0)
            {
                return 0;
            }
            else if(choice == 1){
                input_file_name = (char *)"./imgs/tiger.bmp";
            }
            else if(choice == 2){
                input_file_name = (char *)"./imgs/Rainier.bmp";
            }
            else if(choice == 3){
                input_file_name = (char *)"./imgs/ocean.bmp";
            }
            else if(choice == 4){
                input_file_name = (char *)"./imgs/road.bmp";
            }
            else if(choice == 5){
                input_file_name = (char *)"./imgs/light.bmp";
            }
            else if(choice == 6){
                input_file_name = (char *)"./imgs/flower.bmp";
            }
            else if(choice == 7){
                input_file_name = (char *)"./imgs/mason.bmp";
            }
            else{
                cout << "Not a valid image." << endl;
                exit(EXIT_FAILURE); 
            }

            cout << "Choose your type of filter:" << endl << endl; 
            cout << "[1] Filters for changing pixel data" << endl;
            cout << "[2] Filters for changing orientation" << endl;
            cout << "[0] Quit"<< endl; 
            cin >> choice;
            cout << endl; 

            if(choice == 0)
            {
                return 0;
            }
            else if(choice == 1){
                cout << "Choose a filter to adjust pixel data:" << endl << endl; 
                cout << "[1] Greyscale                   [9] Go Ducks!" << endl;
                cout << "[2] Black and White             [10] Double Vision" << endl;
                cout << "[3] Photo Enhancement           [11] Pop Art" << endl;
                cout << "[4] Inversion                   [12] Thermal Vision " << endl;
                cout << "[5] Photo Enhancement           [13] checkers" << endl;
                cout << "[6] Antique                     [14] Static" << endl;
                cout << "[7] Blood                       [15] Speed" << endl;
                cout << "[8] Blur                        [0] Quit"  << endl;
                cin >> choice;
                cout << endl; 

                if(choice == 0)
                {
                    return 0;
                }
                else if(choice == 1){
                    output = (char *)"./output/greys.pbm";
                    greyscale_filter(input_file_name, output);
                }
                else if(choice == 2){
                    output = (char *)"./output/bandw.pbm";
                    black_white_filter(input_file_name, output);
                }
                else if(choice == 3){
                    output = (char *)"./output/RGB.pbm";
                    RGB_filter(input_file_name, output);
                }
                else if(choice == 4){
                    output = (char *)"./output/invert.pbm";
                    inverted_filter(input_file_name, output);
                }
                else if(choice == 5){
                    output = (char *)"./output/enhance.pbm";
                    enhance_filter(input_file_name, output);
                }
                else if(choice == 6){
                    output = (char *)"./output/antique.pbm";
                    antique_filter(input_file_name, output);
                }
                else if(choice == 7){
                    output = (char *)"./output/blood.pbm";
                    blood_filter(input_file_name, output);
                }
                else if(choice == 8){
                    int blur; 
                    cout << "Enter an integer amount to blur: ";
                    cin >> blur;
                    output = (char *)"./output/blur.pbm";
                    blur_filter(input_file_name, output, blur);
                }
                else if(choice == 9){
                    output = (char *)"./output/ducks.pbm";
                    duck_filter(input_file_name, output);
                }
                else if(choice == 10){
                    output = (char *)"./output/dubvision.pbm";
                    int style; 
                    cout << "Vertical [0] or Horizontal [1]?" << endl;
                    cin >> style;
                    if(style == 0){
                        const char *val = "vertical";
                        double_vision_filter(input_file_name, output, val);
                    }
                    else if(style == 1){
                        const char *val = "horizontal";
                        double_vision_filter(input_file_name, output, val);
                    }
                    else{
                        cout << "Not a valid orientation." << endl;
                    }
                    
                }
                else if(choice == 11){
                    output = (char *)"./output/popart.pbm";
                    popart_filter(input_file_name, output);
                }
                else if(choice == 12){
                    output = (char *)"./output/thermal.pbm";
                    thermal_filter(input_file_name, output);
                }
                else if(choice == 13){
                    output = (char *)"./output/checkers.pbm";
                    int type, box;
                    cout << "Choose a specific checkers filter: " << endl;
                    cout << "Normal [0]            Inverse [1]" << endl;
                    cout << "Dark & Light [2]          B&W [3]" << endl;
                    cin >> type;
                    if(type < 0 || type > 3)
                    {
                        cout << "Not a valid option." << endl;
                    }

                    cout << "Enter a number of checkers: ";
                    cin >> box;
                    if(box <= 0)
                    {
                        cout << "Invalid number of checkers" << endl;
                    }
                    
                    checkers_filter(input_file_name, output, box, type);  
                }
                else if(choice == 14){
                    output = (char *)"./output/static.pbm";
                    static_filter(input_file_name, output);
                }
                else if(choice == 15){
                    int type;
                    output = (char *)"./output/fast.pbm";
                    cout << "Choose a specific speed filter: " << endl;
                    cout << "All B&W [1]         All Color [2]" << endl;
                    cout << "Splash [3]      Inverse Splash[4] " << endl;
                    cin >> type;
                    if(type < 0 || type > 4)
                    {
                        cout << "Not a valid option." << endl;
                        return 0;
                    }
                    fast_filter(input_file_name, output, type);
                }

                else{
                    cout << "Not a valid filter." << endl;
                }

            }
            else if(choice == 2){
                cout << "Choose a filter to adjust orientation:" << endl << endl; 
                cout << "[1] Resize                   [6] Shuffle" << endl;
                cout << "[2] Mirror (Horizontal)      [7] Pixelation" << endl;
                cout << "[3] Flip (Horizontal)        [8] Kaleidoscope" << endl;
                cout << "[4] Mirror (Vertical)        [0] Quit" << endl;
                cout << "[5] Flip (Vertical)" << endl;
                cin >> choice;
                cout << endl; 

                if(choice == 0)
                {
                    return 0;
                }
                else if(choice == 1){
                    float size;
                    cout << "Enter a factor to resize by: " << endl;
                    cout << "For Example:  .5 will make it 1/2 the size " << endl;
                    cout << "               2 will make it 2x the size " << endl;
                    cin >> size;
                    if(size <= 0)
                    {
                        cout << "Invalid size" << endl;
                    }
                    output = (char *)"./output/resize.pbm";
                    resize_filter(input_file_name, output, size);
                }
                else if(choice == 2){
                    output = (char *)"./output/mirror_h.pbm";
                    mirror_h_filter(input_file_name, output);
                }
                else if(choice == 3){
                    output = (char *)"./output/flip_h.pbm";
                    flip_h_filter(input_file_name, output);
                }
                else if(choice == 4){
                    output = (char *)"./output/mirror_v.pbm";
                    mirror_v_filter(input_file_name, output);
                }
                else if(choice == 5){
                    output = (char *)"./output/flip_v.pbm";
                    flip_v_filter(input_file_name, output);
                }
                else if(choice == 6){
                    output = (char *)"./output/shuffle.pbm";
                    shuffle_filter(input_file_name, output);
                }
                else if(choice == 7){
                    int size;
                    cout << "Enter a pixelation factor: ";
                    cin >> size;

                    if(size <= 0)
                    {
                        cout << "Invalid factor number" << endl;
                        return 1;
                    }
                    output = (char *)"./output/pixelate.pbm";
                    pixelate_filter(input_file_name, output, size);
                }
                else if(choice == 8){
                    output = (char *)"./output/kaleidoscope.pbm";
                    kaleidoscope(input_file_name, output);
                }
                else{
                    cout << "Not a valid filter." << endl;
                }
            }
            else{
                cout << "Not a valid type of filter." << endl;
            }
        }
        cout << "Try Again? [y/n]" << endl;
        cin >> option;

        if(option == 'y' || option == 'Y')
        {
            again = 1;
        }

    } while(again == 1);


    return 0;
} 
