#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <boost/algorithm/string.hpp>

#include <fstream>
#include <iostream>
#include <optional>
#include <vector>
#include <algorithm>

#include "files.h"
#include "hash.h"

using namespace std::literals;

namespace fs = boost::filesystem;

struct Args
{
    std::vector<fs::path> scan_directory;
    std::vector<fs::path> exclude_directory;
    size_t scan_level;
    size_t minimum_file_size;
    std::vector<std::string> masks_file_names;
    size_t size_block;
    std::string hash_type;
};

[[nodiscard]] std::optional<Args> ParseCommandLine(int argc,
                                                   const char *const argv[])
{
    namespace po = boost::program_options;

    po::options_description desc{"All options"s};

    Args args;

    auto add = desc.add_options();
    add("help,h", "Show help");
    add("directory,d", po::value<std::vector<fs::path>>(&args.scan_directory)->multitoken(), "directories to scan (there may be several)");
    add("ex_directory,ed", po::value<std::vector<fs::path>>(&args.exclude_directory)->multitoken(), "directories to exclude from scanning (there may be several)");
    add("level,l", po::value<size_t>(&args.scan_level)->default_value(0), "scan level (one for all directories, 0 - only the specified directory without attachments)");
    add("file_size,fs", po::value<size_t>(&args.minimum_file_size)->default_value(1), "minimum file size, by default, all files larger than 1 byte are checked");
    add("mask,m", po::value<std::vector<std::string>>(&args.masks_file_names)->multitoken(), "masks of file names allowed for comparison");
    add("size_block,sb", po::value<size_t>(&args.size_block)->default_value(1), "the block size that reads files (by default is 1 byte)");
    add("hash,H", po::value<std::string>(&args.hash_type)->default_value("md5"), "Set save state period");

    // variables_map хранит значения опций после разбора
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.contains("help"s))
    {
        std::cout << desc;
        return std::nullopt;
    }

    if (!vm.contains("directory"s))
    {
        throw std::runtime_error("The search directory is not set"s);
    }

    if (vm.contains("mask"s))
    {
        for (auto &item : args.masks_file_names)
        {
            boost::replace_all(item, "."s, "\\."s);
            boost::replace_all(item, "?"s, "."s);
            boost::replace_all(item, "*"s, ".*"s);
        }
    }

    // С опциями программы всё в порядке, возвращаем структуру args
    return args;
}

int main(int argc, char **argv)
{
    try
    {

        std::optional<Args> args = ParseCommandLine(argc, argv);
        if (args == std::nullopt)
        {
            throw std::invalid_argument("Args error. Try \'-h\' for info");
        }

        HASH_TYPE(args->hash_type);

        Files files(args->masks_file_names, args->exclude_directory, args->size_block, args->minimum_file_size);

        for (const auto &item : args->scan_directory)
        {
            files.find_files(item, args->scan_level);
        }

        files.find_duplicates();

        auto groups = files.get_groups();

        for (const auto &group : groups)
        {
            std::cout << group.first << std::endl;

            for (const auto &item : group.second)
            {
                std::cout << item << std::endl;
            }

            std::cout << std::endl;
        }

        // BOOST_LOG_TRIVIAL(debug) << "Finish main!";
    }
    catch (const std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
