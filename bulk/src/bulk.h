#pragma once

#include <iostream>
#include <queue>
#include <chrono>
#include <fstream>

class Bulk
{
public:
    Bulk(size_t size) : _size_block(size) {}

    void RunCmd();

    void Log();

private:
    void LogToCmd(const std::string &res_str);

    void LogToFile(const std::string &name_file, const std::string &data);

private:
    std::queue<std::string> commands;

    long _time;

    size_t _open_brakets = 0;
    size_t _close_brakets = 0;
    size_t _size_block;
};