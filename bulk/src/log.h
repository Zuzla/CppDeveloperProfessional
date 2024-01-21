#pragma once
#include <iostream>
#include <fstream>
#include "block.h"

class Logger
{
public:
    virtual void Log(const DataBclock& block) = 0;

    virtual ~Logger() {};
};