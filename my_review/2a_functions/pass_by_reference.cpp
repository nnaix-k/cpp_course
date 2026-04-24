#include <iostream>

void func(int& x)
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

int x   -> 传值，改的是副本
int& x  -> 传引用，改的是原变量
