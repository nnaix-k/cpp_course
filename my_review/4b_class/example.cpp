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

    Student(int student_id, std::string student_name, float student_gpa)
    {
        id = student_id;
        name = student_name;
        gpa = student_gpa;
    }

    void print()
    {
        std::cout << "ID: " << id << "\n";
        std::cout << "Name: " << name << "\n";
        std::cout << "GPA: " << gpa << "\n";
    }

    void set_gpa(float new_gpa)
    {
        gpa = new_gpa;
    }

    float get_gpa() const
    {
        return gpa;
    }

private:
    int id;
    std::string name;
    float gpa;
};

int main()
{
    Student s1;
    Student s2(1, "Alice", 3.8);

    s1.print();
    std::cout << "\n";

    s2.print();
    std::cout << "\n";

    s2.set_gpa(4.0);
    std::cout << "Updated GPA: " << s2.get_gpa() << "\n";

    return 0;
}


1. 定义一个类 Student
2. Student 里面有数据：id, name, gpa
3. Student 里面也有功能：print, set_gpa, get_gpa
4. 在 main 里创建两个学生对象
5. 调用这些对象自己的功能

class 更强调把数据和函数放在一起管理
class = 数据 + 函数


private = 外面不能直接碰
public = 外面可以用
