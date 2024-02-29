#pragma once

#include <optional>
#include <regex>
#include <string>

#include "testmetadata.hpp"

namespace fishtest {

namespace filters {

class Book {
    std::regex regex_book;
    bool invert;

   public:
    Book(const std::regex &rb, bool inv) : regex_book(rb), invert(inv) {}

    bool apply(const std::string &filename, const metadata::TestMetaDataMap &meta_map) const {
        // check if metadata and "book" entry exist
        if (meta_map.find(filename) != meta_map.end() &&
            meta_map.at(filename).args.value().book.has_value()) {
            bool match =
                std::regex_match(meta_map.at(filename).args.value().book.value(), regex_book);
            return invert ? match : !match;
        }

        // missing metadata or "book" entry can never match
        return true;
    }
};

class File {
    std::regex regex_rev;

   public:
    File(const std::regex &rb) : regex_rev(rb) {}

    bool apply(const std::string &filename, const metadata::TestMetaDataMap &meta_map) const {
        if (meta_map.find(filename) == meta_map.end()) {
            return true;
        }

        if (meta_map.at(filename).args.value().resolved_base.has_value() &&
            std::regex_match(meta_map.at(filename).args.value().resolved_base.value(), regex_rev)) {
            return false;
        }

        if (meta_map.at(filename).args.value().resolved_new.has_value() &&
            std::regex_match(meta_map.at(filename).args.value().resolved_new.value(), regex_rev)) {
            return false;
        }

        return true;
    }
};

class Sprt {
   public:
    bool apply(const std::string &filename, const metadata::TestMetaDataMap &meta_map) const {
        // check if metadata and "sprt" entry exist
        if (meta_map.find(filename) != meta_map.end() &&
            meta_map.at(filename).args.value().sprt.has_value() &&
            meta_map.at(filename).args.value().sprt.has_value()) {
            return false;
        }

        return true;
    }
};

template <typename... Filters>
void apply_filters(std::vector<std::string> &file_list, const metadata::TestMetaDataMap &meta_map,
                   Filters... filters) {
    const auto pred = [&](const std::string &pathname) {
        auto test_filename = pathname.substr(0, pathname.find_last_of('-'));
        // Apply all filters to the test_filename. If any filter
        // returns false, the file is removed.
        return !(... || !filters.apply(test_filename, meta_map));
    };

    file_list.erase(std::remove_if(file_list.begin(), file_list.end(), pred), file_list.end());
}
}  // namespace filters

}  // namespace fishtest
