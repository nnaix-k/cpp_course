#include <iostream>
#include <string>

int main()
{
    std::string filename = "myfile.txt";

    std::cout << filename << "\n";
    std::cout << filename.substr(0, 2) << "\n";

    return 0;
}
