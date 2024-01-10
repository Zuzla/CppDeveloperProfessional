#pragma once

#include <iostream>
#include <algorithm>
#include <iterator>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>
#include <boost/uuid/detail/sha1.hpp>

using namespace std::literals;

#define HASH(X) Hashing::GetInstance().hash(X)
#define HASH_TYPE(X) Hashing::GetInstance().set_hash_type(X)

class Hashing
{
    std::string hash_type;

public:
    // убираем конструктор копирования
    Hashing(const Hashing &) = delete;
    Hashing &operator=(const Hashing &) = delete;
    Hashing(Hashing &&) = delete;
    Hashing &operator=(Hashing &&) = delete;

    // получение ссылки на единственный объект
    static Hashing &GetInstance()
    {
        static Hashing obj;
        return obj;
    }

    void set_hash_type(const std::string& new_hash_type);

    const std::string get_md5(const std::string &str);

    const std::string get_sha1(const std::string &str);

    const std::string hash(const std::string& my_string);

private:
    Hashing() = default;
};