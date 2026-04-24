#include <iostream>

void func(int x)
{
    x += 10;
}

int main()
{
    int val = 0;
    func(val);
    std::cout << val << "\n";
    return 0;
}

pass by value：函数里改参数，不会影响外面的原变量
