#include <iostream>
#include <array>

int main()
{
    std::array<int, 4> arr = {1, 2, 3, 4};

    std::cout << arr[0] << "\n";
    std::cout << arr.size() << "\n";

    return 0;
}
