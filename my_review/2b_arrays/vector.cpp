#include <iostream>
#include <vector>

int main()
{
    std::vector<int> vec;

    vec.push_back(1);
    vec.push_back(6);
    vec.push_back(10);

    std::cout << vec.size() << "\n";
    std::cout << vec[0] << "\n";

    return 0;
}
