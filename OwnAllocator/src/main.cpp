#include <iostream>
#include <map>

#include "allocator.h"
#include "vector.h"

unsigned int fact(int num)
{
    unsigned int res = 1;

    for (size_t i = 1; i <= num; i++)
    {
        res *= i;
    };

    return res;
}

int main(int, char **)
{
    std::map<int, int> map;
    std::map<int, int, std::less<int>, Allocator<std::pair<const int, int>, 10>> custom_map;

    for (size_t i = 0; i < 10; i++)
    {
        auto pair = std::pair<const int, int>(i, fact(i));
        map.insert(pair);
        custom_map.insert(pair);
    }

    for (const auto &item : custom_map)
    {
        std::cout << item.first << "\t" << item.second << std::endl;
    }

    vector<int, Allocator<int>> custom_vec;

    for (size_t i = 0; i < 10; i++)
    {
        custom_vec.push_back(fact(i));
        std::cout << custom_vec[i] << std::endl;
    }
}
