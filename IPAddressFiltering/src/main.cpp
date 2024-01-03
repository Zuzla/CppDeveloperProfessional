#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

int main(int argc, char const *argv[])
{
    try
    {
        std::ifstream infile("../data/ip_filter.tsv");
        std::ofstream out("../data/out.txt");
        std::cout.rdbuf(out.rdbuf());

        std::multimap<unsigned long, std::string, std::greater<unsigned long>> ip;

        for (std::string line; std::getline(infile, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            auto nums = split(v.at(0), '.');
            char buff[13];
            snprintf(buff, sizeof(buff), "%03lu%03lu%03lu%03lu",
                     std::stoul(nums.at(0)), std::stoul(nums.at(1)),
                     std::stoul(nums.at(2)), std::stoul(nums.at(3)));
            ip.insert({std::stoul(buff), v.at(0)});
        }

        for (const auto &item : ip)
        {
            std::cout << item.second << std::endl;
        }

        for (auto &item : ip)
        {
            auto parts = split(item.second, '.');

            if (parts[0] == "1")
                std::cout << item.second << std::endl;
        }

        for (auto &item : ip)
        {
            auto parts = split(item.second, '.');

            if (parts[0] == "46" && parts[1] == "70")
                std::cout << item.second << std::endl;
        }


        for (auto &item : ip)
        {
            auto parts = split(item.second, '.');

            if (parts[0] == "46" || parts[1] == "46" || parts[2] == "46" || parts[3] == "46")
                std::cout << item.second << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
