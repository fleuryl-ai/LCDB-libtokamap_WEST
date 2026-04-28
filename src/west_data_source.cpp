#include "west_data_source.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <ctre/ctre.hpp>
#include <deque>
#include <filesystem>
#include <format>
#include <fstream>
#include <libtokamap.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <vector>

// Include ts_rqparam.h at global scope to ensure tsrqparm is declared globally.
// This prevents the include inside the anonymous namespace below from making it local.
#include "ts_rqparam.h"

namespace
{

// Wrapper to redirect calls from the anonymous namespace (due to the include below)
// to the global tsrqparm function defined in west_access library.
Longint tsrqparm(char** pt_char_address, Longint* nb_val, Longint num_choc, const char* nom_prod, const char* nom_objet, const char* nom_param, Longint val_nb, int *format)
{
    return ::tsrqparm(pt_char_address, nb_val, num_choc, nom_prod, nom_objet, nom_param, val_nb, format);
}

// Inclusion du fichier généré contenant les fonctions et la map
#include "../src/west_magnetics_handlers.cpp" 

constexpr auto number_re = ctll::fixed_string{R"(\d+)"};

void parse_signal(const std::string& signal,
                  std::string& func_name_key,
                  std::vector<int>& indices)
{
    std::deque<std::string> tokens;
    libtokamap::split(tokens, signal, "/");

    std::string path_for_func_name;

    for (const auto& token : tokens)
    {
        if (ctre::match<number_re>(token))
        {
            indices.push_back(std::stoi(token));
        }
        else
        {
            if (!path_for_func_name.empty())
            {
                path_for_func_name += '_';
            }
            path_for_func_name += token;
        }
    }

    func_name_key = "get_" + path_for_func_name;
}

std::unique_ptr<libtokamap::DataSource> west_data_source_factory(const libtokamap::DataSourceFactoryArgs& args)
{
    auto data_root = libtokamap::get_arg<std::string>(args, "data_root");
    return std::make_unique<WESTDataSource>(data_root);
}

} // namespace

libtokamap::TypedDataArray WESTDataSource::get(const libtokamap::DataSourceArgs& map_args,
                                               const libtokamap::MapArguments& arguments,
                                               libtokamap::RamCache* /*ram_cache*/)
{
    if (!map_args.contains("signal")) {
        throw libtokamap::ParameterError{"required argument 'signal' not provided"};
    }

    std::string signal = map_args.at("signal");
    printf("-->signal = '%s'\n", signal.c_str());

    std::string func_name_key;
    std::vector<int> indices;

    if (map_args.contains("shot")) {
            int shot_int = map_args.at("shot").get<int>();
    } else {
        //throw libtokamap::DataSourceError("Missing 'shot' argument");
    }

    printf("Calling parse_signal for '%s'\n", signal.c_str());
    parse_signal(signal, func_name_key, indices);

    // Recherche de la fonction associée au signal
    if (auto it = signal_dispatcher.find(func_name_key); it != signal_dispatcher.end()) {
        // Appel de la fonction trouvée en lui passant les arguments
        printf("Calling handler for signal '%s'\n", signal.c_str());
        return it->second(map_args, indices);
    }

    // Gestion du cas où le signal n'est pas connu
    printf("Warning: No handler found for signal '%s' (derived function name '%s')\n", signal.c_str(), func_name_key.c_str());
    return libtokamap::TypedDataArray{0};
}

void LibTokaMapFactoryLoader(libtokamap::FactoryEntryInterface& factory)
{
    factory.function = west_data_source_factory;
}
