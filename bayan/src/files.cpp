#include <regex>
#include <boost/regex.hpp>

#include "files.h"

void Files::find_files(const fs::path &cur_path, const int &level)
{
    if (fs::is_directory(cur_path) && level != 0)
    {        
        if (auto it = std::find(_exclude_directories.begin(), _exclude_directories.end(), cur_path); it == _exclude_directories.end())
        {
            for (const fs::directory_entry &item : fs::directory_iterator(cur_path))
            {
                find_files(item.path(), level);
            }
        }
    }
    else
    {
        if (fs::file_size(cur_path) >= _minimum_file_size)
        {
            // BOOST_LOG_TRIVIAL(debug) << cur_path.string();

            if (mask_check(cur_path.filename().string()))
                files_info.push_back(std::make_shared<File>(cur_path, fs::file_size(cur_path), 0, _size_block));
        }
    }
}

bool Files::mask_check(const std::string &cur_path)
{
    if (_masks_file_names.empty())
        return true;

    for (auto &mask : _masks_file_names)
    {
        mask = mask;
        // std::regex reg{mask};
        // std::smatch match;
        // if(std::regex_search(cur_path, match, reg))
        // {
        //     int y = 0;
        // }

        boost::regex re(mask);
        if (boost::regex_match(cur_path, re))
            return true;
    }

    return false;
}

void Files::find_duplicates()
{
    for (auto f_it = files_info.begin(); f_it != files_info.end(); ++f_it)
    {
        if (!f_it->get()->open_file())
            continue;

        for (auto s_it = std::next(f_it); s_it != files_info.end(); ++s_it)
        {
            if (!s_it->get()->open_file())
                continue;

            if (f_it->get()->equal_hash_file(std::move(*s_it)))
            {
                _groups[f_it->get()->get_file_path()].push_back(s_it->get()->get_file_path());
            }
        }
    }
}
