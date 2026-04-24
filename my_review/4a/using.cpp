#include <iostream>
#include <vector>

using Numbers = std::vector<int>;   以后 Numbers 就是 std::vector<int> 的小名

int main()
{
    Numbers a = {1, 2, 3, 4};

    std::cout << a[0] << "\n";
    std::cout << a[1] << "\n";

    return 0;
}

1. 给一个很长的类型起了一个短名字
2. 以后直接用这个短名字
