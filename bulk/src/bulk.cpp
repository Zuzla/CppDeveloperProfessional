#include "bulk.h"

void Bulk::RunCmd()
{
    std::string str{};

    while (getline(std::cin, str))
    {
        if (str == "{")
        {
            if (_open_brakets == 0)
            {
                Log();
            }

            ++_open_brakets;

            continue;
        }

        if (str == "}")
        {
            ++_close_brakets;

            if (_open_brakets == _close_brakets)
            {
                Log();
            }

            continue;
        }

        if (commands.size() == 0)
        {
            _time = std::chrono::system_clock::now().time_since_epoch().count();
        }
        commands.push(str);

        if ((commands.size() == _size_block) && (_open_brakets == _close_brakets))
        {
            Log();
        }
    }

    Log();
}

void Bulk::Log()
{
    if (commands.size() == 0)
        return;

    _open_brakets = _close_brakets = 0;

    std::string res_str = "";
    while (commands.size() != 0)
    {
        res_str += commands.front() + ", ";
        commands.pop();
    }

    res_str.pop_back();
    res_str.pop_back();

    LogToCmd("bulk: " + res_str);
    LogToFile("bulk" + std::to_string(_time), res_str);
}

void Bulk::LogToCmd(const std::string &res_str)
{
    std::cout << res_str << std::endl;
}

void Bulk::LogToFile(const std::string &name_file, const std::string &data)
{
    std::fstream f;
    f.open(name_file, std::ios::out);
    f << data << std::endl;
    f.close();
}