#include <filters.hpp>
#include <testmetadata.hpp>
#include <utils.hpp>

int main(int argc, char const *argv[]) {
    auto files      = fishtest::utils::get_pgn_files("./pgns", true);
    auto chunks     = fishtest::utils::split_chunks(files, 4);
    auto duplicates = fishtest::utils::check_duplicates(files);

    std::ifstream f("./pgns/65a3aca179aa8af82b96f4b9.json");
    json data = json::parse(f);

    fishtest::metadata::TestMetaData t = data.get<fishtest::metadata::TestMetaData>();

    std::cout << "Test: " << t._id.value() << std::endl;

    auto meta_map = fishtest::metadata::find_metadata(files);

    for (auto &m : meta_map.value()) {
        std::cout << m.first << " " << m.second._id.value() << std::endl;
    }

    for (auto &f : files) {
        std::cout << f << std::endl;
    }

    std::cout << "Applying filters" << std::endl;

    fishtest::filters::apply_filters(files, meta_map.value(),
                                     fishtest::filters::File(std::regex("filter")));

    std::cout << "Applyied filters" << std::endl;

    for (auto &f : files) {
        std::cout << f << std::endl;
    }

    return 0;
}
