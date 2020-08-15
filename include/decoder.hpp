#pragma once
#ifndef DECODER_HPP
#define DECODER_HPP

#include <vector>
#include <string>

#include "lodepng.h"

struct DecoderSettings {
    std::string input;
    unsigned long long length;
    unsigned long long seed;
};


class Decoder
{
private:
    DecoderSettings settings;
    
    std::vector<unsigned char> image;   // raw pixels
    unsigned width, height;             // size of the image
    lodepng::State state;               // state
    unsigned bpp;                       // bits per pixel

    std::string message;                // the decoded message

private:
    void read_image();
    void find_message(std::vector<unsigned long long>& indices);
    void find_randomly_distributed_message(std::vector<unsigned long long>& indices);
    void find_continuously_distributed_message(std::vector<unsigned long long>& indices);
    void decode(std::vector<unsigned long long>& indices);

public:
    Decoder(DecoderSettings settings);
    virtual ~Decoder();
    void run();

};

#endif /* DECODER_HPP */
