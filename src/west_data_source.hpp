
#include <libtokamap.hpp>

extern "C" void LibTokaMapFactoryLoader(libtokamap::FactoryEntryInterface& factory);

class WESTDataSource : public libtokamap::DataSource
{
  public:
    explicit WESTDataSource(std::filesystem::path data_root) : m_data_root{std::move(data_root)}
    {
        if (!std::filesystem::exists(m_data_root)) {
            throw libtokamap::FileError{"data root does not exist"};
        }
        if (!std::filesystem::is_directory(m_data_root)) {
            throw libtokamap::FileError{"data root is not a directory"};
        }
    }
    libtokamap::TypedDataArray get(const libtokamap::DataSourceArgs& map_args,
                                   const libtokamap::MapArguments& arguments, libtokamap::RamCache* ram_cache) override;

  private:
  protected:
    std::filesystem::path m_data_root;
    std::unordered_map<std::string, nlohmann::json> m_data;
};
