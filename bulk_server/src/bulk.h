#pragma once

#include <iostream>
#include <queue>
#include <chrono>
#include <fstream>
#include <memory>

#include "log.h"
#include "log_console.h"
#include "log_file.h"
#include "logger_async.h"

class Bulk
{
public:
    Bulk(size_t size) : _size_block(size) 
    {
        loggers.push_back(std::make_unique<ConcurentQueue<LoggerConsole>>(1));
        loggers.push_back(std::make_unique<ConcurentQueue<LoggerFile>>(2));
    }

    void AddCommand(const std::string& str);

    void Log();

private:
    std::queue<std::string> commands;

    long _time;

    size_t post = 0;

    size_t _open_brakets = 0;
    size_t _close_brakets = 0;
    size_t _size_block;

    std::vector<std::unique_ptr<Logger>> loggers;
};