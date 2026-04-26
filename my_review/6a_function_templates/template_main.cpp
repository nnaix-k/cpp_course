#include <iostream>
#include <vector>
#include "template_example.h"

int main()
{
    std::vector<int> a = {1, 2, 3, 4};
    std::vector<double> b = {2.5, 3.5, 4.5};

    std::cout << compute_mean(a) << "\n";
    std::cout << compute_mean(b) << "\n";

    return 0;
}

模板函数写在头文件里时，main.cpp 怎么调用
