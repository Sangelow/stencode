#pragma once
#ifndef PNGTOOLS_HPP
#define PNGTOOLS_HPP

#include <vector>
#include <string>

#include "lodepng.h"

void readPNG(
    std::string filename,
    std::vector<unsigned char>& image,
    unsigned& width,
    unsigned& height,
    lodepng::State& state
    );


void writePNG(
    std::string filename,
    std::vector<unsigned char>& image,
    unsigned width,
    unsigned height
    );

#endif /* PNGTOOLS_HPP */

