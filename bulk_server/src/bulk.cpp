#include "bulk.h"

#include <sstream>
 

void Bulk::AddCommand(const std::string &input)
{
    std::stringstream ss(input);
	std::string str;


    while (getline(ss, str, '\n'))
    {
        if (str.empty())
            continue;

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

    for (const auto &item : loggers)
    {
        item->Log(DataBclock{"bulk_" + std::to_string(_time + post++), res_str});
    }

    // LogToCmd("bulk: " + res_str);
    // LogToFile("bulk" + std::to_string(_time), res_str);
}