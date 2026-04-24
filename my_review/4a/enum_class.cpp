#include <iostream>

enum class Status {
    Enrolled,
    Graduated,
    Withdrawn
};

int main()
{
    Status s = Status::Enrolled;

    if (s == Status::Enrolled)
    {
        std::cout << "Enrolled\n";
    }

    return 0;
}

1. 定义一个新类型 Status
2. 让它只能在几个固定选项里选一个

我定义了一个新类型，叫 Status
它只能是这 3 个值之一：
Enrolled, Graduated, Withdrawn

创建一个 Status 类型的变量 s
它的值是 Enrolled

如果 s 的值是 Enrolled
就输出 Enrolled

enum class = 固定选项
