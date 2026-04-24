#include <iostream>

int main()
{
    int mark;

    std::cout << "Enter your mark: ";
    std::cin >> mark;

    if (mark >= 70)
    {
        std::cout << "Distinction\n";
    }
    else if (mark >= 60)
    {
        std::cout << "Merit\n";
    }
    else if (mark >= 50)
    {
        std::cout << "Pass\n";
    }
    else
    {
        std::cout << "Fail\n";
    }

    return 0;
}
