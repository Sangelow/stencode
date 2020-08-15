#include <iostream>
#include <vector>

#include "pngtools.hpp"
#include "lodepng.h"

//Decode from disk to raw pixels with a single function call
void readPNG(
        std::string filename,
        std::vector<unsigned char>& image,
        unsigned& width,
        unsigned& height,
        lodepng::State& state
        ) {
    // Load the png
    std::vector<unsigned char> png;   // loaded png file
    unsigned error = lodepng::load_file(png, filename); //load the image file with given filename

    // Decode the png
    if(!error) error = lodepng::decode(image, width, height, state, png);

    //if there's an error, display it
    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}

void writePNG(
        std::string filename,
        std::vector<unsigned char>& image,
        unsigned width,
        unsigned height
        ) {
    //Encode the image
    unsigned error = lodepng::encode(filename, image, width, height);

    //if there's an error, display it
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}
