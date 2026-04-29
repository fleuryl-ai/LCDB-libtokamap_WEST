#include <algorithm>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <libtokamap.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <typeindex>
#include <vector>
#include "west_data_source.hpp"
#include "west_magnetics_mapper.hpp"


namespace
{

int build_mapping(int shot)
{
    std::cout << "[DEBUG] Starting build_mapping\n";
    libtokamap::Profiler::init();

    try {
        std::cout << "[DEBUG] Initializing MappingHandler\n";
        libtokamap::MappingHandler mapping_handler;

        std::filesystem::path config_path = "/ZONE_TRAVAIL/LF218007/libtokamap_west/libtokamap-west-datasource/config/config.toml";

        printf("Loading mapping configuration from '%s'\n", config_path.c_str());
        mapping_handler.init(config_path);

        const char* experiment = "WEST";

        std::cout << "[DEBUG] Entering map_all\n";
        nlohmann::json trace;

        WestMagneticsMapper mapper;
        mapper.map_all(mapping_handler, trace, experiment, shot);

        //std::cout << "[DEBUG] Writing trace.json\n";
        //std::ofstream("trace.json") << trace.dump(4);
        
    } catch (std::exception& ex) {
        std::cerr << "error: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}

} // namespace

int main()
{
    int shot = 57420;
    return build_mapping(shot);
}
