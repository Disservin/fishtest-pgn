#pragma once

#include <algorithm>
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace fishtest::utils {

[[nodiscard]] inline std::vector<std::string> get_pgn_files(const std::string &path,
                                                            bool recursive = false) {
    std::vector<std::string> files;

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (std::filesystem::is_regular_file(entry)) {
            std::string stem      = entry.path().stem().string();
            std::string extension = entry.path().extension().string();
            if ((extension == ".gz" && stem.ends_with(".pgn")) || extension == ".pgn") {
                files.push_back(entry.path().string());
            }
        } else if (recursive && std::filesystem::is_directory(entry)) {
            auto subdir_files = get_pgn_files(entry.path().string(), true);
            files.insert(files.end(), subdir_files.begin(), subdir_files.end());
        }
    }

    std::sort(files.begin(), files.end());

    return files;
}

[[nodiscard]] inline std::vector<std::vector<std::string>> split_chunks(
    const std::vector<std::string> &pgns, int target_chunks) {
    const int chunks_size = (pgns.size() + target_chunks - 1) / target_chunks;

    auto begin = pgns.begin();
    auto end   = pgns.end();

    std::vector<std::vector<std::string>> chunks;

    while (begin != end) {
        auto n    = std::min(chunks_size, static_cast<int>(std::distance(begin, end)));
        auto next = std::next(begin, n);
        chunks.push_back(std::vector<std::string>(begin, next));
        begin = next;
    }

    return chunks;
}

[[nodiscard]] std::optional<std::pair<std::string, std::string>> check_duplicates(
    const std::vector<std::string> &file_list) {
    for (size_t i = 1; i < file_list.size(); ++i) {
        if (file_list[i].find(file_list[i - 1]) == 0) {
            return std::make_pair(file_list[i - 1], file_list[i]);
        }
    }

    return std::nullopt;
}

}  // namespace fishtest::utils
