#include "bulk.h"

#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Argc error!\n";
        return EXIT_FAILURE;
    }

    Bulk bulk(std::stoi(argv[1]));

    bulk.RunCmd();

    return EXIT_SUCCESS;
}
