#include "file.h"

bool File::open_file()
{
    if (handle == nullptr)
    {
        handle = std::make_unique<std::ifstream>(_cur_path);

        if (_size < _block_size)
        {
            close_file();
            return false;
        }

        _block_count = std::ceil((_size * 1.) / (_block_size * 1.));
        read_block();
    }

    return true;
}

void File::close_file()
{
    if (handle != nullptr)
    {
        handle.get()->close();
        handle = nullptr;
    }
}

std::optional<std::string> File::read_block()
{
    if (handle == nullptr)
    {
        return std::nullopt;
    }

    if (_size < _block_size)
    {
        close_file();
        return std::nullopt;
    }

    auto _data = std::make_unique<char[]>(_block_size);

    handle.get()->read(_data.get(), _block_size);
    handle.get()->seekg((_block_number + 1) * _block_size);

    _hash_blocks.push_back(HASH(_data.get()));

    ++_block_number;

    return _hash_blocks.at(_block_number - 1);
}

bool File::equal_hash_file(std::shared_ptr<File> &&other)
{
    if (_size != other->get_file_size())
        return false;

    for (size_t i = 0; i < _block_count; ++i)
    {
        if (i >= _block_number)
        {
            read_block();
        }

        if (i >= other->get_hash_block_number())
        {
            other->read_block();
        }

        auto rmp1 = get_hash_block(i);
        auto rmp2 = other->get_hash_block(i);

        if (rmp1 != rmp2)
        {
            return false;
        }
    }

    return true;
}