#include "hash.h"

void Hashing::set_hash_type(const std::string& new_hash_type)
{
    hash_type = new_hash_type;
}

const std::string Hashing::get_md5(const std::string &str)
{
    using boost::uuids::detail::md5;

    md5 hash;
    md5::digest_type digest;

    hash.process_bytes(str.data(), str.size());
    hash.get_digest(digest);

    const auto charDigest = reinterpret_cast<const char *>(&digest);
    std::string result;
    boost::algorithm::hex(charDigest, charDigest + sizeof(md5::digest_type), std::back_inserter(result));
    return result;
}

const std::string Hashing::get_sha1(const std::string &str)
{
    using boost::uuids::detail::sha1;

    sha1 hash;
    sha1::digest_type digest;

    hash.process_bytes(str.data(), str.size());
    hash.get_digest(digest);

    const auto charDigest = reinterpret_cast<const char *>(&digest);
    std::string result;
    boost::algorithm::hex(charDigest, charDigest + sizeof(sha1::digest_type), std::back_inserter(result));
    return result;
}

const std::string Hashing::hash(const std::string& my_string)
{

    if (hash_type == "sha1"s)
    {
        return get_sha1(my_string);
    }
    else
    {
        return get_md5(my_string);
    }
}