#include <iostream>
#include <vector>
#include <bitset>
#include <stdlib.h>
#include <algorithm>
#include <time.h>

#include "lodepng.h"
#include "pngtools.hpp"
#include "encoder.hpp"


Encoder::Encoder(EncoderSettings settings) : settings(settings) {
    // Generate a random seed if necessary
    if (this->settings.random_seed) {
        this->settings.seed = time(NULL);
    }
}


Encoder::~Encoder() {

}


void Encoder::run() {
    // Display some informations
    std::cout << " - Length of the message: " << settings.message.size() << std::endl;
    std::cout << " - Start the encoding"<< std::endl;

    // Read the PNG file
    read_image();

    // Generate a vector that associate the bit number in the message to the bit number in the image
    std::vector<unsigned long long> indices;
    indices.reserve(8*settings.message.size());
    distribute_message(indices);

    // Encode the message in the least significant bits of the char at each indices
    encode(indices);

    // Encode the new png file
    std::cout << " - Write the new image in the file: " << settings.output << std::endl;
    writePNG(settings.output, image, width, height);

    // Display final message
    std::cout << "Encoding done successfully!" << std::endl;
}


void Encoder::read_image() {
    std::cout << " - Reading the file: " << settings.input << std::endl;
    readPNG(settings.input, image, width, height, state);

    // Check if the image is large enough to store the message
    if (width * height < settings.message.size()*8) {
        std::cout << "Image is too small to store the message!" << std::endl;
        return;
    }

    // Get the number of bits per pixel
    bpp = lodepng_get_bpp(&state.info_raw);
    std::cout << " - Detected " << bpp << " bits per pixel" << std::endl;

    // Get the number of channel per bits
    unsigned n_channels = lodepng_get_channels(&state.info_raw);
    std::cout << " - Detected " << n_channels << " channels" << std::endl;

    // Compute the number of bit per channels
    bpc = bpp/n_channels;
}


void Encoder::distribute_message(std::vector<unsigned long long>& indices) {
    std::cout << " - Distribute the message inside the image" << std::endl;
    if (settings.seed != 0) {
        distribute_message_randomly(indices);
    } else {
        distribute_message_continuously(indices);
    }
}

void Encoder::distribute_message_randomly(std::vector<unsigned long long>& indices) {

    std::cout << " - Initialise the pseudo random number generator with the seed: " << settings.seed << std::endl;
    srand (settings.seed);

    // Declare variables
    unsigned long long pixel;
    unsigned long long index;

    for (unsigned i=0; i<settings.message.size(); ++i) {
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

void Encoder::distribute_message_continuously(std::vector<unsigned long long>& indices) {
    for (unsigned i=0; i<settings.message.size(); ++i) {
        for (int j=0; j<8; ++j) {
            // i*8+j corresponds to the pixel in the image
            // then we multiply by the number of byte per pixel
            indices[i*8+j] = (i*8 + j) * (bpc/(8*sizeof(char)));
        }
    }
}

void Encoder::encode(std::vector<unsigned long long>& indices) {
    std::cout << " - Encoding the message in the image" << std::endl;
    // Initialise the bitset
    std::bitset<8> c_bitset;
    // Write the message in the png file
    for (unsigned i=0; i<settings.message.size(); ++i) {
        // Convert the character to bitset
        c_bitset = std::bitset<8>(settings.message[i]);
        // Iterate through the bitset
        for (int j=0; j<8; ++j) {
            // std::cout << indices[i*8+j] << "/" << image.size() << std::endl;
            image[indices[i*8+j]] ^= (-c_bitset[j] ^ image[indices[i*8+j]]) & 1UL;
        }
    }
}
