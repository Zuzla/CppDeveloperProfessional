#pragma once
#include <iostream>
#include <fstream>
#include "block.h"

class Logger
{
public:
    virtual void Log() {};
    virtual void Log(const DataBclock& block) {};

    virtual ~Logger() {};
};