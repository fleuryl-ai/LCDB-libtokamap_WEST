#include "my_magnetics_writer.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

int main() {
    int shot = 57420;

    MyMagneticsWriter writer;

    std::cout << "Generating JSON data for shot " << shot << "..." << std::endl;

    // La méthode generate() appelle toutes vos méthodes surchargées
    nlohmann::json data = writer.generate(shot);

    std::string filename = "data_" + std::to_string(shot) + "_generated.json";
    std::ofstream output_file(filename);
    output_file << data.dump(4);

    std::cout << "Successfully generated " << filename << std::endl;

    return 0;
}