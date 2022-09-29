#include <iostream>

#include "matrix.hpp"

using namespace lib;

int main(int argc, char const *argv[])
{
    Matrix<std::string> matrix(4, 4);

    matrix.at(1, 1) = "Felipe";

    std::cout << matrix << std::endl;

    return 0;
}
