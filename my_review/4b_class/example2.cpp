#include <iostream>
#include <string>

class Student {
public:
    Student()
    {
        id = 0;
        name = "Unknown";
        gpa = 0.0;
    }

    void print()
    {
        std::cout << id << "\n";
        std::cout << name << "\n";
        std::cout << gpa << "\n";
    }

private:
    int id;
    std::string name;
    float gpa;
};

int main()
{
    Student s;
    s.print();
    return 0;
}
