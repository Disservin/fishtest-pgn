#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <regex>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

// nlohmann/json
#include <nlohmann/json.hpp>

using json   = nlohmann::json;
namespace fs = std::filesystem;

namespace fishtest::metadata {

template <typename T = std::string>
std::optional<T> get_optional(const nlohmann::json &j, const char *name) {
    const auto it = j.find(name);
    if (it != j.end()) {
        return std::optional<T>(j[name]);
    } else {
        return std::nullopt;
    }
}

class Sprt {
   public:
    Sprt()          = default;
    virtual ~Sprt() = default;

    std::optional<double> alpha;
    std::optional<int64_t> batch_size;
    std::optional<double> beta;
    std::optional<double> elo0;
    std::optional<double> elo1;
    std::optional<std::string> elo_model;
    std::optional<double> llr;
    std::optional<double> lower_bound;
    std::map<std::string, double> overshoot;
    std::string state;
    std::optional<double> upper_bound;
};

void inline from_json(const json &j, Sprt &s) {
    s.alpha       = get_optional<double>(j, "alpha");
    s.batch_size  = get_optional<int64_t>(j, "batch_size");
    s.beta        = get_optional<double>(j, "beta");
    s.elo0        = get_optional<double>(j, "elo0");
    s.elo1        = get_optional<double>(j, "elo1");
    s.elo_model   = get_optional<std::string>(j, "elo_model");
    s.llr         = get_optional<double>(j, "llr");
    s.lower_bound = get_optional<double>(j, "lower_bound");
    s.overshoot   = j.at("overshoot").get<std::map<std::string, double>>();
    s.state       = j.at("state").get<std::string>();
    s.upper_bound = get_optional<double>(j, "upper_bound");
}

class Args {
   public:
    Args()          = default;
    virtual ~Args() = default;

    std::optional<bool> adjudication;
    std::optional<bool> auto_purge;
    std::optional<std::string> base_net;
    std::optional<std::string> base_options;
    std::optional<std::string> base_signature;
    std::optional<std::string> base_tag;
    std::optional<std::string> book;
    std::optional<std::string> book_depth;
    std::optional<std::string> info;
    std::optional<double> itp;
    std::optional<std::string> msg_base;
    std::optional<std::string> msg_new;
    std::optional<std::string> new_net;
    std::optional<std::string> new_options;
    std::optional<std::string> new_signature;
    std::optional<std::string> new_tag;
    std::optional<std::string> new_tc;
    std::optional<int64_t> num_games;
    std::optional<int64_t> priority;
    std::optional<std::string> resolved_base;
    std::optional<std::string> resolved_new;
    std::optional<Sprt> sprt;
    std::optional<std::string> tc;
    std::optional<std::string> tests_repo;
    std::optional<int64_t> threads;
    std::optional<int64_t> throughput;
    std::optional<std::string> username;
};

void inline from_json(const json &j, Args &a) {
    a.adjudication   = get_optional<bool>(j, "adjudication");
    a.auto_purge     = get_optional<bool>(j, "auto_purge");
    a.base_net       = get_optional<std::string>(j, "base_net");
    a.base_options   = get_optional<std::string>(j, "base_options");
    a.base_signature = get_optional<std::string>(j, "base_signature");
    a.base_tag       = get_optional<std::string>(j, "base_tag");
    a.book           = get_optional<std::string>(j, "book");
    a.book_depth     = get_optional<std::string>(j, "book_depth");
    a.info           = get_optional<std::string>(j, "info");
    a.itp            = get_optional<double>(j, "itp");
    a.msg_base       = get_optional<std::string>(j, "msg_base");
    a.msg_new        = get_optional<std::string>(j, "msg_new");
    a.new_net        = get_optional<std::string>(j, "new_net");
    a.new_options    = get_optional<std::string>(j, "new_options");
    a.new_signature  = get_optional<std::string>(j, "new_signature");
    a.new_tag        = get_optional<std::string>(j, "new_tag");
    a.new_tc         = get_optional<std::string>(j, "new_tc");
    a.num_games      = get_optional<int64_t>(j, "num_games");
    a.priority       = get_optional<int64_t>(j, "priority");
    a.resolved_base  = get_optional<std::string>(j, "resolved_base");
    a.resolved_new   = get_optional<std::string>(j, "resolved_new");
    a.sprt           = get_optional<Sprt>(j, "sprt");
    a.tc             = get_optional<std::string>(j, "tc");
    a.tests_repo     = get_optional<std::string>(j, "tests_repo");
    a.threads        = get_optional<int64_t>(j, "threads");
    a.throughput     = get_optional<int64_t>(j, "throughput");
    a.username       = get_optional<std::string>(j, "username");
}

class Results {
   public:
    Results()          = default;
    virtual ~Results() = default;

    std::optional<int64_t> crashes;
    std::optional<int64_t> draws;
    std::optional<int64_t> losses;
    std::optional<std::vector<int64_t>> pentanomial;
    std::optional<int64_t> time_losses;
    std::optional<int64_t> wins;
};

void inline from_json(const json &j, Results &r) {
    r.crashes     = get_optional<int64_t>(j, "crashes");
    r.draws       = get_optional<int64_t>(j, "draws");
    r.losses      = get_optional<int64_t>(j, "losses");
    r.pentanomial = get_optional<std::vector<int64_t>>(j, "pentanomial");
    r.time_losses = get_optional<int64_t>(j, "time_losses");
    r.wins        = get_optional<int64_t>(j, "wins");
}

class ResultsInfo {
   public:
    ResultsInfo()          = default;
    virtual ~ResultsInfo() = default;

    std::optional<std::vector<std::string>> info;
    std::optional<std::string> style;
};

void inline from_json(const json &j, ResultsInfo &ri) {
    ri.info  = get_optional<std::vector<std::string>>(j, "info");
    ri.style = get_optional<std::string>(j, "style");
}

class TestMetaData {
   public:
    TestMetaData()          = default;
    virtual ~TestMetaData() = default;

    std::optional<std::string> _id;
    std::optional<bool> approved;
    std::optional<std::string> approver;
    std::optional<Args> args;
    std::optional<bool> base_same_as_master;
    std::optional<int64_t> cores;
    std::optional<bool> deleted;
    std::optional<bool> failed;
    std::optional<bool> finished;
    std::optional<bool> is_green;
    std::optional<bool> is_yellow;
    std::optional<std::string> last_updated;
    std::optional<std::string> rescheduled_from;
    std::optional<Results> results;
    std::optional<ResultsInfo> results_info;
    std::optional<std::string> start_time;
    std::optional<double> tc_base;
    std::optional<int64_t> workers;
};

void inline from_json(const json &j, TestMetaData &t) {
    t._id                 = get_optional<std::string>(j, "_id");
    t.approved            = get_optional<bool>(j, "approved");
    t.approver            = get_optional<std::string>(j, "approver");
    t.args                = get_optional<Args>(j, "args");
    t.base_same_as_master = get_optional<bool>(j, "base_same_as_master");
    t.cores               = get_optional<int64_t>(j, "cores");
    t.deleted             = get_optional<bool>(j, "deleted");
    t.failed              = get_optional<bool>(j, "failed");
    t.finished            = get_optional<bool>(j, "finished");
    t.is_green            = get_optional<bool>(j, "is_green");
    t.is_yellow           = get_optional<bool>(j, "is_yellow");
    t.last_updated        = get_optional<std::string>(j, "last_updated");
    t.rescheduled_from    = get_optional<std::string>(j, "rescheduled_from");
    t.results             = get_optional<Results>(j, "results");
    t.results_info        = get_optional<ResultsInfo>(j, "results_info");
    t.start_time          = get_optional<std::string>(j, "start_time");
    t.tc_base             = get_optional<double>(j, "tc_base");
    t.workers             = get_optional<int64_t>(j, "workers");
}

using TestMetaDataMap = std::unordered_map<std::string, TestMetaData>;

[[nodiscard]] inline TestMetaData find_metadata_of_pgn(const std::string &pathname) {
    fs::path path(pathname);
    auto directory     = path.parent_path().string();
    auto filename      = path.filename().string();
    auto test_id       = filename.substr(0, filename.find_last_of('-'));
    auto test_filename = pathname.substr(0, pathname.find_last_of('-'));

    std::ifstream json_file(test_filename + ".json");

    if (!json_file.is_open()) {
        throw std::runtime_error("Could not open file " + test_filename + ".json");
    }

    json metadata = json::parse(json_file);

    return metadata.get<TestMetaData>();
}

/// @brief Finds and loads the metadata for a list of test files
/// metadata is expected to be in the same directory as the pgn files.
/// @param pgn_files
/// @param allow_duplicates
/// @return
[[nodiscard]] inline std::optional<TestMetaDataMap> find_metadata(
    const std::vector<std::string> &pgn_files, bool allow_duplicates = false) {
    TestMetaDataMap meta_map;

    // map to check for duplicate tests
    std::unordered_map<std::string, std::string> test_map;
    std::set<std::string> test_warned;

    for (const auto &pathname : pgn_files) {
        fs::path path(pathname);
        auto filename      = path.filename().string();
        auto test_id       = filename.substr(0, filename.find_last_of('-'));
        auto test_filename = pathname.substr(0, pathname.find_last_of('-'));

        if (test_map.find(test_id) == test_map.end()) {
            test_map[test_id] = test_filename;
        } else if (test_map[test_id] != test_filename) {
            if (test_warned.find(test_filename) == test_warned.end()) {
                auto directory = path.parent_path().string();
                auto type      = (allow_duplicates ? "Warning" : "Error");

                std::cout << type << ": Detected a duplicate of test " << test_id
                          << " in directory " << directory << std::endl;

                test_warned.insert(test_filename);

                if (!allow_duplicates) {
                    return std::nullopt;
                }
            }
        }

        // load the JSON data from disk, only once for each test
        if (meta_map.find(test_filename) == meta_map.end()) {
            meta_map[test_filename] = find_metadata_of_pgn(pathname);
        }
    }

    return meta_map;
}
}  // namespace fishtest::metadata
