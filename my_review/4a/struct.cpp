#include <iostream>
#include <string>

struct Student {
    int id;
    std::string name;
    float gpa;
};

int main()
{
    Student s;
    s.id = 1;
    s.name = "Alice";
    s.gpa = 3.8;

    std::cout << s.id << "\n";
    std::cout << s.name << "\n";
    std::cout << s.gpa << "\n";

    return 0;
}

1. 定义一个新类型 Student
2. 创建一个 Student 变量 s
3. 给 s 填信息，然后输出

#include <iostream>：为了用 std::cout
#include <string>：为了用 std::string

我现在自己定义一个新类型，名字叫 Student
这个类型里面有 3 个成员：
id, name, gpa

创建一个 Student 类型的变量，名字叫 s

struct = 把几个相关变量打包成一个新类型
