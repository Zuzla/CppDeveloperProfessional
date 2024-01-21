#pragma once

#include "log.h"

class LoggerConsole : public Logger
{
public:
    void Log(const DataBclock& block) override
    {
        std::cout << "bulk: ";
        std::cout << block.data << std::endl;
    }
};