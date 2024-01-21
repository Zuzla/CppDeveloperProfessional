#pragma once

#include <iostream>
#include <queue>
#include <chrono>
#include <fstream>
#include <memory>

#include "log.h"
#include "log_console.h"
#include "log_file.h"

class Bulk
{
public:
    Bulk(size_t size) : _size_block(size) 
    {
        logs.push_back(std::make_unique<LoggerConsole>());
        logs.push_back(std::make_unique<LoggerFile>());
    }

    void RunCmd();

    void Log();

private:
    std::queue<std::string> commands;

    long _time;

    size_t _open_brakets = 0;
    size_t _close_brakets = 0;
    size_t _size_block;

    std::vector<std::unique_ptr<Logger>> logs;
};