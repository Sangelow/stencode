#include <iostream>
#include <vector>
#include <bitset>
#include <stdlib.h>
#include <algorithm>
#include <time.h>

#include "decoder.hpp"
#include "pngtools.hpp"
#include "lodepng.h"

Decoder::Decoder(DecoderSettings settings) : settings(settings) {
    
}

Decoder::~Decoder() {

}

void Decoder::run() {
    // Display some informations
    std::cout << " - Length of the message: " << settings.length << std::endl;
    std::cout << " - Start the decoding"<< std::endl;
    // Read the PNG file
    read_image();
    // Generate a vector that associate the bit number in the message to the bit number in the image
    std::vector<unsigned long long> indices;
    indices.reserve(8*settings.length);
    find_message(indices);
    // Decode the message
    decode(indices);
    // Display
    std::cout << "The message is:" << std::endl;
    std::cout << "\033[3m" << message << "\033[0m"<< std::endl;
}

void Decoder::read_image() {
    std::cout << " - Reading the file: " << settings.input << std::endl;
    // Read the image
    readPNG(settings.input, image, width, height, state);
    // Get the number of bits per pixel
    bpp = lodepng_get_bpp(&state.info_raw);
    std::cout << " - Detected " << bpp << " bits per pixel" << std::endl;
    // Get the number of channel per bits
    unsigned n_channels = lodepng_get_channels(&state.info_raw);
    std::cout << " - Detected " << n_channels << " channels" << std::endl;
    // Compute the number of bit per channels
    bpc = bpp/n_channels;
}

void Decoder::find_message(std::vector<unsigned long long>& indices) {
    std::cout << " - Detect the character inside the image" << std::endl;
    if (settings.seed != 0) {
        find_randomly_distributed_message(indices);
    } else {
        find_continuously_distributed_message(indices);
    }
}

void Decoder::find_randomly_distributed_message(std::vector<unsigned long long>& indices) {
    // Initialise the seed
    std::cout << " - Initialise the pseudo random number generator" << std::endl;
    srand (settings.seed);
    // Declare variables
    unsigned long long pixel;
    unsigned long long index;
    for (unsigned i=0; i<settings.length; ++i) {
        for (int j=0; j<8; ++j) {
            do {
                // Get a random pixel
                pixel = rand() % (height*width);
                // Convert to bit number in the image
                index = pixel * (bpc/(8*sizeof(char)));
                // Repeat if the pixel is already used
            } while (std::find(indices.begin(), indices.end(), index) != indices.end());
            // Store the new index
            indices[i*8+j] = index;
        }
    }
}

void Decoder::find_continuously_distributed_message(std::vector<unsigned long long>& indices) {
    for (unsigned i=0; i<settings.length; ++i) {
        for (int j=0; j<8; ++j) {
            // i*8+j corresponds to the pixel in the image
            // then we multiply by the number of byte per pixel
            indices[i*8+j] = (i*8 + j) * (bpc/(8*sizeof(char)));
        }
    }
}

void Decoder::decode(std::vector<unsigned long long>& indices) {
    std::cout << " - Decoding the message in the image" << std::endl;
    // Initialise the quantities
    std::bitset<8> c_bitset;    // character bitset
    // Get the message
    for (unsigned i=0; i<settings.length; ++i) {
        // Reset the bitset
        c_bitset.reset();
        for (unsigned j=0; j<8; ++j) {
            c_bitset[j] = image[indices[i*8+j]] & 1U;
        }
        // Add the character to the message
        message += (char)c_bitset.to_ulong();
    }
}
