#pragma once
#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <vector>
#include <string>

#include "lodepng.h"

struct EncoderSettings {
    std::string input;
    std::string output;
    std::string message;
    bool random_seed;
    unsigned long long seed;
};

class Encoder
{
private:
    EncoderSettings settings;

    std::vector<unsigned char> image; // raw pixels
    unsigned width, height;              // size of the image
    lodepng::State state;                // state
    unsigned bpp;                        // bits per pixel
    unsigned bpc;                        // bits per channel

private:
    void read_image();
    void distribute_message(std::vector<unsigned long long>& indices);
    void distribute_message_randomly(std::vector<unsigned long long>& indices);
    void distribute_message_continuously(std::vector<unsigned long long>& indices);
    void encode(std::vector<unsigned long long>& indices);

public:
    Encoder(EncoderSettings settings);
    virtual ~Encoder();
    void run();



};

#endif /* ENCODER_HPP */
