#include <iostream>
#include "matrix.h"

int main(int, char **)
{
    auto matrix = std::make_shared<Matrix<int>>();

    (*matrix)[1][0] = 1;

    for (int i = 0; i < 10; ++i)
    {
        (*matrix)[i][i] = i;
        (*matrix)[i][9 - i] = 9 - i;
    }

    std::cout << "Матрица - \n";

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            std::cout << (*matrix)[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Размер = " << (*matrix).size() << std::endl;

    return EXIT_SUCCESS;
}
