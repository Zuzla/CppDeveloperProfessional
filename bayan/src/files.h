#pragma once

#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>

#include <iostream>
#include <vector>
#include <memory>

#include "file.h"

using namespace std::literals;

namespace fs = boost::filesystem;

class Files
{
public:
    Files(const std::vector<std::string> &masks_file_names, const std::vector<fs::path> &exclude_directories, size_t size_block, size_t minimum_file_size) : _masks_file_names(masks_file_names), _exclude_directories(exclude_directories), _size_block(size_block), _minimum_file_size(minimum_file_size)
    {
    }

    void find_files(const fs::path &cur_path, const int &level);

    void find_duplicates();

    const std::map<fs::path, std::vector<fs::path>> get_groups() const noexcept
    {

        return _groups;
    }

    bool mask_check(const std::string &cur_path);

private:
    std::vector<std::shared_ptr<File>> files_info;

    std::vector<fs::path> _exclude_directories;
    std::vector<std::string> _masks_file_names;
    size_t _size_block;

    std::map<fs::path, std::vector<fs::path>> _groups;

    size_t _minimum_file_size;
};