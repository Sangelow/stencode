#include <iostream>

#include "cxxopts.hpp"
#include "encoder.hpp"

int main(int argc, char **argv) {
    // Display title
    std::cout << "\033[1mStenography - Encoder\033[0m"<< std::endl;

    // Generate parser options
    cxxopts::Options options("stencode", "Encode a file or a message inside a png file");
    options.add_options()
        ("i,input", "Input png image file name",                                        cxxopts::value<std::string>()->default_value("input.png"))
        ("m,message", "Message to encode",                                              cxxopts::value<std::string>()->default_value(""))
        ("o,output", "Output png image file name",                                      cxxopts::value<std::string>()->default_value("output.png"))
        ("r,random_seed", "Generate a random seed and use the pseudo random generator", cxxopts::value<bool>()->default_value("false"))
        ("s,seed", "Seed of the pseudo-random number generator (0 if none)",            cxxopts::value<unsigned long long>()->default_value("0"))
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
    EncoderSettings settings;
    settings.input = result["input"].as<std::string>();
    settings.message = result["message"].as<std::string>();
    settings.output = result["output"].as<std::string>();
    settings.seed = result["seed"].as<unsigned long long>();
    settings.random_seed = result["random_seed"].as<bool>();

    // Create and run the encoder
    Encoder encoder(settings);
    encoder.run();

    std::cout << "\033[1mDone\033[0m"<< std::endl;
}


