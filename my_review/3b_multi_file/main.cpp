#include <iostream>
#include "add.h"    
int main()
{
    std::cout << add(3, 5) << "\n";
    return 0;
}

include 头文件 .h
编译时再把多个 .cpp 一起编译

.h 用来 include
.cpp 用来编译

一次全编译
g++ main.cpp add.cpp -o main
把 main.cpp 和 add.cpp 一起编译，
生成可执行文件 main
./main
