
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>

#include <iostream>
#include <vector>
#include <istream>
#include <fstream>
#include <optional>
#include <memory.h>

#include "hash.h"

using namespace std::literals;

namespace fs = boost::filesystem;

class File
{
public:
    File(const fs::path &cur_path, size_t size, size_t group, size_t block_size) : _cur_path(cur_path), _size(size), _group(group), _block_size(block_size)
    {
    }

    bool open_file();

    void close_file();

    std::optional<std::string> read_block();

    bool equal_hash_file(std::shared_ptr<File> &&other);

    /// @brief returns the number of counted blocks
    /// @return
    const size_t get_hash_block_number() const noexcept
    {
        return _block_number;
    }

    const size_t get_file_size() const noexcept
    {
        return _size;
    }

    const std::string get_hash_block(size_t block_num = 0) const noexcept
    {
        return _hash_blocks.at(block_num);
    }

    const fs::path get_file_path() const noexcept
    {
        return _cur_path;
    }

private:
    fs::path _cur_path;
    size_t _size;
    size_t _group;

    size_t _block_size;
    size_t _block_number = 0;
    size_t _block_count;

    std::unique_ptr<std::ifstream> handle;

    std::vector<std::string> _hash_blocks;
};