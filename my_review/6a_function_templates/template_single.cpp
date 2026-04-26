#include <iostream>

template <typename T>
T pow3(T x)
{
    return x * x * x;
}

int main()
{
    std::cout << pow3(2) << "\n";
    std::cout << pow3(2.5) << "\n";
    std::cout << pow3(3.0f) << "\n";

    return 0;
}

一个模板函数，计算 x 的三次方
