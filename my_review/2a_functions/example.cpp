#include <iostream>

int add(int a, int b)
{
    return a + b;
}

int main()
{
    int result = add(3, 5);
    std::cout << result << "\n";
    return 0;
}
