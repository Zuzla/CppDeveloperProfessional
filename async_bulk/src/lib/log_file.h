#pragma once

#include "log.h"

class LoggerFile : public Logger
{
public:
    LoggerFile() = default;

    void Log(const DataBclock& block) override
    {
        std::fstream f;
        f.open(block.name_file, std::ios::out);
        f << block.data << std::endl;
        f.close();
    }


private:

};