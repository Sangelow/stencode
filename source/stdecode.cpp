#include <iostream>

#include "cxxopts.hpp"
#include "decoder.hpp"


int main(int argc, char **argv) {
    // Display title
    std::cout << "\033[1mStenography - Decoder\033[0m"<< std::endl;

    // Generate parser options
    cxxopts::Options options("test", "A brief description");
    options.add_options()
        ("i,input", "Input file name",                                              cxxopts::value<std::string>()->default_value("input.png"))
        ("l,length", "Length of the message to decode",                             cxxopts::value<unsigned long long>()->default_value("0"))
        ("s,seed", "Seed of the pseudo-random number generator (0 if none)",        cxxopts::value<unsigned long long>()->default_value("0"))
        ("h,help", "Print usage")
        ;

    // Parse the arguments
    auto result = options.parse(argc, argv);

    // Help case
    if (result.count("help"))
    {
      std::cout << options.help() << std::endl;
      exit(0);
    }

    // Get the parameters
    DecoderSettings settings;
    settings.input = result["input"].as<std::string>();
    settings.length = result["length"].as<unsigned long long>();
    settings.seed = result["seed"].as<unsigned long long>();

    // Create and run the decoder
    Decoder decoder(settings);
    decoder.run();

    std::cout << "\033[1mDone\033[0m"<< std::endl;
}


